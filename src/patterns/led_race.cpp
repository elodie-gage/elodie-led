#include "common_led.h"
#include <FastLED.h>


void LedRace::render(CRGB* leds) {
  static int offsetPattern;

  offsetPattern++;  // Increment the offset
  if (offsetPattern >= NUM_LEDS) {  // Wrap around
    offsetPattern = 0;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    int red = i == offsetPattern ? 255 : 0;
    leds[i].setRGB(red, 0, 0);
  }
}