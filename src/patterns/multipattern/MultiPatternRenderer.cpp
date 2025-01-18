#include <crgb.h>

#include <algorithm>
#include <iterator>
#include <vector>

#include "led_common.h"
#include "patterns.h"

void MultiPatternRenderer::addPattern(std::unique_ptr<MultiPatternItem> item) {
  patterns.push_back(std::move(item));
}

void MultiPatternRenderer::render(CRGB* leds) {
  // Clear LEDs
  fill_black(leds, NUM_LEDS);

  for (const auto& pattern : patterns) {
    pattern->update();
  }

  // Remove patterns that are dead
  patterns.erase(
      std::remove_if(patterns.begin(), patterns.end(),
                     [](const auto& pattern) { return pattern->isDead(); }),
      patterns.end());

  // Render
  for (const auto& pattern : patterns) {
    pattern->render(leds);
  }
}
