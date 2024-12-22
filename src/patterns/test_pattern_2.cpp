#include "patterns.h"
#include <crgb.h>

void TestPattern2::render(CRGB* leds) {

  for (int i = 0; i < 32; i++) {
    int led = i;
    int r = 255 - (i*8);
    leds[led].setRGB(r, 0, 0);  
  }

  for (int i = 0; i < 32; i++) {
    int led = 32+i;
    int g = 255 - (i*8);
    leds[led].setRGB(0, g, 0);  
  }

  for (int i = 0; i < 32; i++) {
    int led = 64+i;
    int b = 255 - (i*8);
    leds[led].setRGB(0, 0, b);  
  }

  for (int i = 0; i < 32; i++) {
    int led = 96+i;
    int c = 255 - (i*8);
    leds[led].setRGB(c, c, c);  
  }


}