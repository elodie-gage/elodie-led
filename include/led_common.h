#pragma once
// It should be possible to replace this with crgb.h, but that causes errors
#include <FastLED.h>

#include <memory>
#include <vector>

// The total number of LEDs in the string
#define NUM_LEDS 428

void fill_black(struct CRGB* targetArray, int numToFill);

class PatternRenderer {
 public:
  virtual void render(CRGB* leds) = 0;
  virtual ~PatternRenderer() = default;  // Ensure proper cleanup
};

class MultiPatternItem {
 public:
  virtual void update() = 0;
  virtual bool isDead() = 0;
  virtual void render(CRGB* leds) = 0;
  virtual ~MultiPatternItem() = default;
};

class MultiPatternRenderer {
 private:
  std::vector<std::unique_ptr<MultiPatternItem>> patterns;

 public:
  void render(CRGB* leds);
  ~MultiPatternRenderer() = default;  // Ensure proper cleanup

  void addPattern(std::unique_ptr<MultiPatternItem>);
};