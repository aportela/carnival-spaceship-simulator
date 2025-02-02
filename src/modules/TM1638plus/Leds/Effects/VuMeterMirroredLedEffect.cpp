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
        this->module->setLEDs(0);
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
            this->module->setLED(3, 1);
            this->module->setLED(4, 1);
            if (activeLeds >= 4)
            {
                this->module->setLED(2, 1);
                this->module->setLED(5, 1);
                if (activeLeds >= 6)
                {
                    this->module->setLED(1, 1);
                    this->module->setLED(6, 1);
                    if (activeLeds == 8)
                    {
                        this->module->setLED(0, 1);
                        this->module->setLED(7, 1);
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
