#include "common_led.h"
#include <FastLED.h>

void TestPattern::render(CRGB* leds) {
  for (int i = 0; i < NUM_LEDS; i++) {

    if (i % 100 == 0) {
      leds[i] = CRGB::White;
    } else if (i % 10 == 0) {
      leds[i] = CRGB::Red;
    } else if (i % 5 == 0) {
      leds[i] = CRGB::Green;
    } else {
      leds[i] = CRGB::Black;
    }
  }
}