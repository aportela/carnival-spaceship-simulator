#include "ScannerLedEffect.hpp"

ScannerLedEffect::ScannerLedEffect(TM1638plus *module) : LedEffect(module)
{
}

ScannerLedEffect::~ScannerLedEffect()
{
}

bool ScannerLedEffect::loop(void)
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
        this->module->setLED(this->LEDposition, this->inverse ? 0 : 1);
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
