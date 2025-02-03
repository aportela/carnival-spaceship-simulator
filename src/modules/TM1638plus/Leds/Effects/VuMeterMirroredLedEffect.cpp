#include "VuMeterMirroredLedEffect.hpp"

const uint16_t VuMeterMirroredLedEffect::individualLedMasks[5] = {
    LED_NONE,
    LED_4 | LED_5,
    LED_3 | LED_4 | LED_5 | LED_6,
    LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7,
    LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7 | LED_8,
};

VuMeterMirroredLedEffect::VuMeterMirroredLedEffect(TM1638plus *module) : LedEffect(module)
{
}

VuMeterMirroredLedEffect::~VuMeterMirroredLedEffect()
{
}

bool VuMeterMirroredLedEffect::loop(void)
{
    if (this->refresh())
    {
        this->inc = (this->currentLedIndex == 4) ? false : (this->currentLedIndex == 0 ? true : this->inc);
        uint16_t mask = this->individualLedMasks[currentLedIndex];
        if (inverse)
        {
            mask = 0xFFFF & ~mask;
        }
        this->module->setLEDs(mask);
        this->currentLedIndex = (this->currentLedIndex + (this->inc ? 1 : -1)) % 5;
        if (this->currentLedIndex < 0)
        {
            this->currentLedIndex += 5;
        }
        return (true);
    }
    else
    {
        return (false);
    }
}
