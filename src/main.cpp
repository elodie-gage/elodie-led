#include <FastLED.h>
#include "common_led.h"

#define DATA_PIN 23

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  led_race_loop(leds);
}
