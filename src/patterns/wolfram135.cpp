/*
 * Implement the Wolfram 135 cellular automaton.
 *
 * This is a one-dimensional cellular automaton in which each cell's
 * new state is computed as a function of the previous state of that
 * cell and its two immediate neighbours. Interpreting that row of
 * three cells as a 3-bit binary number, a cell is live in the next
 * generation if the previous three cells had states 000, 001, 010 or
 * 111, i.e. 0, 1, 2 or 7. (The index number 135 reflects this,
 * because in binary it's 10000111 = 2^0+2^1+2^2+2^7.)
 *
 * To make this a little more interesting than just flashing black and
 * white, cells that have just turned _off_ are shown in orange, and
 * fade gradually through red to black. The fade is computed smoothly
 * per frame, though the automaton itself evolves at a slower rate.
 */

#include <algorithm>
#include <array>
#include <stdint.h>

#include <FastLED.h>
#include "patterns.h"

class Wolfram135::Impl {
    // Delay between successive generations.
    static constexpr int delay_frames = 50;

    // How many frames until we compute the next generation.
    int next_frame;

    // The logical state of each cell (on or off).
    std::array<bool, NUM_LEDS> value;

    // The current state of each off cell, fading out. Starts at 384,
    // which corresponds to orange #ff8000 or thereabouts, and
    // gradually fades through red to black.
    std::array<int, NUM_LEDS> fade;

    // Factor to multiply fade[i] by in each frame. Controls how fast
    // the LEDs fade out. Closer to 1 = slower fade.
    static constexpr float fade_constant = 0.97;

  public:
    Impl();
    void render(CRGB *leds);
};

static inline bool compute135(bool left, bool mid, bool right)
{
    // Make a binary number out of three cells, and use it as a bit
    // index into the 8-bit number 135 that defines the automaton.
    return 1 & (135 >> (4*left + 2*mid + right));
}

static bool rand2()
{
    // A random cell value.
    return rand() > RAND_MAX / 2;
}

Wolfram135::Impl::Impl() {
    for (size_t i = 0; i < NUM_LEDS; i++) {
        // Initialise the whole row to random starting values.
        value[i] = rand2();

        // No fading to begin with.
        fade[i] = 0;
    }

    // But compute a new generation immediately.
    next_frame = 0;
}

void Wolfram135::Impl::render(CRGB *leds) {
    if (next_frame-- <= 0) {
        // Compute the next frame.
        next_frame = delay_frames;

        // Make an extended version of the existing value, with an
        // extra random element at each end, so that we keep injecting
        // entropy and the system never just settles into a pattern by
        // accident.
        std::array<bool, NUM_LEDS + 2> oldvalue;
        for (size_t i = 0; i < NUM_LEDS; i++)
            oldvalue[i+1] = value[i];
        oldvalue[0] = rand2();
        oldvalue[NUM_LEDS+1] = rand2();

        // Compute the new values.
        std::array<bool, NUM_LEDS> newvalue;
        for (size_t i = 0; i < NUM_LEDS; i++)
            newvalue[i] = compute135(
                oldvalue[i], oldvalue[i+1], oldvalue[i+2]);

        // Reset the 'fade' value for any cell that was live and is
        // now dead.
        for (size_t i = 0; i < NUM_LEDS; i++)
            if (value[i] && !newvalue[i])
                fade[i] = 384;

        // Done. Overwrite the live value array.
        value = newvalue;
    }

    // In every frame, render the LEDs and update fade[].
    for (size_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = value[i] ? CRGB(255, 255, 255) :
            CRGB(std::min(fade[i], 255), std::max(fade[i] - 255, 0), 0);
        fade[i] = fade[i] * fade_constant;
    }
}

Wolfram135::Wolfram135() : impl(new Impl) {}
Wolfram135::~Wolfram135() { delete impl; }
void Wolfram135::render(CRGB* leds) { impl->render(leds); }

