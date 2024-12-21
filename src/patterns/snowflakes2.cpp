#include <vector>
#include "common_led.h"
#include <FastLED.h>
#include <iterator>
#include <algorithm>

enum Side {
    Left,
    Right
};

static const int sideLength = 214;

bool inLedRange(int index) {
    return index >= 0 && index < NUM_LEDS;
}

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

   void draw(CRGB* leds) const {
        int pos1 = accuPos / 100;
        int pos2 = pos1+1;

        uint8_t scale2 = (256 * (accuPos % 100)) / 100;
        uint8_t scale1 = 256 - scale2;

        int ledIndex1;
        int ledIndex2;
        switch(side) {
            case Side::Left:  ledIndex1 = sideLength - 1 - pos(); ledIndex2=ledIndex1-1; break;
            case Side::Right: ledIndex1 = sideLength + pos(); ledIndex2=ledIndex1+1; break;
        };

        if (inLedRange(ledIndex1)) {
            leds[ledIndex1] = color.scale8(scale1);
        }
        if (inLedRange(ledIndex2)) {
            leds[ledIndex2] = color.scale8(scale2);
        }
   }

};

void Snowflakes2::render(CRGB* leds) {
    static std::vector<Snowflake> snowflakes;
    

    static const CRGB snowflakeColours[] = { 
        CRGB(182, 129, 37), // 
        // CRGB(255, 247, 21),
        //CRGB(158, 32, 0),
        CRGB(255, 255, 230)
    };

    // Clear LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    int randValue = rand();

    int valP = 30;
    // Spawn new snowflakes
    if (randValue % 1000 < valP) { // P% chance to spawn a new snowflake
        Side side = randValue % 2 == 0 ? Side::Left : Side::Right;

        int speed = 12 + rand() % 12;

        CRGB colour = snowflakeColours[rand() % std::size(snowflakeColours)];

        snowflakes.emplace_back(0, speed, colour, side);
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
        snowflake.draw(leds);
    }
}
