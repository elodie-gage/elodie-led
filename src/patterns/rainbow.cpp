#include "common_led.h"
#include <FastLED.h>


void Rainbow::render(CRGB* leds) {
  static int increment = 0;

  int saturation = 255;
  int value = 255;

  int modifier = increment / 10;

  for (int i = 0; i < NUM_LEDS; i++) {
    int hue = (modifier + (i * 255) / NUM_LEDS) % 255;

    leds[i].setHSV(hue, saturation, value);
  }

  increment++;

}