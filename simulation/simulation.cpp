#include <crgb.h>
#include "simulation.h"
#include "common_led.h"

LedRace ledRace;
TestPattern testPattern;
Rainbow rainbow;
Snowflakes1 snowflakes1;
Snowflakes2 snowflakes2;
TestPattern2 testPattern2;
Twinkles twinkles;


extern "C" void render(CRGB* leds) {

  PatternRenderer* patternRenderer; 

  patternRenderer = &snowflakes2;

  patternRenderer->render(leds);
}
