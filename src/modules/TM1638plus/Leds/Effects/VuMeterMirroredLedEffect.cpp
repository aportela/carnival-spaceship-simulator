#include "VuMeterMirroredLedEffect.hpp"

const uint16_t VuMeterMirroredLedEffect::individualLedMasks[] = {
    LED_NONE,
    LED_4 | LED_5,
    LED_3 | LED_4 | LED_5 | LED_6,
    LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7 | LED_8,
    LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7,
    LED_3 | LED_4 | LED_5 | LED_6,
    LED_4 | LED_5,
};

VuMeterMirroredLedEffect::VuMeterMirroredLedEffect(TM1638plus *module) : LedEffect(module, VuMeterMirroredLedEffect::individualLedMasks, sizeof(VuMeterMirroredLedEffect::individualLedMasks) / sizeof(VuMeterMirroredLedEffect::individualLedMasks[0]))
{
}

VuMeterMirroredLedEffect::~VuMeterMirroredLedEffect()
{
}
