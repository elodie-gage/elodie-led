#include <crgb.h>

#include <algorithm>
#include <iterator>
#include <vector>

#include "patterns.h"

class Twinkle2 : public MultiPatternItem {
 private:
  int pos;
  CRGB color;
  int seq;
  int scaleUpRate;
  int scaleDownRate;
  int scaleDownFromSeq;
  int deathSeq;

 public:
  Twinkle2(int randValue) {
    seq = 0;

    pos = randValue % NUM_LEDS;

    int colorChoice = randValue % 1000;

    if (colorChoice < 800) {
      color = CRGB(255, 255, 255);  // white
      scaleUpRate = 5;
      scaleDownRate = 5;
    } else {
      color = CRGB(245, 239, 66);  // gold
      scaleUpRate = 2;
      scaleDownRate = 2;
    }

    scaleDownFromSeq = 255 / scaleUpRate;
    deathSeq =
        scaleDownFromSeq + (scaleUpRate * scaleDownFromSeq) / scaleDownRate;
  }

  void update() override { seq++; }

  bool isDead() override { return seq >= deathSeq; }

  void render(CRGB* leds) override {
    int fadeFactor = seq < scaleDownFromSeq
                         ? seq * scaleUpRate
                         : (scaleDownFromSeq * scaleUpRate) -
                               ((seq - scaleDownFromSeq) * scaleDownRate);

    if (fadeFactor > 0) {
      leds[pos] = color.scale8(fadeFactor);
    }
  }
};

class RainbowTwinkle : public MultiPatternItem {
 private:
  int pos;
  CRGB color;
  int seq;
  int scaleUpRate;
  int scaleDownRate;
  int scaleDownFromSeq;
  int deathSeq;

 public:
  RainbowTwinkle(int randValue) {
    seq = 0;

    pos = randValue % NUM_LEDS;

    int colorChoice = randValue % 1000;

    deathSeq = 220;
  }

  void update() override { seq++; }

  bool isDead() override { return seq >= deathSeq; }

  void render(CRGB* leds) override {
    uint8_t hue = seq;
    leds[pos].setHSV(hue, 255, 255);
  }
};

class Twinkles::Impl {
 private:
  MultiPatternRenderer multiPatternRenderer;

 public:
  Impl();
  void render(CRGB* leds);
};

Twinkles::Impl::Impl() {
  // Initialise
}

void Twinkles::Impl::render(CRGB* leds) {
  int randValue = rand();

  // Spawn new twinkle
  if (randValue % 100 < 5) {
    multiPatternRenderer.addPattern(std::make_unique<Twinkle2>(randValue));
  } else if (randValue % 100 < 10) {
    multiPatternRenderer.addPattern(
        std::make_unique<RainbowTwinkle>(randValue));
  }

  multiPatternRenderer.render(leds);
}

Twinkles::Twinkles() : impl(new Impl) {}
Twinkles::~Twinkles() { delete impl; }
void Twinkles::render(CRGB* leds) { impl->render(leds); }
