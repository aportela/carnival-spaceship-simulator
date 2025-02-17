#include "MorseLedEffect.hpp"

const uint16_t MorseLedEffect::letterSLedMasks[] = {
    LED_NONE,
    LED_1 | LED_2 | LED_3 | LED_6 | LED_7 | LED_8,
    LED_NONE,
    LED_1 | LED_2 | LED_3 | LED_6 | LED_7 | LED_8,
    LED_NONE,
    LED_1 | LED_2 | LED_3 | LED_6 | LED_7 | LED_8,
};

const uint16_t MorseLedEffect::letterOLedMasks[] = {
    LED_NONE,
    LED_3 | LED_4 | LED_5 | LED_6,
    LED_NONE,
    LED_3 | LED_4 | LED_5 | LED_6,
    LED_NONE,
    LED_3 | LED_4 | LED_5 | LED_6,
};

const uint16_t MorseLedEffect::emptyLetterLedMasks[] = {};

MorseLedEffect::MorseLedEffect(TM1638plus *module, uint16_t msDelay, const char letter)
    : LedEffect(
          module,
          (letter == 'S') ? letterSLedMasks : (letter == 'O') ? letterOLedMasks
                                                              : emptyLetterLedMasks,
          (letter == 'S') ? sizeof(letterSLedMasks) / sizeof(letterSLedMasks[0]) : (letter == 'O') ? sizeof(letterOLedMasks) / sizeof(letterOLedMasks[0])
                                                                                                   : 0,
          msDelay)
{
}
MorseLedEffect::~MorseLedEffect()
{
}
