#include <Arduino.h>
#include <FastLED.h>
#include "common_led.h"

int offsetPattern;
unsigned long lastUpdate = 0;

void led_race_loop(CRGB* leds) {
  unsigned long currentMillis = millis();

  for (int i = 0; i < NUM_LEDS; i++) {
    int red = i == offsetPattern ? 255 : 0;
    leds[i].setRGB(red, 0, 0);
  }

  FastLED.show();

  if (currentMillis - lastUpdate > 10) {
    offsetPattern++;  // Increment the offset
    if (offsetPattern >= NUM_LEDS) {  // Wrap around
      offsetPattern = 0;
    }
    lastUpdate = currentMillis;
  }
}
