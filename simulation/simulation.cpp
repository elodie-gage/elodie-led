#include <FastLED.h>
#include "simulation.h"
#include "common_led.h"

extern "C" void render(CRGB* leds) {
  LedRace ledRace;

  PatternRenderer* patternRenderer; 

  patternRenderer = &ledRace;

  patternRenderer->render(leds);
}