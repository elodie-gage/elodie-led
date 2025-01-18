#include <crgb.h>

#include "led_common.h"
#include "patterns.h"

/* Default "everything black/off" pattern */

void Black::render(CRGB* leds) { fill_black(leds, NUM_LEDS); }