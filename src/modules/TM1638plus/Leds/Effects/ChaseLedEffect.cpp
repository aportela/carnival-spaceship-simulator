#include "ChaseLedEffect.hpp"

const uint16_t ChaseLedEffect::individualLedMasks[11] = {LED_NONE, LED_1, LED_1 | LED_2, LED_1 | LED_2 | LED_3, LED_2 | LED_3 | LED_4, LED_3 | LED_4 | LED_5, LED_4 | LED_5 | LED_6, LED_5 | LED_6 | LED_7, LED_6 | LED_7 | LED_8, LED_7 | LED_8, LED_8};

ChaseLedEffect::ChaseLedEffect(TM1638plus *module) : LedEffect(module)
{
}

ChaseLedEffect::~ChaseLedEffect()
{
}

bool ChaseLedEffect::loop(void)
{
    if (this->refresh())
    {
        if (this->currentLedIndex >= 11)
        {
            this->currentLedIndex = 0;
        }
        uint16_t mask = this->individualLedMasks[currentLedIndex];
        if (inverse)
        {
            mask = 0xFFFF & ~mask;
        }
        this->module->setLEDs(mask);
        this->currentLedIndex++;
        return (true);
    }
    else
    {
        return (false);
    }
}
