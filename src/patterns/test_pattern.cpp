#include <crgb.h>

#include "patterns.h"

void TestPattern::render(CRGB* leds) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 100 == 0) {
      leds[i].setRGB(255, 255, 255);
    } else if (i % 10 == 0) {
      leds[i].setRGB(255, 0, 0);
    } else if (i % 5 == 0) {
      leds[i].setRGB(0, 255, 0);
    } else {
      leds[i].setRGB(5, 5, 5);
    }
  }
}