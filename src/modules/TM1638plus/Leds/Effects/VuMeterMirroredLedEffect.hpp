#ifndef TM1638_PLUS_VUMETER_MIRRORED_LED_EFFECT_H
#define TM1638_PLUS_VUMETER_MIRRORED_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class VuMeterMirroredLedEffect : public LedEffect
{
private:
    uint8_t activeLeds = 0;
    bool inc = true;

public:
    VuMeterMirroredLedEffect(TM1638plus *module);
    ~VuMeterMirroredLedEffect();

    bool loop(void) override;
};

#endif // TM1638_PLUS_VUMETER_MIRRORED_LED_EFFECT_H
