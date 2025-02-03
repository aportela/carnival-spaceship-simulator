#ifndef TM1638_PLUS_CHASE_LED_EFFECT_H
#define TM1638_PLUS_CHASE_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class ChaseLedEffect : public LedEffect
{
private:
    static const uint16_t individualLedMasks[11];
    uint8_t currentLedIndex = 0;
    bool inc = true;

public:
    ChaseLedEffect(TM1638plus *module);
    ~ChaseLedEffect();

    bool loop(void) override;
};

#endif // TM1638_PLUS_CHASE_LED_EFFECT_H
