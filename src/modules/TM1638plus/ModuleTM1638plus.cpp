#include "ModuleTM1638plus.hpp"
#include "../../CommonDefines.hpp"

ModuleTM1638plus::ModuleTM1638plus(uint8_t strobePIN, uint8_t clockPIN, uint8_t dioPIN, bool highFreq)
{
    this->modulePtr = new TM1638plus(strobePIN, clockPIN, dioPIN, highFreq);
    this->modulePtr->displayBegin();
    this->modulePtr->brightness(MAX_BRIGHTNESS);
    this->buttonsPtr = new TM1638plusButtons(this->modulePtr);
}

ModuleTM1638plus::~ModuleTM1638plus()
{
    if (this->currentLedAnimationPtr != nullptr)
    {
        delete this->currentLedAnimationPtr;
        this->currentLedAnimationPtr = nullptr;
    }
    if (this->SevenSegmentLeftBlock != nullptr)
    {
        delete this->SevenSegmentLeftBlock;
        this->SevenSegmentLeftBlock = nullptr;
    }
    if (this->SevenSegmentRightBlock != nullptr)
    {
        delete this->SevenSegmentRightBlock;
        this->SevenSegmentRightBlock = nullptr;
    }
    if (this->SevenSegmentBothBlocks != nullptr)
    {
        delete this->SevenSegmentBothBlocks;
        this->SevenSegmentBothBlocks = nullptr;
    }
    delete this->buttonsPtr;
    this->buttonsPtr = nullptr;
    delete this->modulePtr;
    this->modulePtr = nullptr;
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
        this->sevenSegmentDisplayEffect = new SevenSegmentDisplayEffect(this->modulePtr);
        break;
    case SEVEN_SEGMENT_EFFECT_TYPE_RANDOM_WORDS:
        this->currentSevenSegmentEffectType = SEVEN_SEGMENT_EFFECT_TYPE_NONE;
        break;
    default:
        break;
    }
    */
    /*
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
         */
    // this->ef = new SimpleTextEffect(this->modulePtr, "AA BB CC", true, 500, 0, 7);
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
    this->mf = new MultiFrameTextEffect(this->modulePtr, frames, sizeof(frames) / sizeof(frames[0]), 200, 0);
        */
}

void ModuleTM1638plus::toggleLedAnimation(uint16_t msDelay)
{
    switch (this->currentLedAnimationType)
    {
    case LED_ANIMATION_TYPE_NONE:
        this->setLedAnimation(LED_ANIMATION_TYPE_SCANNER, msDelay);
        break;
    case LED_ANIMATION_TYPE_SCANNER:
        this->setLedAnimation(LED_ANIMATION_TYPE_CHASE, msDelay);
        break;
    case LED_ANIMATION_TYPE_CHASE:
        this->setLedAnimation(LED_ANIMATION_TYPE_VUMETER, msDelay);
        break;
    case LED_ANIMATION_TYPE_VUMETER:
        this->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, msDelay);
        break;
    case LED_ANIMATION_TYPE_VUMETER_MIRRORED:
        this->setLedAnimation(LED_ANIMATION_TYPE_ALTERNATE, msDelay);
        break;
    case LED_ANIMATION_TYPE_ALTERNATE:
        this->setLedAnimation(LED_ANIMATION_TYPE_INTERMITENT, msDelay);
        break;
    case LED_ANIMATION_TYPE_INTERMITENT:
        this->setLedAnimation(LED_ANIMATION_TYPE_NONE, msDelay);
        break;
    default:
        this->setLedAnimation(LED_ANIMATION_TYPE_NONE, msDelay);
        break;
    }
}

LED_ANIMATION_TYPE ModuleTM1638plus::getCurrentLedAnimation(void)
{
    return (this->currentLedAnimationType);
}

void ModuleTM1638plus::setLedAnimation(LED_ANIMATION_TYPE animation, uint16_t msDelay)
{
    if (animation != this->currentLedAnimationType)
    {
        this->modulePtr->setLEDs(0);
        if (this->currentLedAnimationPtr != nullptr)
        {
            delete this->currentLedAnimationPtr;
            this->currentLedAnimationPtr = nullptr;
        }
        switch (animation)
        {
        case LED_ANIMATION_TYPE_SCANNER:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => SCANNER (delay %f ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new ScannerLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_CHASE:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => CHASE (delay %f ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new ChaseLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_VUMETER:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => VUMETER (delay %f ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new VuMeterLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_VUMETER_MIRRORED:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => VUMETER MIRRORED (delay %f ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new VuMeterMirroredLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_ALTERNATE:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => ALTERNATE (delay %f ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new AlternateLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_INTERMITENT:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => INTERMITENT (delay %f ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new IntermitentLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_MORSE_LETTER_S:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => morse letter S (delay %f ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new MorseLedEffect(this->modulePtr, msDelay, 'S');
            break;
        case LED_ANIMATION_TYPE_MORSE_LETTER_O:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => morse letter O (delay %f ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new MorseLedEffect(this->modulePtr, msDelay, 'O');
            break;
        default:
            break;
        }
        this->currentLedAnimationType = animation;
    }
    else
    {
        if (animation != LED_ANIMATION_TYPE_NONE && this->currentLedAnimationPtr != nullptr)
        {
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: setting current led animation msDelay: %d\n", msDelay);
#endif
            this->currentLedAnimationPtr->setDelay(msDelay);
        }
    }
}

void ModuleTM1638plus::toggleLedAnimationInverseMode(void)
{
    if (this->currentLedAnimationType != LED_ANIMATION_TYPE_NONE && this->currentLedAnimationPtr != nullptr)
    {
        if (this->currentLedAnimationPtr->toggleInverse())
        {
#ifdef DEBUG_SERIAL
            Serial.println("TM1638plus:: led animation inverse mode enabled");
#endif
        }
        else
        {
#ifdef DEBUG_SERIAL
            Serial.println("TM1638plus:: led animation inverse mode disabled");
#endif
        }
    }
}

void ModuleTM1638plus::clearSevenSegmentBlock(SEVEN_SEGMENT_BLOCKS block)
{
    if (block == SEVEN_SEGMENT_BLOCK_LEFT || SEVEN_SEGMENT_BLOCK_BOTH)
    {
        this->modulePtr->displayASCII(0, ' ');
        this->modulePtr->displayASCII(1, ' ');
        this->modulePtr->displayASCII(2, ' ');
        this->modulePtr->displayASCII(3, ' ');
    }
    if (block == SEVEN_SEGMENT_BLOCK_RIGHT || SEVEN_SEGMENT_BLOCK_BOTH)
    {
        this->modulePtr->displayASCII(4, ' ');
        this->modulePtr->displayASCII(5, ' ');
        this->modulePtr->displayASCII(6, ' ');
        this->modulePtr->displayASCII(7, ' ');
    }
}

void ModuleTM1638plus::freeSevenSegmentLeftBlock()
{
    if (this->SevenSegmentLeftBlock != nullptr)
    {
        delete this->SevenSegmentLeftBlock;
        this->SevenSegmentLeftBlock = nullptr;
    }
}

void ModuleTM1638plus::freeSevenSegmentRightBlock()
{
    if (this->SevenSegmentRightBlock != nullptr)
    {
        delete this->SevenSegmentRightBlock;
        this->SevenSegmentRightBlock = nullptr;
    }
}

void ModuleTM1638plus::freeSevenSegmentBothBlocks()
{
    if (this->SevenSegmentBothBlocks != nullptr)
    {
        delete this->SevenSegmentBothBlocks;
        this->SevenSegmentBothBlocks = nullptr;
    }
}

void ModuleTM1638plus::displayTextOnLeft7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    this->freeSevenSegmentBothBlocks();
    this->freeSevenSegmentLeftBlock();
    this->SevenSegmentLeftBlock = new SimpleTextEffect(this->modulePtr, text, blink, blinkTimeout, 0, 4);
}

void ModuleTM1638plus::displayTextOnRight7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    this->freeSevenSegmentBothBlocks();
    this->freeSevenSegmentRightBlock();
    this->SevenSegmentRightBlock = new SimpleTextEffect(this->modulePtr, text, blink, blinkTimeout, 4, 8);
}

void ModuleTM1638plus::displayTextOnFull7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    this->freeSevenSegmentBothBlocks();
    this->freeSevenSegmentLeftBlock();
    this->freeSevenSegmentRightBlock();
    this->SevenSegmentBothBlocks = new SimpleTextEffect(this->modulePtr, text, blink, blinkTimeout, 0, 8);
}

void ModuleTM1638plus::refreshTextOnLeft7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->SevenSegmentLeftBlock != nullptr && this->SevenSegmentLeftBlock->isSimpleTextEffect())
    {
        SimpleTextEffect *effect = static_cast<SimpleTextEffect *>(this->SevenSegmentLeftBlock);
        effect->setText(text, blink, blinkTimeout);
    }
}

void ModuleTM1638plus::refreshTextOnRight7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->SevenSegmentRightBlock != nullptr && this->SevenSegmentRightBlock->isSimpleTextEffect())
    {
        SimpleTextEffect *effect = static_cast<SimpleTextEffect *>(this->SevenSegmentRightBlock);
        effect->setText(text, blink, blinkTimeout);
    }
}

void ModuleTM1638plus::refreshTextOnFull7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->SevenSegmentBothBlocks != nullptr && this->SevenSegmentBothBlocks->isSimpleTextEffect())
    {
        SimpleTextEffect *effect = static_cast<SimpleTextEffect *>(this->SevenSegmentBothBlocks);
        effect->setText(text, blink, blinkTimeout);
    }
}

void ModuleTM1638plus::displayMultiFrameTextEffect(const char *frames[], size_t frameCount, uint16_t frameTimeout, const uint8_t startIndex)
{
    this->freeSevenSegmentBothBlocks();
    this->freeSevenSegmentLeftBlock();
    this->freeSevenSegmentRightBlock();
    this->SevenSegmentBothBlocks = new MultiFrameTextEffect(this->modulePtr, frames, frameCount, frameTimeout, startIndex);
}

void ModuleTM1638plus::displayMultiFrameSevenSegmentEffect(const uint8_t frames[], size_t frameCount, uint16_t frameTimeout, const uint8_t startIndex, const uint8_t endIndex)
{
    this->freeSevenSegmentBothBlocks();
    this->freeSevenSegmentLeftBlock();
    this->freeSevenSegmentRightBlock();
    this->SevenSegmentBothBlocks = new MultiFrameSegmentEffect(this->modulePtr, frames, frameCount, frameTimeout, startIndex, endIndex);
}

void ModuleTM1638plus::displayMultiFrameIndividualSevenSegmentEffect(uint8_t **frames, size_t frameCount, size_t frameAffectedSegmentCount, uint16_t frameTimeout, const uint8_t startIndex, const uint8_t endIndex)
{
    // this->freeSevenSegmentBothBlocks();
    // this->freeSevenSegmentLeftBlock();
    // this->freeSevenSegmentRightBlock();
    this->SevenSegmentBothBlocks = new MultiFrameIndividualSegmentEffect(this->modulePtr, frames, frameCount, frameAffectedSegmentCount, frameTimeout, startIndex, endIndex);
}

void ModuleTM1638plus::displayOscilloscopeEffect(void)
{
    this->freeSevenSegmentBothBlocks();
    this->freeSevenSegmentLeftBlock();
    this->freeSevenSegmentRightBlock();
    size_t frameCount = 4;
    size_t frameAffectedSegmentCount = 8;
    uint8_t **seq = new uint8_t *[frameCount];
    for (size_t i = 0; i < frameCount; ++i)
    {
        seq[i] = new uint8_t[frameAffectedSegmentCount];
    }
    std::memcpy(seq[0], (uint8_t[]){SEGMENT_D, SEGMENT_G | SEGMENT_E | SEGMENT_F, SEGMENT_A | SEGMENT_B | SEGMENT_C, SEGMENT_G | SEGMENT_E | SEGMENT_F, SEGMENT_D, SEGMENT_NONE, SEGMENT_NONE, SEGMENT_NONE}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seq[1], (uint8_t[]){SEGMENT_NONE, SEGMENT_D, SEGMENT_G | SEGMENT_E | SEGMENT_F, SEGMENT_A | SEGMENT_B | SEGMENT_C, SEGMENT_G | SEGMENT_E | SEGMENT_F, SEGMENT_D, SEGMENT_NONE, SEGMENT_NONE}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seq[2], (uint8_t[]){SEGMENT_NONE, SEGMENT_NONE, SEGMENT_D, SEGMENT_G | SEGMENT_E | SEGMENT_F, SEGMENT_A | SEGMENT_B | SEGMENT_C, SEGMENT_G | SEGMENT_E | SEGMENT_F, SEGMENT_D, SEGMENT_NONE}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seq[3], (uint8_t[]){SEGMENT_NONE, SEGMENT_NONE, SEGMENT_NONE, SEGMENT_D, SEGMENT_G | SEGMENT_E | SEGMENT_F, SEGMENT_A | SEGMENT_B | SEGMENT_C, SEGMENT_G | SEGMENT_E | SEGMENT_F, SEGMENT_D}, frameAffectedSegmentCount * sizeof(uint8_t));
    this->displayMultiFrameIndividualSevenSegmentEffect(seq, frameCount, frameAffectedSegmentCount, 300, 0, 3);
}

TM1638plusBUTTON ModuleTM1638plus::getPressedButton()
{
    uint8_t pressedButtons = this->buttonsPtr->getPressedButtonsMask();
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
    if (this->currentLedAnimationType != LED_ANIMATION_TYPE_NONE && this->currentLedAnimationPtr != nullptr)
    {
        this->currentLedAnimationPtr->loop();
    }
    // full 7 segment animation
    if (this->SevenSegmentBothBlocks != nullptr)
    {
        this->SevenSegmentBothBlocks->loop();
    }
    else
    {
        // left side 7 segment animation
        if (this->SevenSegmentLeftBlock != nullptr)
        {
            this->SevenSegmentLeftBlock->loop();
        }
        // right side 7 segment animation
        if (this->SevenSegmentRightBlock != nullptr)
        {
            this->SevenSegmentRightBlock->loop();
        }
    }
}
