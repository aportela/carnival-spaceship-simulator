#ifndef TM1638_PLUS_CHASE_LED_EFFECT_H
#define TM1638_PLUS_CHASE_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class ChaseLedEffect : public LedEffect
{
private:
    static const uint16_t individualLedMasks[11];

public:
    ChaseLedEffect(TM1638plus *module);
    ~ChaseLedEffect();
};

#endif // TM1638_PLUS_CHASE_LED_EFFECT_H
