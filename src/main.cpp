#include <FastLED.h>
#include "common_led.h"
#include <limits.h>

#define DATA_PIN 23

#define INTERVAL_MICROS 10000

#define STATS_EVERY 1000


typedef unsigned long ulong;

CRGB leds[NUM_LEDS];

ulong lastUpdateMicros;
ulong lastSerialUpdateMicros;

LedRace ledRace;
TestPattern testPattern;
Rainbow rainbow;
Snowflakes2 snowflake2;

PatternRenderer* activePatternRenderer;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  lastUpdateMicros = 0;

  activePatternRenderer = &snowflake2;
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

  static ulong totalRenderElapsed = 0;
  static ulong totalShowElapsed = 0;
  static int loopCount = 0;

  activePatternRenderer->render(leds);
  ulong renderElapsed = elapsedMicros(lastUpdateMicros); 
  totalRenderElapsed += renderElapsed;

  FastLED.show();
  ulong showElapsed = elapsedMicros(lastUpdateMicros) - renderElapsed; 
  totalShowElapsed += showElapsed;

  // Wait for 10ms (10,000us)
  ulong totaElapsed;
  do {
    totaElapsed = elapsedMicros(lastUpdateMicros); 
  } while (totaElapsed < INTERVAL_MICROS);
  lastUpdateMicros = micros();

  if (loopCount++ > STATS_EVERY) {

    ulong averageRenderElapsed = totalRenderElapsed / loopCount;
    ulong averageShowElapsed = totalShowElapsed / loopCount;

    Serial.print("Avg render ");
    Serial.print(averageRenderElapsed);
    Serial.print("us. Avg show ");
    Serial.print(averageShowElapsed);
    Serial.println("us");

    totalShowElapsed = 0;
    totalRenderElapsed = 0;
    loopCount = 0;
  }
}

