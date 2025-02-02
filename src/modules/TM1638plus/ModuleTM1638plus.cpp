#include "ModuleTM1638plus.hpp"

ModuleTM1638plus::ModuleTM1638plus(uint8_t strobePIN, uint8_t clockPIN, uint8_t dioPIN, bool highFreq)
{
    this->module = new TM1638plus(strobePIN, clockPIN, dioPIN, highFreq);
    this->module->displayBegin();
    this->module->brightness(MAX_BRIGHTNESS);
    this->buttons = new Buttons(this->module);
    switch (this->currentLedEffectType)
    {
    case LED_EFFECT_TYPE_SCANNER:
        this->ledEffect = new ScannerLedEffect(this->module);
        break;
    case LED_EFFECT_TYPE_CHASE:
        this->ledEffect = new ChaseLedEffect(this->module);
        break;
    default:
        break;
    }
}

ModuleTM1638plus::~ModuleTM1638plus()
{
    delete this->buttons;
    this->buttons = nullptr;
    delete this->module;
    this->module = nullptr;
    if (this->ledEffect != nullptr)
    {
        delete this->ledEffect;
        this->ledEffect = nullptr;
    }
}

bool ModuleTM1638plus::loop()
{
    this->buttons->loop();
    if (this->ledEffect != nullptr)
    {
        this->ledEffect->loop();
    }
    return (false);
}