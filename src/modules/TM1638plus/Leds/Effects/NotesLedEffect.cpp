#include "NotesLedEffect.hpp"

const uint16_t NotesLedEffect::individualLedMasks[] = {
    LED_6 | LED_7,
    LED_NONE,
    LED_NONE,
    LED_7 | LED_8,
    LED_NONE,
    LED_NONE,
    LED_5 | LED_6,
    LED_NONE,
    LED_NONE,
    LED_1 | LED_2 | LED_3,
    LED_1 | LED_2 | LED_3,
    LED_NONE,
    LED_NONE,
    LED_3 | LED_4 | LED_5,
    LED_3 | LED_4 | LED_5,
    LED_NONE,
    LED_NONE,
};

NotesLedEffect::NotesLedEffect(TM1638plus *module, uint16_t msDelay) : LedEffect(module, NotesLedEffect::individualLedMasks, sizeof(NotesLedEffect::individualLedMasks) / sizeof(NotesLedEffect::individualLedMasks[0]), msDelay)
{
}

NotesLedEffect::~NotesLedEffect()
{
}
