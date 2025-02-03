#include "VuMeterLedEffect.hpp"

const uint16_t VuMeterLedEffect::individualLedMasks[9] = {
    LED_NONE,
    LED_1,
    LED_1 | LED_2,
    LED_1 | LED_2 | LED_3,
    LED_1 | LED_2 | LED_3 | LED_4,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7 | LED_8};

VuMeterLedEffect::VuMeterLedEffect(TM1638plus *module) : LedEffect(module)
{
}

VuMeterLedEffect::~VuMeterLedEffect()
{
}

bool VuMeterLedEffect::loop(void)
{
    if (this->refresh())
    {
        this->inc = (this->currentLedIndex == 8) ? false : (this->currentLedIndex == 0 ? true : this->inc);
        uint16_t mask = this->individualLedMasks[currentLedIndex];
        if (inverse)
        {
            mask = 0xFFFF & ~mask;
        }
        this->module->setLEDs(mask);
        this->currentLedIndex = (this->currentLedIndex + (this->inc ? 1 : -1)) % 9;
        if (this->currentLedIndex < 0)
        {
            this->currentLedIndex += 9;
        }
        return (true);
    }
    else
    {
        return (false);
    }
}
