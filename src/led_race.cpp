//#include <Arduino.h>
#include "common_led.h"
#include <FastLED.h>

int offsetPattern;
unsigned long lastUpdate = 0;

void led_race_loop(CRGB* leds) {

  offsetPattern++;  // Increment the offset
  if (offsetPattern >= NUM_LEDS) {  // Wrap around
    offsetPattern = 0;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    int red = i == offsetPattern ? 255 : 0;
    leds[i].setRGB(red, 10, 0);
  }
}
