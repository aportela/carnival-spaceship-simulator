#ifndef TM1638_PLUS_CHASE_LED_EFFECT_H
#define TM1638_PLUS_CHASE_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

#define DEFAULT_LED_ANIMATION_DELAY 64

class ChaseLedEffect : public LedEffect
{
private:
    uint8_t LEDposition = 0;
    bool inc = true;
    uint8_t delayMS = DEFAULT_LED_ANIMATION_DELAY;

public:
    ChaseLedEffect(TM1638plus *module);
    ~ChaseLedEffect();

    bool loop(void) override;
};

#endif // TM1638_PLUS_CHASE_LED_EFFECT_H
