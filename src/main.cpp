#define FASTLED_OVERCLOCK 1.2

#include <ArduinoOTA.h>
#include <FastLED.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <arduino.h>
#include <limits.h>

#include "mqtt.h"
#include "patterns.h"
#define IR_PIN D10
#define INTERVAL_MICROS 20000

#define STATS_EVERY 1000
// #define PRINT_STATS 1

typedef unsigned long ulong;

CRGB leds[NUM_LEDS];

IRrecv irrecv(IR_PIN);
decode_results results;

ulong lastUpdateMicros;
ulong lastSerialUpdateMicros;

// Define an instance of each pattern class
#define MAKE_INSTANCE(classname) classname instance_of_##classname
ALL_PATTERNS(MAKE_INSTANCE, ;);
#undef MAKE_INSTANCE

PatternRenderer* activePatternRenderer;

#define CHECK_STRING(classname)                       \
  if (option == #classname) {                         \
    activePatternRenderer = &instance_of_##classname; \
    return;                                           \
  }

void onOptionChange(std::string option) {
  // Translate each pattern name as a string into the instance of the class
  ALL_PATTERNS(CHECK_STRING, else)

  Serial.println("Unknown pattern");
}

#undef CHECK_STRING

void setup() {
  delay(500);

  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting...");
  irrecv.enableIRIn();  // Start the receiver
  Serial.println("Enable IR");

  start(onOptionChange);

  FastLED.addLeds<NEOPIXEL, D4>(leds, NUM_LEDS);

  lastUpdateMicros = 0;

  activePatternRenderer = &instance_of_Black;
  Serial.println("LED control running...");
}

ulong elapsedMicros(ulong since) {
  ulong microsNow = micros();
  ulong elapsed = microsNow - lastUpdateMicros;
  if (elapsed < 0) {
    // clock has overflowed
    elapsed += ULONG_MAX;
  }
  return elapsed;
}

void loop() {
  //   static ulong totalRenderElapsed = 0;
  //   static ulong totalShowElapsed = 0;
  //   static int loopCount = 0;

  activePatternRenderer->render(leds);
  //   ulong renderElapsed = elapsedMicros(lastUpdateMicros);
  //   totalRenderElapsed += renderElapsed;

  FastLED.show();
  //   ulong showElapsed = elapsedMicros(lastUpdateMicros) - renderElapsed;
  //   totalShowElapsed += showElapsed;

  //   // Wait for INTERVAL_MICROS
  //   ulong totaElapsed;
  //   do {
  //     ArduinoOTA.handle();  // Check for OTA update

  //     totaElapsed = elapsedMicros(lastUpdateMicros);
  //   } while (totaElapsed < INTERVAL_MICROS);
  //   lastUpdateMicros = micros();

  //   if (loopCount++ > STATS_EVERY) {
  // #ifdef PRINT_STATS
  //     ulong averageRenderElapsed = totalRenderElapsed / loopCount;
  //     ulong averageShowElapsed = totalShowElapsed / loopCount;

  //     Serial.print("Avg render ");
  //     Serial.print(averageRenderElapsed);
  //     Serial.print("us. Avg show ");
  //     Serial.print(averageShowElapsed);
  //     Serial.println("us");
  // #endif

  //     totalShowElapsed = 0;
  //     totalRenderElapsed = 0;
  //     loopCount = 0;
  //   }

  if (irrecv.decode(&results)) {
    // Serial.println(resultToHumanReadableBasic(&results));
    serialPrintUint64(results.value, HEX);
    Serial.print("\n");

    if (results.value == 0xFF22DD) {
      Serial.println("Change to rainbow");
      activePatternRenderer = &instance_of_Rainbow;
    }
    if (results.value == 0xFFC23D) {
      Serial.println("Change to other rainbow");
      activePatternRenderer = &instance_of_Rainbow2;
    }
    if (results.value == 0xFFE01F) {
      Serial.println("Change to test pattern");
      activePatternRenderer = &instance_of_TestPattern;
    }
    if (results.value == 0xFFE21D) {
      Serial.println("Change to black");
      activePatternRenderer = &instance_of_Black;
    }

    irrecv.resume();  // Receive the next value
  }
}
