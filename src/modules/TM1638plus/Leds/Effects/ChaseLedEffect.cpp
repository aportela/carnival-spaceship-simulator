#include "ChaseLedEffect.hpp"

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
        this->module->setLEDs(this->inverse ? 0xFF00 : 0);
        switch (this->LEDposition)
        {
        case 0:
            this->module->setLED(0, this->inverse ? 0 : 1);
            break;
        case 1:
            this->module->setLED(0, this->inverse ? 0 : 1);
            this->module->setLED(1, this->inverse ? 0 : 1);
            break;
        case 2:
            this->module->setLED(0, this->inverse ? 0 : 1);
            this->module->setLED(1, this->inverse ? 0 : 1);
            this->module->setLED(2, this->inverse ? 0 : 1);
            break;
        case 3:
            this->module->setLED(1, this->inverse ? 0 : 1);
            this->module->setLED(2, this->inverse ? 0 : 1);
            this->module->setLED(3, this->inverse ? 0 : 1);
            break;
        case 4:
            this->module->setLED(2, this->inverse ? 0 : 1);
            this->module->setLED(3, this->inverse ? 0 : 1);
            this->module->setLED(4, this->inverse ? 0 : 1);
            break;
        case 5:
            this->module->setLED(3, this->inverse ? 0 : 1);
            this->module->setLED(4, this->inverse ? 0 : 1);
            this->module->setLED(5, this->inverse ? 0 : 1);
            break;
        case 6:
            this->module->setLED(4, this->inverse ? 0 : 1);
            this->module->setLED(5, this->inverse ? 0 : 1);
            this->module->setLED(6, this->inverse ? 0 : 1);
            break;
        case 7:
            this->module->setLED(5, this->inverse ? 0 : 1);
            this->module->setLED(6, this->inverse ? 0 : 1);
            this->module->setLED(7, this->inverse ? 0 : 1);
            break;
        case 8:
            this->module->setLED(6, this->inverse ? 0 : 1);
            this->module->setLED(7, this->inverse ? 0 : 1);
            break;
        case 9:
            this->module->setLED(7, this->inverse ? 0 : 1);
            break;
        }
        this->LEDposition++;
        if (this->LEDposition == 9)
        {
            this->LEDposition = 0;
        }
        return (true);
    }
    else
    {
        return (false);
    }
}
