#include <cstring>
#include <Arduino.h>
#include "Events.hpp"
#include "CommonDefines.hpp"

Events::Events(ExternalButtons *externalButtonsPtr, ModuleTM1638plus *tm1638plusPtr, Sampler *samplerPtr) : externalButtonsPtr(externalButtonsPtr), tm1638plusPtr(tm1638plusPtr), samplerPtr(samplerPtr)
{
}

Events::~Events()
{
    this->externalButtonsPtr = nullptr;
    this->tm1638plusPtr = nullptr;
    this->samplerPtr = nullptr;
}

void Events::onExternalButton(EXTERNAL_BUTTON button)
{
    if (button != EXTERNAL_BUTTON_NONE)
    {
        switch (button)
        {
        case EXTERNAL_BUTTON_1:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: external button 1 pressed... enqueue random laser sample");
#endif
            this->samplerPtr->queueSample(Sampler::laserSamples[random(0, Sampler::laserSamplesSize)]);
            break;
        case EXTERNAL_BUTTON_2:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: external button 2 pressed... enqueue random laser sample");
#endif
            this->samplerPtr->queueSample(Sampler::laserSamples[random(0, Sampler::laserSamplesSize)]);
            break;
        case EXTERNAL_BUTTON_3:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: external button 3 pressed... enqueue tones1 sample");
#endif
            switch (random(0, 2))
            {
            case 0:
                this->samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1);
                break;
            case 1:
                this->samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1);
                break;
            }
            break;
        case EXTERNAL_BUTTON_4:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: external button 4 pressed... enqueue tones2 sample");
#endif
            switch (random(0, 4))
            {
            case 0:
                this->samplerPtr->queueSample(SAMPLE_ALIEN_VOICE_01);
                break;

            case 1:
                this->samplerPtr->queueSample(SAMPLE_ALIEN_VOICE_02);
                break;

            case 2:
                this->samplerPtr->queueSample(SAMPLE_ALIEN_VOICE_03);
                break;

            case 3:
                this->samplerPtr->queueSample(SAMPLE_ALIEN_VOICE_04);
                break;
            }
            break;
        case EXTERNAL_BUTTON_5:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: external button 5 pressed ... enqueue SOS sample");
#endif
            this->samplerPtr->queueSample(SAMPLE_SOS_01);
            break;
        }
    }
}

void Events::onTM1638plusButton(TM1638plusBUTTON button)
{
    if (button != TM1638plusBUTTON_NONE)
    {
        switch (button)
        {
        case TM1638plusBUTTON_S1:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 1 pressed... toggle led effect");
#endif
            this->tm1638plusPtr->toggleLedEffect();
            break;
        case TM1638plusBUTTON_S2:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 2 pressed...toggle led effect inverse mode");
#endif
            this->tm1638plusPtr->toggleLedInverseMode();
            break;
        case TM1638plusBUTTON_S3:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 3 pressed...");
#endif
            break;
        case TM1638plusBUTTON_S4:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 4 pressed...");
#endif
            break;
        case TM1638plusBUTTON_S5:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 5 pressed...");
#endif
            break;
        case TM1638plusBUTTON_S6:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 6 pressed...");
#endif
            break;
        case TM1638plusBUTTON_S7:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 7 pressed...");
#endif
            break;
        case TM1638plusBUTTON_S8:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 8 pressed...");
#endif
            this->tm1638plusPtr->displayOscilloscopeEffect();
            break;
        }
    }
}

void Events::onSampleStarted(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER1_SINGLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER2_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER2_SINGLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER3_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER3_SINGLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER4_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER4_SINGLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER1_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER1_DOUBLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER2_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER2_DOUBLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER3_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER3_DOUBLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER4_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER4_DOUBLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_ALARM_REVERB:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALARM_REVERB");
#endif
        break;
    case SAMPLE_DIRTY_SYREN_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_DIRTY_SYREN_1");
#endif
        break;
    case SAMPLE_DIRTY_SYREN_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_DIRTY_SYREN_2");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
        tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_ALTERNATE, 80);
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5");
#endif
        break;
    case SAMPLE_SOS_01:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_SOS_01");
#endif
        this->startAnimation(ANIMATION_SOS_1);
        break;
    case SAMPLE_SOS_02:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_SOS_02");
#endif
        this->startAnimation(ANIMATION_SOS_2);
        break;
    case SAMPLE_SOS_03:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_SOS_03");
#endif
        this->startAnimation(ANIMATION_SOS_3);
        break;
    case SAMPLE_ALIEN_VOICE_01:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_01");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_1);
        break;
    case SAMPLE_ALIEN_VOICE_02:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_02");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_2);
        break;
    case SAMPLE_ALIEN_VOICE_03:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_03");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_3);
        break;
    case SAMPLE_ALIEN_VOICE_04:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_04");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_4);
        break;
    default:
#ifdef DEBUG_SERIAL
#endif
        tm1638plusPtr->displayTextOnLeft7Segment("    ", false, 0);
        break;
    }
#ifdef DEBUG_SERIAL
    Serial.printf("EVENTS:: OnStart total: %d\n", this->currentLaserSamplesPlaying);
#endif
}

void Events::onSampleStopped(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER1_SINGLE");
#endif
        this->currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER2_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER2_SINGLE");
#endif
        this->currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER3_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER3_SINGLE");
#endif
        this->currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER4_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER4_SINGLE");
#endif
        this->currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER1_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER1_DOUBLE");
#endif
        this->currentLaserSamplesPlaying--;
        samplerPtr->queueSample(SAMPLE_LASER1_SINGLE);
        break;
    case SAMPLE_LASER2_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER2_DOUBLE");
#endif
        this->currentLaserSamplesPlaying--;
        samplerPtr->queueSample(SAMPLE_LASER2_SINGLE);
        break;
    case SAMPLE_LASER3_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER3_DOUBLE");
#endif
        this->currentLaserSamplesPlaying--;
        samplerPtr->queueSample(SAMPLE_LASER3_SINGLE);
        break;
    case SAMPLE_LASER4_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER4_DOUBLE");
#endif
        this->currentLaserSamplesPlaying--;
        samplerPtr->queueSample(SAMPLE_LASER4_SINGLE);
        break;
    case SAMPLE_ALARM_REVERB:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALARM_REVERB");
#endif
        break;
    case SAMPLE_DIRTY_SYREN_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_DIRTY_SYREN_1");
#endif
        break;
    case SAMPLE_DIRTY_SYREN_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_DIRTY_SYREN_2");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5");
#endif
        break;
    case SAMPLE_SOS_01:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_SOS_01");
#endif
        samplerPtr->queueSample(SAMPLE_SOS_02);
        break;
    case SAMPLE_SOS_02:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_SOS_02");
#endif
        samplerPtr->queueSample(SAMPLE_SOS_03);
        break;
    case SAMPLE_SOS_03:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_SOS_03");
#endif
        this->stopAnimation();
        break;
    default:
#ifdef DEBUG_SERIAL
#endif
        break;
    }
#ifdef DEBUG_SERIAL
    Serial.printf("EVENTS:: onStop total: %d\n", this->currentLaserSamplesPlaying);
#endif
    if (true || this->currentLaserSamplesPlaying <= 0)
    {
        // TODO: conflict with another animations ?
        this->stopAnimation();
    }
}

void Events::display7SegmentLaserAnimation(void)
{
    tm1638plusPtr->clearSevenSegmentBlock(SEVEN_SEGMENT_BLOCK_BOTH);
    char buffer[5] = {'\0'};
    // led block
    tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_INTERMITENT, 80);
    // seven segment right block
    if (this->laserShoots >= 10000) // only 4 digits (right block)
    {
        this->laserShoots = 0;
    }
    snprintf(buffer, sizeof(buffer), "%04d", this->laserShoots);
    tm1638plusPtr->displayTextOnRight7Segment(buffer, false, 0);
    // seven segment left block
    size_t frameCount = 5;
    size_t frameAffectedSegmentCount = 4;
    uint8_t **seq = new uint8_t *[frameCount];
    for (size_t i = 0; i < frameCount; ++i)
    {
        seq[i] = new uint8_t[frameAffectedSegmentCount];
    }
    std::memcpy(seq[0], (uint8_t[]){SEGMENT_NONE, SEGMENT_G, SEGMENT_G, SEGMENT_NONE}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seq[1], (uint8_t[]){SEGMENT_G, SEGMENT_G, SEGMENT_G, SEGMENT_G}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seq[2], (uint8_t[]){SEGMENT_F | SEGMENT_G | SEGMENT_E, SEGMENT_G, SEGMENT_G, SEGMENT_B | SEGMENT_G | SEGMENT_C}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seq[3], (uint8_t[]){SEGMENT_A | SEGMENT_F | SEGMENT_G | SEGMENT_E | SEGMENT_D, SEGMENT_G, SEGMENT_G, SEGMENT_A | SEGMENT_B | SEGMENT_G | SEGMENT_C | SEGMENT_D}, frameAffectedSegmentCount * sizeof(uint8_t));
    std::memcpy(seq[4], (uint8_t[]){SEGMENT_A | SEGMENT_F | SEGMENT_E | SEGMENT_D, SEGMENT_A | SEGMENT_D, SEGMENT_A | SEGMENT_D, SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D}, frameAffectedSegmentCount * sizeof(uint8_t));
    tm1638plusPtr->displayMultiFrameIndividualSevenSegmentEffect(seq, frameCount, frameAffectedSegmentCount, 60, 0, 3);
}

void Events::startAnimation(ANIMATION animation)
{
    char buffer[5] = {'\0'};

    if (animation != currentAnimation)
    {
        currentAnimation = animation;
        switch (animation)
        {
        case ANIMATION_LASER_SHOOT:
            this->previousLedEffect = tm1638plusPtr->getCurrentLedEffect();
            this->display7SegmentLaserAnimation();
            break;
        case ANIMATION_SOS_1:
            this->previousLedEffect = tm1638plusPtr->getCurrentLedEffect();
            tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_MORSE_LETTER_S, 105);
            tm1638plusPtr->displayTextOnFull7Segment("S.O.S.  S.O.S.", true, 105);
            break;
        case ANIMATION_SOS_2:
            this->previousLedEffect = tm1638plusPtr->getCurrentLedEffect();
            tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_MORSE_LETTER_O, 140);
            tm1638plusPtr->displayTextOnFull7Segment("  CASA  ", true, 140);
            break;
        case ANIMATION_SOS_3:
            this->previousLedEffect = tm1638plusPtr->getCurrentLedEffect();
            tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_MORSE_LETTER_S, 105);
            tm1638plusPtr->displayTextOnFull7Segment(" CEAVA5 ", true, 105);
            break;
        case ANIMATION_ALIEN_VOICE_1:
        case ANIMATION_ALIEN_VOICE_2:
        case ANIMATION_ALIEN_VOICE_3:
        case ANIMATION_ALIEN_VOICE_4:
            this->previousLedEffect = tm1638plusPtr->getCurrentLedEffect();
            tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_VUMETER_MIRRORED, random(50, 100));
            break;
        }
    }
    else
    {
        switch (animation)
        {
        case ANIMATION_LASER_SHOOT:
            if (this->laserShoots >= 10000) // only 4 digits (right block)
            {
                this->laserShoots = 0;
            }
            // char buffer[5] = {'\0'};
            snprintf(buffer, sizeof(buffer), "%04d", this->laserShoots);
            tm1638plusPtr->refreshTextOnRight7Segment(buffer, false, 0);
            break;
        case ANIMATION_SOS_1:
        case ANIMATION_SOS_2:
        case ANIMATION_SOS_3:
            break;
        }
    }
}

void Events::stopAnimation()
{
    this->previousLedEffect = LED_EFFECT_TYPE_SCANNER;
    switch (this->currentAnimation)
    {
    case ANIMATION_LASER_SHOOT:
        tm1638plusPtr->setLedEffect(this->previousLedEffect);
        tm1638plusPtr->freeSevenSegmentLeftBlock();
        tm1638plusPtr->freeSevenSegmentRightBlock();
        tm1638plusPtr->freeSevenSegmentBothBlocks();
        tm1638plusPtr->clearSevenSegmentBlock(SEVEN_SEGMENT_BLOCK_BOTH);
        break;
    case ANIMATION_SOS_1:
    case ANIMATION_SOS_2:
    case ANIMATION_SOS_3:
        tm1638plusPtr->setLedEffect(this->previousLedEffect);
        tm1638plusPtr->freeSevenSegmentBothBlocks();
        tm1638plusPtr->clearSevenSegmentBlock(SEVEN_SEGMENT_BLOCK_BOTH);
        break;
    case ANIMATION_ALIEN_VOICE_1:
    case ANIMATION_ALIEN_VOICE_2:
    case ANIMATION_ALIEN_VOICE_3:
    case ANIMATION_ALIEN_VOICE_4:
        tm1638plusPtr->setLedEffect(this->previousLedEffect);
        break;
        this->currentAnimation = ANIMATION_NONE;
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
    tm1638plusPtr->displayMultiFrameTextEffect(textFrames, sizeof(textFrames) / sizeof(textFrames[0]), 300, 0);
}