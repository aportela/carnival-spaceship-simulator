#include "ModuleTM1638plus.hpp"

ModuleTM1638plus::ModuleTM1638plus(uint8_t strobePIN, uint8_t clockPIN, uint8_t dioPIN, bool highFreq)
{
    this->module = new TM1638plus(strobePIN, clockPIN, dioPIN, highFreq);
    this->module->displayBegin();
    this->module->brightness(MAX_BRIGHTNESS);
    this->buttons = new Buttons(this->module);
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

void ModuleTM1638plus::toggleLedEffect(void)
{
    this->module->setLEDs(0);
    if (this->ledEffect != nullptr)
    {
        delete this->ledEffect;
        this->ledEffect = nullptr;
    }
    switch (this->currentLedEffectType)
    {
    case LED_EFFECT_TYPE_NONE:
        this->currentLedEffectType = LED_EFFECT_TYPE_SCANNER;
        this->ledEffect = new ScannerLedEffect(this->module);
        break;
    case LED_EFFECT_TYPE_SCANNER:
        this->currentLedEffectType = LED_EFFECT_TYPE_CHASE;
        this->ledEffect = new ChaseLedEffect(this->module);
        break;
    case LED_EFFECT_TYPE_CHASE:
        this->currentLedEffectType = LED_EFFECT_TYPE_NONE;
        break;
    default:
        break;
    }
}

bool ModuleTM1638plus::loop()
{
    uint8_t buttons = this->buttons->loop();
    if (buttons == BUTTON_S1)
    {
        this->toggleLedEffect();
    }
    if (this->currentLedEffectType != LED_EFFECT_TYPE_NONE && this->ledEffect != nullptr)
    {
        this->ledEffect->loop();
    }
    return (false);
}