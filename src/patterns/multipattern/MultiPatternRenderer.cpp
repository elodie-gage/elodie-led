#include <crgb.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "patterns.h"

void MultiPatternRenderer::addPattern(std::unique_ptr<MultiPatternItem> item) {
  std::cout << "Adding pattern" << std::endl;
  patterns.push_back(std::move(item));
}

void MultiPatternRenderer::render(CRGB* leds) {
  // Clear LEDs
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  std::cout << "Updating patterns..." << std::endl;
  std::cout << patterns.size() << std::endl;

  for (const auto& pattern : patterns) {
    if (pattern) {
      std::cout << "Pattern is valid" << std::endl;
    }
    std::cout << "About to SegFault" << std::endl;
    pattern->update();
    std::cout << "We don't get here" << std::endl;
  }

  std::cout << "Removing patterns..." << std::endl;

  // Remove patterns that are dead
  patterns.erase(
      std::remove_if(patterns.begin(), patterns.end(),
                     [](const auto& pattern) { return pattern->isDead(); }),
      patterns.end());

  std::cout << "Rendering patterns..." << std::endl;
  std::cout << patterns.size() << std::endl;
  // Draw
  for (const auto& pattern : patterns) {
    pattern->render(leds);
  }
}
