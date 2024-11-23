#include <FastLED.h>
#include "simulation.h"
#include "common_led.h"

LedRace ledRace;
TestPattern testPattern;
Rainbow rainbow;
Snowflakes snowflakes;


extern "C" void render(CRGB* leds) {

  PatternRenderer* patternRenderer; 

  patternRenderer = &snowflakes;

  patternRenderer->render(leds);
}

uint16_t XY(uint8_t x, uint8_t y) {
    return 0;
}
