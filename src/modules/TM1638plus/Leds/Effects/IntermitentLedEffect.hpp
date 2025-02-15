#ifndef TM1638_PLUS_INTERMITENT_LED_EFFECT_H
#define TM1638_PLUS_INTERMITENT_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class IntermitentLedEffect : public LedEffect
{
private:
    static const uint16_t individualLedMasks[];

public:
    IntermitentLedEffect(TM1638plus *module, uint16_t msDelay = DEFAULT_LED_MS_DELAY);
    ~IntermitentLedEffect();
};

#endif // TM1638_PLUS_INTERMITENT_LED_EFFECT_H
