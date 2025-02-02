#include "ChaseLedEffect.hpp"

ChaseLedEffect::ChaseLedEffect(TM1638plus *module) : LedEffect(module)
{
}

ChaseLedEffect::~ChaseLedEffect()
{
}

bool ChaseLedEffect::loop(void)
{
    this->module->setLEDs(0);
    switch (this->LEDposition)
    {
    case 0:
        this->module->setLED(0, 1);
        break;
    case 1:
        this->module->setLED(0, 1);
        this->module->setLED(1, 1);
        break;
    case 2:
        this->module->setLED(0, 1);
        this->module->setLED(1, 1);
        this->module->setLED(2, 1);
        break;
    case 3:
        this->module->setLED(1, 1);
        this->module->setLED(2, 1);
        this->module->setLED(3, 1);
        break;
    case 4:
        this->module->setLED(2, 1);
        this->module->setLED(3, 1);
        this->module->setLED(4, 1);
        break;
    case 5:
        this->module->setLED(3, 1);
        this->module->setLED(4, 1);
        this->module->setLED(5, 1);
        break;
    case 6:
        this->module->setLED(4, 1);
        this->module->setLED(5, 1);
        this->module->setLED(6, 1);
        break;
    case 7:
        this->module->setLED(5, 1);
        this->module->setLED(6, 1);
        this->module->setLED(7, 1);
        break;
    case 8:
        this->module->setLED(6, 1);
        this->module->setLED(7, 1);
        break;
    case 9:
        this->module->setLED(7, 1);
        break;
    }
    this->LEDposition++;
    if (this->LEDposition == 9)
    {
        this->LEDposition = 0;
    }
    delay(this->delayMS);
    return (false);
}
