#include <crgb.h>

#include <algorithm>
#include <iterator>
#include <vector>

#include "patterns.h"

// class NAME : public PatternRenderer {
//  public:
//   void render(CRGB* leds) override;
// };

class Twinkle : public MultiPatternItem {
 private:
  int pos;
  CRGB color;
  int seq;
  int scaleUpRate;
  int scaleDownRate;
  int scaleDownFromSeq;
  int deathSeq;
  bool isRainbow;

 public:
  Twinkle(int randValue) {
    seq = 0;

    pos = randValue % NUM_LEDS;

    int colorChoice = randValue % 1000;

    isRainbow = false;
    if (colorChoice < 800) {
      color = CRGB(255, 255, 255);  // white
      scaleUpRate = 5;
      scaleDownRate = 5;
    } else if (colorChoice < 970) {
      color = CRGB(245, 239, 66);  // gold
      scaleUpRate = 2;
      scaleDownRate = 2;
    } else {
      isRainbow = true;
      deathSeq = 220;
    }

    if (!isRainbow) {
      scaleDownFromSeq = 255 / scaleUpRate;
      deathSeq =
          scaleDownFromSeq + (scaleUpRate * scaleDownFromSeq) / scaleDownRate;
    }
  }

  void update() override { seq++; }

  bool isDead() override { return seq >= deathSeq; }

  void render(CRGB* leds) override {
    if (isRainbow) {
      uint8_t hue = seq;
      leds[pos].setHSV(hue, 255, 255);
    } else {
      int fadeFactor = seq < scaleDownFromSeq
                           ? seq * scaleUpRate
                           : (scaleDownFromSeq * scaleUpRate) -
                                 ((seq - scaleDownFromSeq) * scaleDownRate);

      if (fadeFactor > 0) {
        leds[pos] = color.scale8(fadeFactor);
      }
    }
  }
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
    // multiPatternRenderer.addPattern(std::make_unique<Twinkle>(randValue));
  }

  multiPatternRenderer.render(leds);
}

TwinklesMod::TwinklesMod() : impl(new Impl) {}
TwinklesMod::~TwinklesMod() { delete impl; }
void TwinklesMod::render(CRGB* leds) { impl->render(leds); }
