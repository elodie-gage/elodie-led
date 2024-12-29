#include "patterns.h"
#include <crgb.h>

/* Default "everything black/off" pattern */

void Black::render(CRGB* leds) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }
}