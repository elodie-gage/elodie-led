#include <vector>
#include "common_led.h"
#include <FastLED.h>
#include <iterator>

class Twinkle {
    private:
    int pos;
    CRGB color;
    int seq;

    public:  
    Twinkle(int pos, CRGB color) : pos(pos), color(color) {
        seq = 0;
    }


    void update() {
        seq+=2;
    }

    bool isDead() {
        return seq >= 500;
    }


    void draw(CRGB* leds) const {
        int fadeFactor = seq < 250 ? seq : 500 - seq; 

        leds[pos] = color.scale8(fadeFactor);
    }
};

void Twinkles::render(CRGB* leds) {
    static std::vector<Twinkle> twinkles;
    

    static const CRGB colours[] = { 
        CRGB(255, 250, 221), 
        CRGB(157, 152, 127), 
        CRGB(83, 81, 64) 
    };

    // Clear LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    int randValue = rand();

    int valP = 80;
    // Spawn new twinkle
    if (randValue % 1000 < valP) {
        CRGB colour = colours[rand() % std::size(colours)];

        int pos = randValue % NUM_LEDS;

        twinkles.emplace_back(pos, colour);
    }

    for (Twinkle& twinkle : twinkles) twinkle.update();

    // Remove twinkles that are dead
    twinkles.erase(
        std::remove_if(twinkles.begin(), twinkles.end(),
                       [](Twinkle twinkle) { return twinkle.isDead(); }),
        twinkles.end());


    // Draw
    for (const Twinkle& twinkle  : twinkles) {
        twinkle.draw(leds);
    }
}
