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
Wolfram135 wolfram135;


extern "C" void render(CRGB* leds) {

  PatternRenderer* patternRenderer; 

  patternRenderer = &wolfram135;

  patternRenderer->render(leds);
}
