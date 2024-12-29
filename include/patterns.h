#include <memory>
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

#define PATTERN_INSTANCE(NAME) \
class NAME: public PatternRenderer  {  \
   public:                                \
      void render(CRGB* leds) override;   \
};                                        \

PATTERN_INSTANCE(Black)
PATTERN_INSTANCE(LedRace)
PATTERN_INSTANCE(TestPattern)
PATTERN_INSTANCE(Rainbow)
PATTERN_INSTANCE(Snowflakes1)
PATTERN_INSTANCE(Snowflakes2)
PATTERN_INSTANCE(TestPattern2)
PATTERN_INSTANCE(Twinkles)

#undef PATTERN_INSTANCE

class Wolfram135: public PatternRenderer {
      class Impl;
      Impl *impl;
   public:
      Wolfram135();
      ~Wolfram135();
      void render(CRGB* leds) override;
};

/*
 * List of all patterns, in the form of a parametric macro. Whenever
 * you want to list all the known patterns in other parts of the code,
 * you can invoke this with another macro name, and it will evaluate
 * that macro with each pattern as an argument.
 *
 * The second parameter SEPARATOR will be interleaved between the
 * invocations of the macro X.
 */
#define ALL_PATTERNS(X, SEPARATOR)                        \
X(Black) SEPARATOR \
X(LedRace) SEPARATOR \
X(TestPattern) SEPARATOR \
X(Rainbow) SEPARATOR \
X(Snowflakes1) SEPARATOR \
X(Snowflakes2) SEPARATOR \
X(TestPattern2) SEPARATOR \
X(Twinkles) SEPARATOR \
X(Wolfram135)
