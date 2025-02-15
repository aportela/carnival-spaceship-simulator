#ifndef TM1638_PLUS_VUMETER_MIRRORED_LED_EFFECT_H
#define TM1638_PLUS_VUMETER_MIRRORED_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class VuMeterMirroredLedEffect : public LedEffect
{
private:
    static const uint16_t individualLedMasks[];

public:
    VuMeterMirroredLedEffect(TM1638plus *module, uint16_t msDelay = DEFAULT_LED_MS_DELAY);
    ~VuMeterMirroredLedEffect();
};

#endif // TM1638_PLUS_VUMETER_MIRRORED_LED_EFFECT_H
