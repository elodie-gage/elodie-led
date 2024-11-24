#include <vector>
#include "common_led.h"
#include <FastLED.h>


class Snowflake {
   public:
   uint16_t accuPos;
   uint16_t accuSpeed;
   CRGB color;
   
   Snowflake(uint16_t accuPos, uint16_t accuSpeed, CRGB color) : accuPos(accuPos), accuSpeed(accuSpeed), color(color) {}

   void moveStep() {
     accuPos += accuSpeed;
   }

   int pos() const {
     return accuPos / 100;
   }
};



void Snowflakes2::render(CRGB* leds) {
    static std::vector<Snowflake> snowflakesLeft;
    static std::vector<Snowflake> snowflakesRight;
    static const int sideLength = 214;

    // Clear LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    int valP = 2;
    // Spawn new snowflakes
    if (rand() % 100 < valP) { // P% chance to spawn a new snowflake
        snowflakesLeft.emplace_back(0, 100, CRGB::White);  // Top of the right side
    }
    if (rand() % 100 < valP) { // P% chance to spawn a new snowflake
        snowflakesRight.emplace_back(0, 100, CRGB::White);  // Top of the right side
    }

    // Update snowflake positions
    for (Snowflake& snowflake : snowflakesLeft) snowflake.moveStep();
    for (Snowflake& snowflake : snowflakesRight) snowflake.moveStep();

    // Remove snowflakes that have reached the bottom
    snowflakesLeft.erase(
        std::remove_if(snowflakesLeft.begin(), snowflakesLeft.end(),
                       [](Snowflake snowflake) { return snowflake.pos() >= sideLength; }),
        snowflakesLeft.end());

    snowflakesRight.erase(
        std::remove_if(snowflakesRight.begin(), snowflakesRight.end(),
                       [](Snowflake snowflake) { return snowflake.pos() >= sideLength; }),
        snowflakesRight.end());

    // Draw snowflakes
    for (const Snowflake& snowflake  : snowflakesLeft) {
        leds[sideLength - 1 - snowflake.pos()] = CRGB::White; // Map to the left half
    }
    for (const Snowflake& snowflake : snowflakesRight) {
        leds[sideLength + snowflake.pos()] = CRGB::White; // Map to the right half
    }
}
