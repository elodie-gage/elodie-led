#include <FastLED.h>
#include "simulation.h"
#include "common_led.h"

LedRace ledRace;
TestPattern testPattern;
Rainbow rainbow;


extern "C" void render(CRGB* leds) {

  PatternRenderer* patternRenderer; 

  patternRenderer = &rainbow;

  patternRenderer->render(leds);
}