#include "ScannerLedEffect.hpp"

const uint16_t ScannerLedEffect::individualLedMasks[14] = {
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_7,
    LED_6,
    LED_5,
    LED_4,
    LED_3,
    LED_2,
};

ScannerLedEffect::ScannerLedEffect(TM1638plus *module) : LedEffect(module, ScannerLedEffect::individualLedMasks, sizeof(ScannerLedEffect::individualLedMasks) / sizeof(ScannerLedEffect::individualLedMasks[0]))
{
}

ScannerLedEffect::~ScannerLedEffect()
{
}
