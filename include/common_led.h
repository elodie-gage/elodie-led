
#include <FastLED.h>
#define NUM_LEDS 300

class PatternRenderer {
   public:
      virtual void render(CRGB* leds) = 0;
      virtual ~PatternRenderer() = default; // Ensure proper cleanup
};

class LedRace: public PatternRenderer  {
   public:
      void render(CRGB* leds) override;
};