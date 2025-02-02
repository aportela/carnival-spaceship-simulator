#include "VuMeterLedEffect.hpp"

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
        this->module->setLEDs(this->inverse ? 0xFF00 : 0);
        if (this->LEDposition == 7)
        {
            this->inc = false;
        }
        else if (this->LEDposition == 0)
        {
            this->inc = true;
        }
        for (uint8_t i = 0; i <= this->LEDposition; i++)
        {
            this->module->setLED(i, this->inverse ? 0 : 1);
        }
        if (this->inc)
        {
            this->LEDposition++;
        }
        else
        {
            this->LEDposition--;
        }
        return (true);
    }
    else
    {
        return (false);
    }
}
