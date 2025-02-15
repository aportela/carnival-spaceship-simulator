#include "ModuleTM1638plus.hpp"

ModuleTM1638plus::ModuleTM1638plus(uint8_t strobePIN, uint8_t clockPIN, uint8_t dioPIN, bool highFreq)
{
    this->module = new TM1638plus(strobePIN, clockPIN, dioPIN, highFreq);
    this->module->displayBegin();
    this->module->brightness(MAX_BRIGHTNESS);
    this->buttons = new TM1638plusButtons(this->module);
    // this->toggleLedEffect();
    //  this->toggleSevenSegmentEffect();
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
    /*
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
    */
    if (this->ef != nullptr)
    {
        delete this->ef;
        this->ef = nullptr;
    }
    if (this->mf != nullptr)
    {
        delete this->mf;
        this->mf = nullptr;
    }
    // this->ef = new SimpleTextEffect(this->module, "AA BB CC", true, 500, 0, 7);
    /*
    const char *frames[] = {
        "S.O.S.     ",
        " S.O.S.    ",
        "  S.O.S.   ",
        "   S.O.S.  ",
        "    S.O.S. ",
        "     S.O.S.",
        "    S.O.S. ",
        "   S.O.S.  ",
        "  S.O.S.   ",
        " S.O.S.    ",
        "S.O.S.     ",
        "CASA    ",
        " CASA   ",
        "  CASA  ",
        "   CASA ",
        "    CASA",
        "   CASA ",
        "  CASA  ",
        " CASA   ",
        "CASA    ",
        "CEAVA5  ",
        " CEAVA5 ",
        "  CEAVA5",
        " CEAVA5 ",
        "CEAVA5  ",
        " CEAVA5 ",
        "  CEAVA5",
        " CEAVA5 ",
        "CEAVA5  ",
    };
    */
    const char *frames[] = {
        "UFO     ",
        " UFO    ",
        "  UFO   ",
        "   UFO  ",
        "    UFO ",
        "     UFO",
        "    UFO ",
        "   UFO  ",
        "  UFO   ",
        " UFO    ",
    };
    this->mf = new MultiFrameTextEffect(this->module, frames, sizeof(frames) / sizeof(frames[0]), 200, 0);
}

void ModuleTM1638plus::toggleSevenSegmentSpeed(void)
{
    if (this->currentSevenSegmentEffectType != SEVEN_SEGMENT_EFFECT_TYPE_NONE)
    {
        this->sevenSegmentDisplayEffect->toggleCurrentSpeed();
    }
}

void ModuleTM1638plus::setLedEffect(LED_EFFECT_TYPE effect, uint16_t msDelay)
{
    this->module->setLEDs(0);
    if (this->ledEffect != nullptr)
    {
        delete this->ledEffect;
        this->ledEffect = nullptr;
    }
    switch (effect)
    {
    case LED_EFFECT_TYPE_SCANNER:
        this->ledEffect = new ScannerLedEffect(this->module, msDelay);
        break;
    case LED_EFFECT_TYPE_CHASE:
        this->ledEffect = new ChaseLedEffect(this->module, msDelay);
        break;
    case LED_EFFECT_TYPE_VUMETER:
        this->ledEffect = new VuMeterLedEffect(this->module, msDelay);
        break;
    case LED_EFFECT_TYPE_VUMETER_MIRRORED:
        this->ledEffect = new VuMeterMirroredLedEffect(this->module, msDelay);
        break;
    case LED_EFFECT_TYPE_ALTERNATE:
        this->ledEffect = new AlternateLedEffect(this->module, msDelay);
        break;
    case LED_EFFECT_TYPE_INTERMITENT:
        this->ledEffect = new IntermitentLedEffect(this->module, msDelay);
        break;
    default:
        break;
    }
    this->currentLedEffectType = effect;
}

void ModuleTM1638plus::toggleLedInverseMode(void)
{
    if (this->currentLedEffectType != LED_EFFECT_TYPE_NONE && this->ledEffect != nullptr)
    {
        this->ledEffect->toggleInverse();
    }
}

void ModuleTM1638plus::displayTextOnLeft7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->textEffectLeft != nullptr)
    {
        delete this->textEffectLeft;
        this->textEffectLeft = nullptr;
    }
    this->textEffectLeft = new SimpleTextEffect(this->module, text, blink, blinkTimeout, 0, 4);
}

void ModuleTM1638plus::displayTextOnRight7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->textEffectRight != nullptr)
    {
        delete this->textEffectRight;
        this->textEffectRight = nullptr;
    }
    this->textEffectRight = new SimpleTextEffect(this->module, text, blink, blinkTimeout, 4, 8);
}

void ModuleTM1638plus::displayTextOnFull7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->textEffectRight != nullptr)
    {
        delete this->textEffectRight;
        this->textEffectRight = nullptr;
    }
    this->textEffectRight = new SimpleTextEffect(this->module, text, blink, blinkTimeout, 0, 8);
}

TM1638plusBUTTON ModuleTM1638plus::checkPressedButton()
{
    uint8_t pressedButtons = this->buttons->loop();
    TM1638plusBUTTON pressedButton = TM1638plusBUTTON_NONE;

    if (pressedButtons == TM1638plusBUTTON_S1)
    {
        pressedButton = TM1638plusBUTTON_S1;
    }
    if (pressedButtons == TM1638plusBUTTON_S2)
    {
        pressedButton = TM1638plusBUTTON_S2;
    }
    if (pressedButtons == TM1638plusBUTTON_S3)
    {
        pressedButton = TM1638plusBUTTON_S3;
    }
    if (pressedButtons == TM1638plusBUTTON_S4)
    {
        pressedButton = TM1638plusBUTTON_S4;
    }
    if (pressedButtons == TM1638plusBUTTON_S5)
    {
        pressedButton = TM1638plusBUTTON_S5;
    }
    if (pressedButtons == TM1638plusBUTTON_S6)
    {
        pressedButton = TM1638plusBUTTON_S6;
    }
    if (pressedButtons == TM1638plusBUTTON_S7)
    {
        pressedButton = TM1638plusBUTTON_S7;
    }
    if (pressedButtons == TM1638plusBUTTON_S8)
    {
        pressedButton = TM1638plusBUTTON_S8;
    }
    return (pressedButton);
}

void ModuleTM1638plus::loop(void)
{
    if (this->currentLedEffectType != LED_EFFECT_TYPE_NONE && this->ledEffect != nullptr)
    {
        this->ledEffect->loop();
    }
    if (this->currentSevenSegmentEffectType != SEVEN_SEGMENT_EFFECT_TYPE_NONE && this->sevenSegmentDisplayEffect != nullptr)
    {
        // this->sevenSegmentDisplayEffect->loop();
    }
    if (this->ef != nullptr)
    {
        // this->ef->loop();
    }
    if (this->mf != nullptr)
    {
        this->mf->loop();
    }
    if (this->textEffectLeft != nullptr)
    {
        this->textEffectLeft->loop();
    }
    if (this->textEffectRight != nullptr)
    {
        this->textEffectRight->loop();
    }
}
