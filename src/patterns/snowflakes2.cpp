#include <vector>
#include "common_led.h"
#include <FastLED.h>


enum Side {
    Left,
    Right
};

class Snowflake {
   private:
   uint16_t accuPos;
   uint16_t accuSpeed;

   public:
   CRGB color;
   Side side;

   
   Snowflake(uint16_t accuPos, uint16_t accuSpeed, CRGB color, Side side) : accuPos(accuPos), accuSpeed(accuSpeed), color(color), side(side) {}

   void moveStep() {
     accuPos += accuSpeed;
   }

   int pos() const {
     return accuPos / 100;
   }
};



void Snowflakes2::render(CRGB* leds) {
    static std::vector<Snowflake> snowflakes;
    static const int sideLength = 214;

    // Clear LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    int randValue = rand();

    int valP = 2;
    // Spawn new snowflakes
    if (randValue % 100 < valP) { // P% chance to spawn a new snowflake
        Side side = randValue % 2 == 0 ? Side::Left : Side::Right;

        snowflakes.emplace_back(0, 100, CRGB::White, side);
    }

    // Update snowflake positions
    for (Snowflake& snowflake : snowflakes) snowflake.moveStep();

    // Remove snowflakes that have reached the bottom
    snowflakes.erase(
        std::remove_if(snowflakes.begin(), snowflakes.end(),
                       [](Snowflake snowflake) { return snowflake.pos() >= sideLength; }),
        snowflakes.end());


    // Draw snowflakes
    for (const Snowflake& snowflake  : snowflakes) {
        int ledIndex;
        switch(snowflake.side) {
            case Side::Left:  ledIndex = sideLength - 1 - snowflake.pos(); break;
            case Side::Right: ledIndex = sideLength + snowflake.pos(); break;
        }

        leds[ledIndex] = snowflake.color;
    }
}
