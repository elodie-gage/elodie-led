#include <crgb.h>

#include <algorithm>
#include <iterator>
#include <vector>

#include "patterns.h"

class Twinkle2 : public MultiPatternItem {
 private:
  int pos;

 public:
  Twinkle2(int randValue) { pos = randValue % NUM_LEDS; }

  void update() override {}

  bool isDead() override { return false; }

  void render(CRGB* leds) override { leds[pos].setRGB(255, 0, 0); }
};

class TwinklesMod::Impl {
 private:
  MultiPatternRenderer multiPatternRenderer;

 public:
  Impl();
  void render(CRGB* leds);
};

TwinklesMod::Impl::Impl() {
  // Initialise
}

void TwinklesMod::Impl::render(CRGB* leds) {
  int randValue = rand();

  // Spawn new twinkle
  if (randValue % 25 < 2) {
    multiPatternRenderer.addPattern(std::make_unique<Twinkle2>(randValue));
  }

  multiPatternRenderer.render(leds);
}

TwinklesMod::TwinklesMod() : impl(new Impl) {}
TwinklesMod::~TwinklesMod() { delete impl; }
void TwinklesMod::render(CRGB* leds) { impl->render(leds); }
