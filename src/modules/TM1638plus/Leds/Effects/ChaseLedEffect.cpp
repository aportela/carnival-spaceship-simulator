#include "ChaseLedEffect.hpp"

const uint16_t ChaseLedEffect::individualLedMasks[] = {
    LED_NONE,
    LED_1,
    LED_1 | LED_2,
    LED_1 | LED_2 | LED_3,
    LED_2 | LED_3 | LED_4,
    LED_3 | LED_4 | LED_5,
    LED_4 | LED_5 | LED_6,
    LED_5 | LED_6 | LED_7,
    LED_6 | LED_7 | LED_8,
    LED_7 | LED_8,
    LED_8,
};

ChaseLedEffect::ChaseLedEffect(TM1638plus *module, uint16_t msDelay) : LedEffect(module, ChaseLedEffect::individualLedMasks, sizeof(ChaseLedEffect::individualLedMasks) / sizeof(ChaseLedEffect::individualLedMasks[0]), msDelay)
{
}

ChaseLedEffect::~ChaseLedEffect()
{
}
