#include <FastLED.h>
#include "common_led.h"
#include <limits.h>

#define DATA_PIN 23

#define INTERVAL_MICROS 10000


typedef unsigned long ulong;

CRGB leds[NUM_LEDS];

ulong lastUpdateMicros;
ulong lastSerialUpdateMicros;

LedRace ledRace;
TestPattern testPattern;
Rainbow rainbow;

PatternRenderer* activePatternRenderer;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  lastUpdateMicros = 0;

  activePatternRenderer = &testPattern;
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

  activePatternRenderer->render(leds);
  FastLED.show();

  // Wait for 10ms (10,000us)
  ulong elapsed;
  do {
    elapsed = elapsedMicros(lastUpdateMicros); 
  } while (elapsed < INTERVAL_MICROS);
  lastUpdateMicros = micros();
}

