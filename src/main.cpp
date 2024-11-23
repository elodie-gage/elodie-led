#include <FastLED.h>
#include "common_led.h"
#include <limits.h>

#define DATA_PIN 23

#define INTERVAL_MICROS 10000


typedef unsigned long ulong;

CRGB leds[NUM_LEDS];

ulong lastUpdateMicros;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  lastUpdateMicros = 0;
}



void loop() {

  led_race_loop(leds);

  FastLED.show();

  ulong stopMicros = micros();

  // Wait for 10ms (10,000us)
  ulong elapsed;
  do {
    elapsed = stopMicros - lastUpdateMicros; 
    if (elapsed < 0) {
      // clock has overflowed
      elapsed += ULONG_MAX;
    }
  } while (elapsed < INTERVAL_MICROS);
}
