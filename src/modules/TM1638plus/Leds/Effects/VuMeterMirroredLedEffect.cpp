#include "VuMeterMirroredLedEffect.hpp"

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
        this->module->setLEDs(this->inverse ? 0xFF00 : 0);
        if (this->activeLeds == 8)
        {
            this->inc = false;
        }
        else if (this->activeLeds == 0)
        {
            this->inc = true;
        }
        if (activeLeds >= 2)
        {
            this->module->setLED(3, this->inverse ? 0 : 1);
            this->module->setLED(4, this->inverse ? 0 : 1);
            if (activeLeds >= 4)
            {
                this->module->setLED(2, this->inverse ? 0 : 1);
                this->module->setLED(5, this->inverse ? 0 : 1);
                if (activeLeds >= 6)
                {
                    this->module->setLED(1, this->inverse ? 0 : 1);
                    this->module->setLED(6, this->inverse ? 0 : 1);
                    if (activeLeds == 8)
                    {
                        this->module->setLED(0, this->inverse ? 0 : 1);
                        this->module->setLED(7, this->inverse ? 0 : 1);
                    }
                }
            }
        }
        if (this->inc)
        {
            this->activeLeds += 2;
        }
        else
        {
            this->activeLeds -= 2;
        }
        return (true);
    }
    else
    {
        return (false);
    }
}
