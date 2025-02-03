#include "AlternateLedEffect.hpp"

const uint16_t AlternateLedEffect::individualLedMasks[] = {
    LED_1 | LED_3 | LED_5 | LED_7,
    LED_2 | LED_4 | LED_6 | LED_8,
};

AlternateLedEffect::AlternateLedEffect(TM1638plus *module) : LedEffect(module, AlternateLedEffect::individualLedMasks, sizeof(AlternateLedEffect::individualLedMasks) / sizeof(AlternateLedEffect::individualLedMasks[0]))
{
}

AlternateLedEffect::~AlternateLedEffect()
{
}
