
#define FASTLED_HD_COLOR_MIXING 0

#include <FastLED.h>
#define NUM_LEDS 300

extern "C" void led_race_loop(CRGB* leds, unsigned long currentMillis);