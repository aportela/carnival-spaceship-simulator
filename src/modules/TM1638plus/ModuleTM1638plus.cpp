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
    if (this->SevenSegmentLeftBlockPtr != nullptr)
    {
        delete this->SevenSegmentLeftBlockPtr;
        this->SevenSegmentLeftBlockPtr = nullptr;
    }
    if (this->SevenSegmentRightBlockPtr != nullptr)
    {
        delete this->SevenSegmentRightBlockPtr;
        this->SevenSegmentRightBlockPtr = nullptr;
    }
    if (this->SevenSegmentBothBlocksPtr != nullptr)
    {
        delete this->SevenSegmentBothBlocksPtr;
        this->SevenSegmentBothBlocksPtr = nullptr;
    }
    delete this->buttonsPtr;
    this->buttonsPtr = nullptr;
    delete this->modulePtr;
    this->modulePtr = nullptr;
}

void ModuleTM1638plus::reset(void)
{
    this->modulePtr->reset();
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

LED_ANIMATION_TYPE ModuleTM1638plus::getCurrentLedAnimation(void)
{
    return (this->currentLedAnimationType);
}

void ModuleTM1638plus::toggleLedAnimation()
{
    switch (this->currentLedAnimationType)
    {
    case LED_ANIMATION_TYPE_NONE:
        this->setLedAnimation(LED_ANIMATION_TYPE_SCANNER, DEFAULT_LED_MS_DELAY);
        break;
    case LED_ANIMATION_TYPE_SCANNER:
        this->setLedAnimation(LED_ANIMATION_TYPE_CHASE, DEFAULT_LED_MS_DELAY);
        break;
    case LED_ANIMATION_TYPE_CHASE:
        this->setLedAnimation(LED_ANIMATION_TYPE_VUMETER, DEFAULT_LED_MS_DELAY);
        break;
    case LED_ANIMATION_TYPE_VUMETER:
        this->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, DEFAULT_LED_MS_DELAY);
        break;
    case LED_ANIMATION_TYPE_VUMETER_MIRRORED:
        this->setLedAnimation(LED_ANIMATION_TYPE_ALTERNATE, DEFAULT_LED_MS_DELAY);
        break;
    case LED_ANIMATION_TYPE_ALTERNATE:
        this->setLedAnimation(LED_ANIMATION_TYPE_INTERMITENT, DEFAULT_LED_MS_DELAY);
        break;
    case LED_ANIMATION_TYPE_INTERMITENT:
        this->setLedAnimation(LED_ANIMATION_TYPE_NONE, DEFAULT_LED_MS_DELAY);
        break;
    default:
        this->setLedAnimation(LED_ANIMATION_TYPE_NONE, DEFAULT_LED_MS_DELAY);
        break;
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
            Serial.printf("TM1638plus:: set led animation => SCANNER (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new ScannerLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_CHASE:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => CHASE (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new ChaseLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_VUMETER:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => VUMETER (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new VuMeterLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_VUMETER_MIRRORED:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => VUMETER MIRRORED (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new VuMeterMirroredLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_ALTERNATE:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => ALTERNATE (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new AlternateLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_INTERMITENT:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => INTERMITENT (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new IntermitentLedEffect(this->modulePtr, msDelay);
            break;
        case LED_ANIMATION_TYPE_MORSE_LETTER_S:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => MORSE LETTER S (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new MorseLedEffect(this->modulePtr, msDelay, 'S');
            break;
        case LED_ANIMATION_TYPE_MORSE_LETTER_O:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => MORSE LETTER O (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new MorseLedEffect(this->modulePtr, msDelay, 'O');
            break;
        case LED_ANIMATION_TYPE_NOTES:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set led animation => NOTES (delay %i ms)", msDelay);
#endif
            this->currentLedAnimationPtr = new NotesLedEffect(this->modulePtr, msDelay);
            // this->currentLedAnimationPtr->disableAnimationLoopAtEnd();
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

void ModuleTM1638plus::setLedAnimationRandomDelay(uint16_t minRandomMSDelay, uint16_t maxRandomMSDelay, uint8_t randomMultiplier)
{
    this->currentLedAnimationPtr->setRandomDelay(minRandomMSDelay, maxRandomMSDelay, randomMultiplier);
}

void ModuleTM1638plus::clearSevenSegmentBlock(SEVEN_SEGMENT_BLOCKS block)
{
    if (block == SEVEN_SEGMENT_BLOCK_LEFT || block == SEVEN_SEGMENT_BLOCK_BOTH)
    {
        this->modulePtr->displayASCII(0, ' ');
        this->modulePtr->displayASCII(1, ' ');
        this->modulePtr->displayASCII(2, ' ');
        this->modulePtr->displayASCII(3, ' ');
    }
    if (block == SEVEN_SEGMENT_BLOCK_RIGHT || block == SEVEN_SEGMENT_BLOCK_BOTH)
    {
        this->modulePtr->displayASCII(4, ' ');
        this->modulePtr->displayASCII(5, ' ');
        this->modulePtr->displayASCII(6, ' ');
        this->modulePtr->displayASCII(7, ' ');
    }
}

void ModuleTM1638plus::freeSevenSegmentLeftBlock()
{
    if (this->SevenSegmentLeftBlockPtr != nullptr)
    {
        delete this->SevenSegmentLeftBlockPtr;
        this->SevenSegmentLeftBlockPtr = nullptr;
    }
}

void ModuleTM1638plus::freeSevenSegmentRightBlock()
{
    if (this->SevenSegmentRightBlockPtr != nullptr)
    {
        delete this->SevenSegmentRightBlockPtr;
        this->SevenSegmentRightBlockPtr = nullptr;
    }
}

void ModuleTM1638plus::freeSevenSegmentBothBlocks()
{
    if (this->SevenSegmentBothBlocksPtr != nullptr)
    {
        delete this->SevenSegmentBothBlocksPtr;
        this->SevenSegmentBothBlocksPtr = nullptr;
    }
}

SEVEN_SEGMENT_ANIMATION_TYPE ModuleTM1638plus::getCurrentSevenSegmentAnimation(void)
{
    return (this->currentSevenSegmentAnimationType);
}

void ModuleTM1638plus::toggleSevenSegmentAnimation()
{
    switch (this->currentSevenSegmentAnimationType)
    {
    case SEVEN_SEGMENT_ANIMATION_TYPE_NONE:
        this->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_1, DEFAULT_7SEGMENT_MS_DELAY);
        break;
    case SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_1:
        this->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_2, DEFAULT_7SEGMENT_MS_DELAY);
        break;
    case SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_2:
        this->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_3, DEFAULT_7SEGMENT_MS_DELAY);
        break;
    case SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_3:
        this->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_MESSAGE_1, DEFAULT_SEVEN_SEGMENT_TEXT_EFFECT_MS_DELAY);
        break;
    case SEVEN_SEGMENT_ANIMATION_TYPE_MESSAGE_1:
        this->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_NONE, DEFAULT_7SEGMENT_MS_DELAY);
        break;
    }
}

void ModuleTM1638plus::setSevenSegmentLaserAnimation(uint16_t laserShoots)
{
    char buffer[5] = {'\0'};
    size_t frameCount = 5;
    size_t frameAffectedSegmentCount = 4;
    uint8_t **seqLaser = new uint8_t *[frameCount];
    for (size_t i = 0; i < frameCount; ++i)
    {
        seqLaser[i] = new uint8_t[frameAffectedSegmentCount];
    }
    std::memcpy(seqLaser[0], (uint8_t[]){SEGMENT_NONE, SEGMENT_G, SEGMENT_G, SEGMENT_NONE}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seqLaser[1], (uint8_t[]){SEGMENT_G, SEGMENT_G, SEGMENT_G, SEGMENT_G}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seqLaser[2], (uint8_t[]){SEGMENT_F | SEGMENT_G | SEGMENT_E, SEGMENT_G, SEGMENT_G, SEGMENT_B | SEGMENT_G | SEGMENT_C}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seqLaser[3], (uint8_t[]){SEGMENT_A | SEGMENT_F | SEGMENT_G | SEGMENT_E | SEGMENT_D, SEGMENT_G, SEGMENT_G, SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_C | SEGMENT_D}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seqLaser[4], (uint8_t[]){SEGMENT_A | SEGMENT_F | SEGMENT_E | SEGMENT_D, SEGMENT_A | SEGMENT_D, SEGMENT_A | SEGMENT_D, SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D}, frameAffectedSegmentCount * sizeof(uint8_t));
    // animation on seven segment left block
    snprintf(buffer, sizeof(buffer), "%04d", laserShoots);
    this->SevenSegmentLeftBlockPtr = new MultiFrameIndividualSegmentEffect(this->modulePtr, seqLaser, frameCount, frameAffectedSegmentCount, DEFAULT_SEVEN_SEGMENT_LASER_EFFECT_MS_DELAY, 0, 3);
    // laser count on seven segment right block
    this->SevenSegmentRightBlockPtr = new SimpleTextEffect(this->modulePtr, buffer, false, 0, 4, 8);
}

void ModuleTM1638plus::updateSevenSegmentLaserCountAnimationText(uint16_t laserShoots)
{
    // laser count on seven segment right block
    char buffer[5] = {'\0'};
    snprintf(buffer, sizeof(buffer), "%04d", laserShoots);
    SimpleTextEffect *effect = static_cast<SimpleTextEffect *>(this->SevenSegmentRightBlockPtr);
    effect->setText(buffer, false, 0);
}

void ModuleTM1638plus::setSevenSegmentOscilloscopeAnimation(void)
{
    const uint8_t oscilloscopeFrame[] = {SEGMENT_G, SEGMENT_F | SEGMENT_A | SEGMENT_B | SEGMENT_C, SEGMENT_D, SEGMENT_E | SEGMENT_G | SEGMENT_B, SEGMENT_A | SEGMENT_B, SEGMENT_G | SEGMENT_C, SEGMENT_D, SEGMENT_E | SEGMENT_G};
    size_t frameCount = 8;
    size_t frameAffectedSegmentCount = 8;
    uint8_t **scrolledFrames = new uint8_t *[frameCount];
    for (size_t i = 0; i < frameCount; ++i)
    {
        scrolledFrames[i] = new uint8_t[frameAffectedSegmentCount];
    }
    for (size_t i = 0; i < frameCount; ++i)
    {
        for (size_t j = 0; j < frameAffectedSegmentCount; ++j)
        {
            scrolledFrames[i][j] = oscilloscopeFrame[(j + i) % frameAffectedSegmentCount];
        }
    }
    this->SevenSegmentBothBlocksPtr = new MultiFrameIndividualSegmentEffect(this->modulePtr, scrolledFrames, frameCount, frameAffectedSegmentCount, 100, 0, 3);
}

void ModuleTM1638plus::setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE animation, uint16_t msDelay, uint16_t extraData)
{
    if (animation != this->currentSevenSegmentAnimationType)
    {
        this->clearSevenSegmentBlock(SEVEN_SEGMENT_BLOCK_BOTH);
        if (this->SevenSegmentLeftBlockPtr != nullptr)
        {
            delete this->SevenSegmentLeftBlockPtr;
            this->SevenSegmentLeftBlockPtr = nullptr;
        }
        if (this->SevenSegmentRightBlockPtr != nullptr)
        {
            delete this->SevenSegmentRightBlockPtr;
            this->SevenSegmentRightBlockPtr = nullptr;
        }
        if (this->SevenSegmentBothBlocksPtr != nullptr)
        {
            delete this->SevenSegmentBothBlocksPtr;
            this->SevenSegmentBothBlocksPtr = nullptr;
        }
        const char *textFrames[] = {
            "       P",
            "      PI",
            "     PIL",
            "    PILI",
            "   PILI ",
            "  PILI D",
            " PILI DE",
            "PILI DE ",
            "ILI DE L",
            "LI DE LE",
            "I DE LEI",
            " DE LEIA",
            "DE LEIAO",
            "E LEIAO ",
            " LEIAO  ",
            "LEIAO   ",
            "EIAO    ",
            "IAO     ",
            "AO      ",
            "O       ",
            "        ",
        };
        const char *notesFrames[] = {
            "W-_[%|1<",
            "W-_[%|1<",
            "W-_[%|1<",
            "*<!K]#/%",
            "*<!K]#/%",
            "*<!K]#/%",
            "[cd|f-tv",
            "[cd|f-tv",
            "[cd|f-tv",
            "WX=<>K[N",
            "WX=<>K[N",
            "WX=<>K[N",
            "WX=<>K[N",
            "]1|v<W>4",
            "]1|v<W>4",
            "]1|v<W>4",
            "]1|v<W>4",
        };
        const uint8_t seq1[] = {SEGMENT_A, SEGMENT_B, SEGMENT_G, SEGMENT_E, SEGMENT_D, SEGMENT_C, SEGMENT_G, SEGMENT_F};
        const uint8_t seq2[] = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F};
        const uint8_t seq3[] = {SEGMENT_A | SEGMENT_D, SEGMENT_F | SEGMENT_E | SEGMENT_B | SEGMENT_C, SEGMENT_G};
        char buffer[5] = {'\0'};

        switch (animation)
        {
        case SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_1:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Full pattern 1 (delay %i ms)\n", msDelay);
#endif
            this->SevenSegmentBothBlocksPtr = new MultiFrameSegmentEffect(this->modulePtr, seq1, sizeof(seq1) / sizeof(seq1[0]), msDelay, 0, 7);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_2:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Full pattern 2 (delay %i ms)\n", msDelay);
#endif
            this->SevenSegmentBothBlocksPtr = new MultiFrameSegmentEffect(this->modulePtr, seq2, sizeof(seq2) / sizeof(seq2[0]), msDelay, 0, 7);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_3:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Full pattern 3 (delay %i ms)\n", msDelay);
#endif
            this->SevenSegmentBothBlocksPtr = new MultiFrameSegmentEffect(this->modulePtr, seq3, sizeof(seq3) / sizeof(seq3[0]), msDelay, 0, 7);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_MESSAGE_1:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Message 1 (delay %i ms)\n", msDelay);
#endif
            this->SevenSegmentBothBlocksPtr = new MultiFrameTextEffect(this->modulePtr, textFrames, sizeof(textFrames) / sizeof(textFrames[0]), msDelay, 0);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_LASER:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Laser (delay %i ms)\n", msDelay);
#endif
            this->setSevenSegmentLaserAnimation(extraData);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_SOS_1:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => SOS morse letter S (delay %i ms)\n", msDelay);
#endif
            this->SevenSegmentBothBlocksPtr = new SimpleTextEffect(this->modulePtr, "S.O.S.  S.O.S.", true, msDelay, 0, 7);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_SOS_2:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => SOS morse letter O (delay %i ms)\n", msDelay);
#endif
            this->SevenSegmentBothBlocksPtr = new SimpleTextEffect(this->modulePtr, "  CASA  ", true, msDelay, 0, 7);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_SOS_3:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => SOS morse letter S (delay %i ms)\n", msDelay);
#endif
            this->SevenSegmentBothBlocksPtr = new SimpleTextEffect(this->modulePtr, " CEAVA5 ", true, msDelay, 0, 7);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_1:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Alien voice 1 (delay %i ms)\n", msDelay);
#endif
            this->setSevenSegmentOscilloscopeAnimation();
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_2:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Alien voice 2 (delay %i ms)\n", msDelay);
#endif
            this->setSevenSegmentOscilloscopeAnimation();
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_3:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Alien voice 3 (delay %i ms)\n", msDelay);
#endif
            this->setSevenSegmentOscilloscopeAnimation();
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_4:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => Alien voice 4 (delay %i ms)\n", msDelay);
#endif
            this->setSevenSegmentOscilloscopeAnimation();
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_NOTES:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => NOTES (delay %i ms)\n", msDelay);
#endif
            this->SevenSegmentBothBlocksPtr = new MultiFrameTextEffect(this->modulePtr, notesFrames, sizeof(notesFrames) / sizeof(notesFrames[0]), msDelay, 0);
            break;
        case SEVEN_SEGMENT_ANIMATION_TYPE_NONE:
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: set seven segment animation => NONE (delay %i ms)\n", msDelay);
#endif
            break;
        }
        this->currentSevenSegmentAnimationType = animation;
    }
    else
    {
        if (animation != SEVEN_SEGMENT_ANIMATION_TYPE_NONE)
        {
#ifdef DEBUG_SERIAL
            Serial.printf("TM1638plus:: setting current seven segment animation msDelay: %d\n", msDelay);
#endif
            if (this->currentSevenSegmentAnimationType == SEVEN_SEGMENT_ANIMATION_TYPE_LASER)
            {
                this->updateSevenSegmentLaserCountAnimationText(extraData);
            }
        }
    }
}

void ModuleTM1638plus::setSevenSegmentBothBlocksAnimationRandomDelay(uint16_t minRandomMSDelay, uint16_t maxRandomMSDelay, uint8_t randomMultiplier)
{
    if (this->SevenSegmentBothBlocksPtr != nullptr)
    {
        this->SevenSegmentBothBlocksPtr->setRandomDelay(minRandomMSDelay, maxRandomMSDelay, randomMultiplier);
    }
}

void ModuleTM1638plus::displayTextOnLeft7Segment(const char *text, bool blink, uint16_t blinkTimeout, bool freePrevious)
{
    if (freePrevious)
    {
        this->freeSevenSegmentLeftBlock();
    }
    this->SevenSegmentLeftBlockPtr = new SimpleTextEffect(this->modulePtr, text, blink, blinkTimeout, 0, 4);
}

void ModuleTM1638plus::displayTextOnRight7Segment(const char *text, bool blink, uint16_t blinkTimeout, bool freePrevious)
{
    if (freePrevious)
    {
        this->freeSevenSegmentRightBlock();
    }
    this->SevenSegmentRightBlockPtr = new SimpleTextEffect(this->modulePtr, text, blink, blinkTimeout, 4, 8);
}

void ModuleTM1638plus::displayTextOnFull7Segment(const char *text, bool blink, uint16_t blinkTimeout, bool freePrevious)
{
    if (freePrevious)
    {
        this->freeSevenSegmentBothBlocks();
    }
    this->SevenSegmentBothBlocksPtr = new SimpleTextEffect(this->modulePtr, text, blink, blinkTimeout, 0, 8);
}

void ModuleTM1638plus::refreshTextOnLeft7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->SevenSegmentLeftBlockPtr != nullptr && this->SevenSegmentLeftBlockPtr->isSimpleTextEffect())
    {
        SimpleTextEffect *effect = static_cast<SimpleTextEffect *>(this->SevenSegmentLeftBlockPtr);
        effect->setText(text, blink, blinkTimeout);
    }
}

void ModuleTM1638plus::refreshTextOnRight7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->SevenSegmentRightBlockPtr != nullptr && this->SevenSegmentRightBlockPtr->isSimpleTextEffect())
    {
        SimpleTextEffect *effect = static_cast<SimpleTextEffect *>(this->SevenSegmentRightBlockPtr);
        effect->setText(text, blink, blinkTimeout);
    }
}

void ModuleTM1638plus::refreshTextOnFull7Segment(const char *text, bool blink, uint16_t blinkTimeout)
{
    if (this->SevenSegmentBothBlocksPtr != nullptr && this->SevenSegmentBothBlocksPtr->isSimpleTextEffect())
    {
        SimpleTextEffect *effect = static_cast<SimpleTextEffect *>(this->SevenSegmentBothBlocksPtr);
        effect->setText(text, blink, blinkTimeout);
    }
}

void ModuleTM1638plus::displayMultiFrameTextEffect(const char *frames[], size_t frameCount, uint16_t frameTimeout, const uint8_t startIndex, bool freePrevious)
{
    if (freePrevious)
    {
        this->freeSevenSegmentBothBlocks();
    }
    this->SevenSegmentBothBlocksPtr = new MultiFrameTextEffect(this->modulePtr, frames, frameCount, frameTimeout, startIndex);
}

void ModuleTM1638plus::displayMultiFrameSevenSegmentEffect(const uint8_t frames[], size_t frameCount, uint16_t frameTimeout, const uint8_t startIndex, const uint8_t endIndex, bool freePrevious)
{
    if (freePrevious)
    {
        this->freeSevenSegmentBothBlocks();
    }
    this->SevenSegmentBothBlocksPtr = new MultiFrameSegmentEffect(this->modulePtr, frames, frameCount, frameTimeout, startIndex, endIndex);
}

void ModuleTM1638plus::displayMultiFrameIndividualSevenSegmentEffect(uint8_t **frames, size_t frameCount, size_t frameAffectedSegmentCount, uint16_t frameTimeout, const uint8_t startIndex, const uint8_t endIndex, bool freePrevious)
{
    if (freePrevious)
    {
        this->freeSevenSegmentBothBlocks();
    }
    this->SevenSegmentBothBlocksPtr = new MultiFrameIndividualSegmentEffect(this->modulePtr, frames, frameCount, frameAffectedSegmentCount, frameTimeout, startIndex, endIndex);
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
    if (this->SevenSegmentBothBlocksPtr != nullptr)
    {
        this->SevenSegmentBothBlocksPtr->loop();
    }
    else
    {
        // left side 7 segment animation
        if (this->SevenSegmentLeftBlockPtr != nullptr)
        {
            this->SevenSegmentLeftBlockPtr->loop();
        }
        // right side 7 segment animation
        if (this->SevenSegmentRightBlockPtr != nullptr)
        {
            if (this->currentSevenSegmentAnimationType == SEVEN_SEGMENT_ANIMATION_TYPE_LASER)
            {
                // TODO: update ?
            }
            this->SevenSegmentRightBlockPtr->loop();
        }
    }
}
