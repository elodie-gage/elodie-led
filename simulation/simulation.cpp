#include <FastLED.h>
#include "simulation.h"
#include "common_led.h"

extern "C" void render(CRGB* leds) {
  LedRace ledRace;
  TestPattern testPattern;

  PatternRenderer* patternRenderer; 

  patternRenderer = &testPattern;

  patternRenderer->render(leds);
}