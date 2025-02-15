#include "IntermitentLedEffect.hpp"

const uint16_t IntermitentLedEffect::individualLedMasks[] = {
    LED_NONE,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7 | LED_8,
};

IntermitentLedEffect::IntermitentLedEffect(TM1638plus *module, uint16_t msDelay) : LedEffect(module, IntermitentLedEffect::individualLedMasks, sizeof(IntermitentLedEffect::individualLedMasks) / sizeof(AlternateLedEffect::individualLedMasks[0]), msDelay)
{
}

IntermitentLedEffect::~IntermitentLedEffect()
{
}
