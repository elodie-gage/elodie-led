#include <vector>
#include "common_led.h"
#include <FastLED.h>
#include <iterator>

class Twinkle {

    private:

    int pos;
    CRGB color;
    int seq;
    int scaleUpRate;
    int scaleDownRate;
    int scaleDownFromSeq;
    int deathSeq;

    public:  

    Twinkle(int randValue) {
        seq = 0;

        pos = randValue % NUM_LEDS;

        int colorChoice = randValue % 10;
        
        if (colorChoice < 7) {
            color = CRGB(255, 255, 255);  // white
            scaleUpRate = 5;
            scaleDownRate = 5;
        } else if (colorChoice < 8) {
            color = CRGB(255, 0, 0); // redish
            scaleUpRate = 10;
            scaleDownRate = 10;
        } else {
            color = CRGB(245, 239, 66); // gold
            scaleUpRate = 2;
            scaleDownRate = 2;
        }

        scaleDownFromSeq = 255 / scaleUpRate;
        deathSeq = scaleDownFromSeq + (scaleUpRate * scaleDownFromSeq) / scaleDownRate;
    }

    void update() {
        seq++;
    }

    bool isDead() {
        return seq >= deathSeq;
    }

    void draw(CRGB* leds) const {
        int fadeFactor = seq < scaleDownFromSeq 
            ? seq * scaleUpRate 
            : (scaleDownFromSeq * scaleUpRate) - ((seq - scaleDownFromSeq) * scaleDownRate);

        if (fadeFactor > 0) {
            leds[pos] = color.scale8(fadeFactor);
        }
    }
};

void Twinkles::render(CRGB* leds) {
    static std::vector<Twinkle> twinkles;
    

    // Clear LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    int randValue = rand();

    int valP = 80;
    // Spawn new twinkle
    if (randValue % 1000 < valP) {

        twinkles.emplace_back(randValue);
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
