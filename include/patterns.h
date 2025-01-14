#include <FastLED.h>

#include <memory>
#include <vector>
#define NUM_LEDS 428
// 214 on each side plus slope
// 132 on each side
// 82 on each slope

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

#define PATTERN_INSTANCE(NAME)          \
  class NAME : public PatternRenderer { \
   public:                              \
    void render(CRGB* leds) override;   \
  };

#define COMPLEX_PATTERN_INSTANCE(NAME)  \
  class NAME : public PatternRenderer { \
    class Impl;                         \
    Impl* impl;                         \
                                        \
   public:                              \
    NAME();                             \
    ~NAME();                            \
    void render(CRGB* leds) override;   \
  };

PATTERN_INSTANCE(Black)

PATTERN_INSTANCE(LedRace)
PATTERN_INSTANCE(TestPattern)
PATTERN_INSTANCE(Rainbow)
PATTERN_INSTANCE(Snowflakes1)
PATTERN_INSTANCE(Snowflakes2)
PATTERN_INSTANCE(TestPattern2)
PATTERN_INSTANCE(Twinkles)
PATTERN_INSTANCE(Rainbow2)
PATTERN_INSTANCE(Bounce)
COMPLEX_PATTERN_INSTANCE(Wolfram135)
COMPLEX_PATTERN_INSTANCE(TwinklesMod)

#undef PATTERN_INSTANCE
#undef COMPLEX_PATTERN_INSTANCE

/*
 * List of all patterns, in the form of a parametric macro. Whenever
 * you want to list all the known patterns in other parts of the code,
 * you can invoke this with another macro name, and it will evaluate
 * that macro with each pattern as an argument.
 *
 * The second parameter SEPARATOR will be interleaved between the
 * invocations of the macro X.
 */
#define ALL_PATTERNS(X, SEPARATOR)        \
  X(Black) SEPARATOR X(LedRace)           \
  SEPARATOR                               \
  X(TestPattern) SEPARATOR X(Rainbow)     \
  SEPARATOR                               \
  X(Snowflakes1) SEPARATOR X(Snowflakes2) \
  SEPARATOR                               \
  X(TestPattern2) SEPARATOR X(Twinkles)   \
  SEPARATOR                               \
  X(TwinklesMod) SEPARATOR X(Rainbow2)    \
  SEPARATOR X(Wolfram135)
