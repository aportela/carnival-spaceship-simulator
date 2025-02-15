#ifndef TM1638_PLUS_ALTERNATE_LED_EFFECT_H
#define TM1638_PLUS_ALTERNATE_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class AlternateLedEffect : public LedEffect
{
private:
    static const uint16_t individualLedMasks[];

public:
    AlternateLedEffect(TM1638plus *module, uint16_t msDelay = DEFAULT_LED_MS_DELAY);
    ~AlternateLedEffect();
};

#endif // TM1638_PLUS_ALTERNATE_LED_EFFECT_H
