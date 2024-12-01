
#include <FastLED.h>
#define NUM_LEDS 428
// 214 on each side plus slope
// 132 on each side
// 82 on each slope

class PatternRenderer {
   public:
      virtual void render(CRGB* leds) = 0;
      virtual ~PatternRenderer() = default; // Ensure proper cleanup
};

class LedRace: public PatternRenderer  {
   public:
      void render(CRGB* leds) override;
};

class TestPattern: public PatternRenderer  {
   public:
      void render(CRGB* leds) override;
};

class Rainbow: public PatternRenderer  {
   public:
      void render(CRGB* leds) override;
};

class Snowflakes1: public PatternRenderer  {
   public:
      void render(CRGB* leds) override;
};

class Snowflakes2: public PatternRenderer  {
   public:
      void render(CRGB* leds) override;
};

class TestPattern2: public PatternRenderer  {
   public:
      void render(CRGB* leds) override;
};