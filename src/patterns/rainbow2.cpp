#include "patterns.h"
#include <crgb.h>
#include <chsv.h>

#define RAINBOW_LENGTH 50
#define FADE_LENGTH 8
// rainbow runs from hue 0 to this hue (anything higher goes back to red)
#define END_HUE 220

CHSV colourAtIndex(int idx) {
    uint8_t saturation = 255;
    if (idx < 0) {
      return CHSV(0,0,0);
    } else if (idx < FADE_LENGTH) {
      uint8_t hue = 0;
      uint8_t value = (255 * idx) / FADE_LENGTH;
      return CHSV(hue, saturation, value);
    } else if (idx < FADE_LENGTH+RAINBOW_LENGTH) {
      
      uint8_t hue =  END_HUE * (idx-FADE_LENGTH) / RAINBOW_LENGTH ;
      uint8_t value = 255;
      return CHSV(hue, saturation, value);
    } else if (idx < FADE_LENGTH+RAINBOW_LENGTH+FADE_LENGTH) {
      uint8_t hue =  END_HUE;
      uint8_t value = 255 - ((255 * (idx-FADE_LENGTH-RAINBOW_LENGTH)) / FADE_LENGTH);
      return CHSV(hue, saturation, value);
    } else {
      return CHSV(0,0,0);
    }
}

void Rainbow2::render(CRGB* leds) {
  static int increment = 0;

  int modifier = increment++ / 2;

  for (int led = 0; led < NUM_LEDS; led++) {
    int rainbowIdx = (led + modifier) % (NUM_LEDS+RAINBOW_LENGTH+FADE_LENGTH+FADE_LENGTH);

    leds[led] = colourAtIndex(rainbowIdx);
  }
}

#undef RAINBOW_LENGTH
#undef FADE_LENGTH
#undef END_HUE
