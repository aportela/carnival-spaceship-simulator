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
            this->samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1);
            break;
        case EXTERNAL_BUTTON_4:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: external button 4 pressed... enqueue tones2 sample");
#endif
            this->samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1);
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
        Serial.println("Started playing SAMPLE_LASER1_SINGLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER2_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_LASER2_SINGLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER3_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_LASER3_SINGLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER4_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_LASER4_SINGLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER1_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_LASER1_DOUBLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER2_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_LASER2_DOUBLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER3_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_LASER3_DOUBLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER4_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_LASER4_DOUBLE");
#endif
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_ALARM_REVERB:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_ALARM_REVERB");
#endif
        break;
    case SAMPLE_DIRTY_SYREN_1:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_DIRTY_SYREN_1");
#endif
        break;
    case SAMPLE_DIRTY_SYREN_2:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_DIRTY_SYREN_2");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5");
#endif
        break;
    case SAMPLE_SOS_01:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_SOS_01");
#endif
        this->startAnimation(ANIMATION_SOS_1);
        break;
    case SAMPLE_SOS_02:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_SOS_02");
#endif
        this->startAnimation(ANIMATION_SOS_2);
        break;
    case SAMPLE_SOS_03:
#ifdef DEBUG_SERIAL
        Serial.println("Started playing SAMPLE_SOS_03");
#endif
        this->startAnimation(ANIMATION_SOS_3);
        break;
    default:
#ifdef DEBUG_SERIAL
#endif
        tm1638plusPtr->displayTextOnLeft7Segment("    ", false, 0);
        break;
    }
    Serial.printf("OnStart total: %d\n", this->currentLaserSamplesPlaying);
}

void Events::onSampleStopped(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_LASER1_SINGLE");
#endif
        this->currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER2_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_LASER2_SINGLE");
#endif
        this->currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER3_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_LASER3_SINGLE");
#endif
        this->currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER4_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_LASER4_SINGLE");
#endif
        this->currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER1_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_LASER1_DOUBLE");
#endif
        this->currentLaserSamplesPlaying--;
        samplerPtr->queueSample(SAMPLE_LASER1_SINGLE);
        break;
    case SAMPLE_LASER2_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_LASER2_DOUBLE");
#endif
        this->currentLaserSamplesPlaying--;
        samplerPtr->queueSample(SAMPLE_LASER2_SINGLE);
        break;
    case SAMPLE_LASER3_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_LASER3_DOUBLE");
#endif
        this->currentLaserSamplesPlaying--;
        samplerPtr->queueSample(SAMPLE_LASER3_SINGLE);
        break;
    case SAMPLE_LASER4_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_LASER4_DOUBLE");
#endif
        this->currentLaserSamplesPlaying--;
        samplerPtr->queueSample(SAMPLE_LASER4_SINGLE);
        break;
    case SAMPLE_ALARM_REVERB:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_ALARM_REVERB");
#endif
        break;
    case SAMPLE_DIRTY_SYREN_1:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_DIRTY_SYREN_1");
#endif
        break;
    case SAMPLE_DIRTY_SYREN_2:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_DIRTY_SYREN_2");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5");
#endif
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4");
#endif
        samplerPtr->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5");
#endif
        break;
    case SAMPLE_SOS_01:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_SOS_01");
#endif
        samplerPtr->queueSample(SAMPLE_SOS_02);
        break;
    case SAMPLE_SOS_02:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_SOS_02");
#endif
        samplerPtr->queueSample(SAMPLE_SOS_03);
        break;
    case SAMPLE_SOS_03:
#ifdef DEBUG_SERIAL
        Serial.println("Stopped playing SAMPLE_SOS_03");
#endif
        this->stopAnimation();
        break;
    default:
#ifdef DEBUG_SERIAL
#endif
        break;
    }
    Serial.printf("onStop total: %d\n", this->currentLaserSamplesPlaying);
    if (this->currentLaserSamplesPlaying <= 0)
    {
        // TODO: conflict with another animations ?
        this->stopAnimation();
    }
}

void Events::startAnimation(ANIMATION animation)
{
    char buffer[5] = {'\0'};
    const char *textFrames_SOS1[] = {
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
    };
    const char *textFrames_SOS2[] = {
        "CASA    ",
        " CASA   ",
        "  CASA  ",
        "   CASA ",
        "    CASA",
        "   CASA ",
        "  CASA  ",
        " CASA   ",
        "CASA    ",
    };

    const char *textFrames_SOS3[] = {
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

    if (animation != currentAnimation)
    {
        currentAnimation = animation;
        switch (animation)
        {
        case ANIMATION_LASER_SHOOT:
            this->previousLedEffect = tm1638plusPtr->getCurrentLedEffect();
            tm1638plusPtr->setLedEffect(LED_EFFECT_TYPE_INTERMITENT, 80);
            if (this->laserShoots >= 10000) // only 4 digits (right block)
            {
                this->laserShoots = 0;
            }
            snprintf(buffer, sizeof(buffer), "%04d", this->laserShoots);
            tm1638plusPtr->displayTextOnRight7Segment(buffer, false, 0);
            break;
        case ANIMATION_SOS_1:
            tm1638plusPtr->displayTextOnFull7Segment("S.O.S.  S.O.S.", true, 105);
            // tm1638plusPtr->displayMultiFrameTextEffect(textFrames_SOS1, (sizeof(textFrames_SOS1) / sizeof(textFrames_SOS1[0])), 60, 0);
            break;
        case ANIMATION_SOS_2:
            tm1638plusPtr->displayTextOnFull7Segment("  CASA  ", true, 140);
            // tm1638plusPtr->displayMultiFrameTextEffect(textFrames_SOS2, (sizeof(textFrames_SOS2) / sizeof(textFrames_SOS2[0])), 60, 0);
            break;
        case ANIMATION_SOS_3:
            tm1638plusPtr->displayTextOnFull7Segment(" CEAVA5 ", true, 105);
            // tm1638plusPtr->displayMultiFrameTextEffect(textFrames_SOS3, (sizeof(textFrames_SOS3) / sizeof(textFrames_SOS3[0])), 60, 0);
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
    switch (currentAnimation)
    {
    case ANIMATION_LASER_SHOOT:
        tm1638plusPtr->setLedEffect(this->previousLedEffect);
        tm1638plusPtr->freeSevenSegmentRightBlock(true);
        break;
    case ANIMATION_SOS_1:
    case ANIMATION_SOS_2:
    case ANIMATION_SOS_3:
        tm1638plusPtr->freeSevenSegmentBothBlocks(true);
        break;
    }
    currentAnimation = ANIMATION_NONE;
}
