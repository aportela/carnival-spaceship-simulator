#include "VuMeterLedEffect.hpp"

const uint16_t VuMeterLedEffect::individualLedMasks[] = {
    LED_NONE,
    LED_1,
    LED_1 | LED_2,
    LED_1 | LED_2 | LED_3,
    LED_1 | LED_2 | LED_3 | LED_4,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7 | LED_8,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5,
    LED_1 | LED_2 | LED_3 | LED_4,
    LED_1 | LED_2 | LED_3,
    LED_1 | LED_2,
    LED_1,
};

VuMeterLedEffect::VuMeterLedEffect(TM1638plus *module, uint16_t msDelay) : LedEffect(module, VuMeterLedEffect::individualLedMasks, sizeof(VuMeterLedEffect::individualLedMasks) / sizeof(VuMeterLedEffect::individualLedMasks[0]), msDelay)
{
}

VuMeterLedEffect::~VuMeterLedEffect()
{
}
