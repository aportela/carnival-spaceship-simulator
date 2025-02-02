#ifndef TM1638_PLUS_VUMETER_LED_EFFECT_H
#define TM1638_PLUS_VUMETER_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class VuMeterLedEffect : public LedEffect
{
private:
    uint8_t LEDposition = 0;
    bool inc = true;

public:
    VuMeterLedEffect(TM1638plus *module);
    ~VuMeterLedEffect();

    bool loop(void) override;
};

#endif // TM1638_PLUS_VUMETER_LED_EFFECT_H
