#include "led_common.h"

void fill_black(struct CRGB* targetArray, int numToFill) {
  for (int i = 0; i < numToFill; ++i) {
    targetArray[i] = CRGB::Black;
  }
}