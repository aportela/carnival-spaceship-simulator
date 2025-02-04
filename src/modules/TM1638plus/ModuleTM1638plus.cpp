#include "ModuleTM1638plus.hpp"

ModuleTM1638plus::ModuleTM1638plus(uint8_t strobePIN, uint8_t clockPIN, uint8_t dioPIN, bool highFreq)
{
    this->module = new TM1638plus(strobePIN, clockPIN, dioPIN, highFreq);
    this->module->displayBegin();
    this->module->brightness(MAX_BRIGHTNESS);
    this->buttons = new Buttons(this->module);
    this->toggleLedEffect();
    this->toggleSevenSegmentEffect();
}

ModuleTM1638plus::~ModuleTM1638plus()
{
    if (this->sevenSegmentDisplayEffect != nullptr)
    {
        delete this->sevenSegmentDisplayEffect;
        this->sevenSegmentDisplayEffect = nullptr;
    }
    if (this->ledEffect != nullptr)
    {
        delete this->ledEffect;
        this->ledEffect = nullptr;
    }
    delete this->buttons;
    this->buttons = nullptr;
    delete this->module;
    this->module = nullptr;
}

void ModuleTM1638plus::toggleSevenSegmentEffect(void)
{
    if (this->sevenSegmentDisplayEffect != nullptr)
    {
        delete this->sevenSegmentDisplayEffect;
        this->sevenSegmentDisplayEffect = nullptr;
    }
    switch (this->currentSevenSegmentEffectType)
    {
    case SEVEN_SEGMENT_EFFECT_TYPE_NONE:
        this->currentSevenSegmentEffectType = SEVEN_SEGMENT_EFFECT_TYPE_RANDOM_WORDS;
        this->sevenSegmentDisplayEffect = new SevenSegmentDisplayEffect(this->module);
        break;
    case SEVEN_SEGMENT_EFFECT_TYPE_RANDOM_WORDS:
        this->currentSevenSegmentEffectType = SEVEN_SEGMENT_EFFECT_TYPE_NONE;
        break;
    default:
        break;
    }
}

void ModuleTM1638plus::toggleSevenSegmentSpeed(void)
{
    if (this->currentSevenSegmentEffectType != SEVEN_SEGMENT_EFFECT_TYPE_NONE)
    {
        this->sevenSegmentDisplayEffect->toggleCurrentSpeed();
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
        this->currentLedEffectType = LED_EFFECT_VUMETER;
        this->ledEffect = new VuMeterLedEffect(this->module);
        break;
    case LED_EFFECT_VUMETER:
        this->currentLedEffectType = LED_EFFECT_VUMETER_MIRRORED;
        this->ledEffect = new VuMeterMirroredLedEffect(this->module);
        break;
    case LED_EFFECT_VUMETER_MIRRORED:
        this->currentLedEffectType = LED_EFFECT_ALTERNATE;
        this->ledEffect = new AlternateLedEffect(this->module);
        break;
    case LED_EFFECT_ALTERNATE:
        this->currentLedEffectType = LED_EFFECT_TYPE_NONE;
        break;
    default:
        break;
    }
}

void ModuleTM1638plus::toggleLedInverseMode(void)
{
    if (this->currentLedEffectType != LED_EFFECT_TYPE_NONE && this->ledEffect != nullptr)
    {
        this->ledEffect->toggleInverse();
    }
}

void ModuleTM1638plus::toggleLedSpeed(void)
{
    if (this->currentLedEffectType != LED_EFFECT_TYPE_NONE && this->ledEffect != nullptr)
    {
        this->ledEffect->toggleCurrentSpeed();
    }
}

bool ModuleTM1638plus::loop()
{
    uint8_t buttons = this->buttons->loop();
    if (buttons == BUTTON_S1)
    {
        this->toggleLedEffect();
    }
    if (buttons == BUTTON_S2)
    {
        this->toggleLedInverseMode();
    }
    if (buttons == BUTTON_S3)
    {
        this->toggleLedSpeed();
    }
    if (buttons == BUTTON_S4)
    {
        this->toggleSevenSegmentEffect();
    }
    if (buttons == BUTTON_S5)
    {
        this->toggleSevenSegmentSpeed();
    }
    if (this->currentLedEffectType != LED_EFFECT_TYPE_NONE && this->ledEffect != nullptr)
    {
        this->ledEffect->loop();
    }
    if (this->currentSevenSegmentEffectType != SEVEN_SEGMENT_EFFECT_TYPE_NONE && this->sevenSegmentDisplayEffect != nullptr)
    {
        this->sevenSegmentDisplayEffect->loop();
    }
    return (false);
}