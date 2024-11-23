#include <vector>
#include "common_led.h"
#include <FastLED.h>

void Snowflakes::render(CRGB* leds) {
    static std::vector<int> snowflakesLeft;
    static std::vector<int> snowflakesRight;
    static const int sideLength = 214;

    // Clear LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Spawn new snowflakes
    if (rand() % 100 < 10) { // 10% chance to spawn a new snowflake
        snowflakesLeft.push_back(0);   // Top of the left side
        snowflakesRight.push_back(0);  // Top of the right side
    }

    // Update snowflake positions
    for (auto& pos : snowflakesLeft) pos++;
    for (auto& pos : snowflakesRight) pos++;

    // Remove snowflakes that have reached the bottom
    snowflakesLeft.erase(
        std::remove_if(snowflakesLeft.begin(), snowflakesLeft.end(),
                       [](int pos) { return pos >= sideLength; }),
        snowflakesLeft.end());

    snowflakesRight.erase(
        std::remove_if(snowflakesRight.begin(), snowflakesRight.end(),
                       [](int pos) { return pos >= sideLength; }),
        snowflakesRight.end());

    // Draw snowflakes
    for (const int pos : snowflakesLeft) {
        leds[sideLength - 1 - pos] = CRGB::White; // Map to the left half
    }
    for (const int pos : snowflakesRight) {
        leds[sideLength + pos] = CRGB::White; // Map to the right half
    }
}
