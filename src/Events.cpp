#include <cstring>
#include <Arduino.h>
#include <RP2040.h>
#include "Events.hpp"
#include "CommonDefines.hpp"

Events::Events(ExternalButtons *externalButtonsPtr, ModuleTM1638plus *tm1638plusPtr, Sampler *samplerPtr) : externalButtonsPtr(externalButtonsPtr), tm1638plusPtr(tm1638plusPtr), samplerPtr(samplerPtr)
{
    this->shuffleAlienVoiceSamplesQueue();
    this->timerBackgroundSampleLastMillis = millis();
}

Events::~Events()
{
    this->externalButtonsPtr = nullptr;
    this->tm1638plusPtr = nullptr;
    this->samplerPtr = nullptr;
}

void Events::shuffleAlienVoiceSamplesQueue(void)
{
    SAMPLE validSamples[ALIEN_VOICE_SAMPLES_QUEUE_SIZE] = {
        SAMPLE_ALIEN_VOICE_01,
        SAMPLE_ALIEN_VOICE_02,
        SAMPLE_ALIEN_VOICE_03,
        SAMPLE_ALIEN_VOICE_04,
        SAMPLE_ALIEN_VOICE_05,
        SAMPLE_ALIEN_VOICE_06,
        SAMPLE_ALIEN_VOICE_07,
        SAMPLE_ALIEN_VOICE_08,
        SAMPLE_ALIEN_VOICE_09,
    };
    for (int i = 0; i < ALIEN_VOICE_SAMPLES_QUEUE_SIZE; i++)
    {
        this->alienVoiceSamplesQueue[i] = validSamples[i];
    }
    for (int i = ALIEN_VOICE_SAMPLES_QUEUE_SIZE - 1; i > 0; i--)
    {
        int j = random(0, i + 1);
        SAMPLE temp = this->alienVoiceSamplesQueue[i];
        this->alienVoiceSamplesQueue[i] = this->alienVoiceSamplesQueue[j];
        this->alienVoiceSamplesQueue[j] = temp;
    }
    this->alienVoiceSamplesQueueIndex = 0;
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
            if (!this->isPlayingEncountersOnThirdPhaseSamples && !this->isPlayingAlienVoiceSamples && !this->isPlayingSOSSamples)
            {
                this->isPlayingEncountersOnThirdPhaseSamples = true;
                this->samplerPtr->queueSample(!lastEncountersOnThirdPhaseToneLow ? SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1 : SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1);
                lastEncountersOnThirdPhaseToneLow = !lastEncountersOnThirdPhaseToneLow;
            }
            break;
        case EXTERNAL_BUTTON_4:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: external button 4 pressed... enqueue tones2 sample");
#endif
            if (!this->isPlayingAlienVoiceSamples && !this->isPlayingSOSSamples && !this->isPlayingEncountersOnThirdPhaseSamples)
            {
                this->isPlayingAlienVoiceSamples = true;
                if (this->alienVoiceSamplesQueueIndex >= ALIEN_VOICE_SAMPLES_QUEUE_SIZE)
                {
                    this->shuffleAlienVoiceSamplesQueue();
                }
                this->samplerPtr->queueSample(this->alienVoiceSamplesQueue[this->alienVoiceSamplesQueueIndex++]);
            }
            break;
        case EXTERNAL_BUTTON_5:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: external button 5 pressed ... enqueue SOS sample");
#endif
            if (!this->isPlayingSOSSamples && !this->isPlayingAlienVoiceSamples && !this->isPlayingEncountersOnThirdPhaseSamples)
            {
                this->isPlayingSOSSamples = true;
                this->samplerPtr->queueSample(SAMPLE_SOS_01);
            }
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
            this->tm1638plusPtr->toggleLedAnimation();
            break;
        case TM1638plusBUTTON_S2:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 2 pressed...toggle led effect inverse mode");
#endif
            this->tm1638plusPtr->toggleLedAnimationInverseMode();
            break;
        case TM1638plusBUTTON_S3:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 3 pressed...");
#endif
            break;
        case TM1638plusBUTTON_S4:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 4 pressed... removing timer background samples");
#endif
            this->timerBackgroundSample = SAMPLE_NONE;
            break;
        case TM1638plusBUTTON_S5:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 5 pressed... adding timer background alarm reverb sample");
#endif
            this->timerBackgroundSample = SAMPLE_ALARM_REVERB_SEQ_1;
            if (!this->isPlayingAlarmReverbSamples)
            {
                this->timerBackgroundSampleLastMillis = millis();
                this->isPlayingAlarmReverbSamples = true;
                this->samplerPtr->play(SAMPLE_ALARM_REVERB_SEQ_1);
            }
            break;
        case TM1638plusBUTTON_S6:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 6 pressed... adding timer background dirty syren 1 sample");
#endif
            this->timerBackgroundSample = SAMPLE_DIRTY_SYREN_1;
            if (!this->isPlayingDirtySyren1Sample)
            {
                this->timerBackgroundSampleLastMillis = millis();
                this->isPlayingDirtySyren1Sample = true;
                this->samplerPtr->play(SAMPLE_DIRTY_SYREN_1);
            }
            break;
        case TM1638plusBUTTON_S7:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 7 pressed... adding timer background dirty syren 2 sample");
#endif
            this->timerBackgroundSample = SAMPLE_DIRTY_SYREN_2;
            if (!this->isPlayingDirtySyren2Sample)
            {
                this->timerBackgroundSampleLastMillis = millis();
                this->isPlayingDirtySyren2Sample = true;
                this->samplerPtr->play(SAMPLE_DIRTY_SYREN_2);
            }
            break;
        case TM1638plusBUTTON_S8:
#ifdef DEBUG_SERIAL
            Serial.println("EVENTS:: TM1638plus button 8 pressed... rebooting");
#endif
            rp2040.reboot();
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
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER2_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER2_SINGLE");
#endif
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER3_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER3_SINGLE");
#endif
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER4_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER4_SINGLE");
#endif
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER1_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER1_DOUBLE");
#endif
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER2_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER2_DOUBLE");
#endif
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER3_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER3_DOUBLE");
#endif
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER4_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_LASER4_DOUBLE");
#endif
        this->startAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_ALARM_REVERB:
    case SAMPLE_ALARM_REVERB_SEQ_1:
    case SAMPLE_ALARM_REVERB_SEQ_2:
    case SAMPLE_ALARM_REVERB_SEQ_3:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALARM_REVERB");
#endif
        this->startAnimation(ANIMATION_ALARM_REVERB);
        break;
    case SAMPLE_DIRTY_SYREN_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_DIRTY_SYREN_1");
#endif
        this->startAnimation(ANIMATION_DIRTY_SYREN_1);
        break;
    case SAMPLE_DIRTY_SYREN_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_DIRTY_SYREN_2");
#endif
        this->startAnimation(ANIMATION_DIRTY_SYREN_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_1);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_3);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_4);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_5);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_1);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_3);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_4);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5");
#endif
        this->startAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_5);
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
    case SAMPLE_ALIEN_VOICE_05:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_05");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_5);
        break;
    case SAMPLE_ALIEN_VOICE_06:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_06");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_6);
        break;
    case SAMPLE_ALIEN_VOICE_07:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_07");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_7);
        break;
    case SAMPLE_ALIEN_VOICE_08:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_08");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_8);
        break;
    case SAMPLE_ALIEN_VOICE_09:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Started playing SAMPLE_ALIEN_VOICE_09");
#endif
        this->startAnimation(ANIMATION_ALIEN_VOICE_9);
        break;
    }
}

void Events::onSampleStopped(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER1_SINGLE");
#endif
        this->stopAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER2_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER2_SINGLE");
#endif
        this->stopAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER3_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER3_SINGLE");
#endif
        this->stopAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER4_SINGLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER4_SINGLE");
#endif
        this->stopAnimation(ANIMATION_LASER_SHOOT);
        break;
    case SAMPLE_LASER1_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER1_DOUBLE");
#endif
        this->stopAnimation(ANIMATION_LASER_SHOOT);
        samplerPtr->queueSample(SAMPLE_LASER1_SINGLE);
        break;
    case SAMPLE_LASER2_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER2_DOUBLE");
#endif
        this->stopAnimation(ANIMATION_LASER_SHOOT);
        samplerPtr->queueSample(SAMPLE_LASER2_SINGLE);
        break;
    case SAMPLE_LASER3_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER3_DOUBLE");
#endif
        this->stopAnimation(ANIMATION_LASER_SHOOT);
        samplerPtr->queueSample(SAMPLE_LASER3_SINGLE);
        break;
    case SAMPLE_LASER4_DOUBLE:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_LASER4_DOUBLE");
#endif
        this->stopAnimation(ANIMATION_LASER_SHOOT);
        samplerPtr->queueSample(SAMPLE_LASER4_SINGLE);
        break;
    case SAMPLE_ALARM_REVERB:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALARM_REVERB");
#endif
        this->stopAnimation(ANIMATION_ALARM_REVERB);
        break;
    case SAMPLE_ALARM_REVERB_SEQ_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALARM_REVERB SEQ1");
#endif
        samplerPtr->queueSample(SAMPLE_ALARM_REVERB_SEQ_2);
        break;
    case SAMPLE_ALARM_REVERB_SEQ_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALARM_REVERB SEQ2");
#endif
        samplerPtr->queueSample(SAMPLE_ALARM_REVERB_SEQ_3);
        break;
    case SAMPLE_ALARM_REVERB_SEQ_3:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALARM_REVERB SEQ3");
#endif
        this->stopAnimation(ANIMATION_ALARM_REVERB);
        break;
    case SAMPLE_DIRTY_SYREN_1:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_DIRTY_SYREN_1");
#endif
        this->stopAnimation(ANIMATION_DIRTY_SYREN_1);
        break;
    case SAMPLE_DIRTY_SYREN_2:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_DIRTY_SYREN_2");
#endif
        this->stopAnimation(ANIMATION_DIRTY_SYREN_2);
        break;
    case SAMPLE_ALIEN_VOICE_01:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_01");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_1);
        break;
    case SAMPLE_ALIEN_VOICE_02:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_02");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_2);
        break;
    case SAMPLE_ALIEN_VOICE_03:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_03");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_3);
        break;
    case SAMPLE_ALIEN_VOICE_04:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_04");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_4);
        break;
    case SAMPLE_ALIEN_VOICE_05:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_05");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_5);
        break;
    case SAMPLE_ALIEN_VOICE_06:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_06");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_6);
        break;
    case SAMPLE_ALIEN_VOICE_07:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_07");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_7);
        break;
    case SAMPLE_ALIEN_VOICE_08:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_08");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_8);
        break;
    case SAMPLE_ALIEN_VOICE_09:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_ALIEN_VOICE_09");
#endif
        this->stopAnimation(ANIMATION_ALIEN_VOICE_9);
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
        this->stopAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_5);
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
        this->stopAnimation(ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_5);
        break;
    case SAMPLE_SOS_01:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_SOS_01");
#endif
        this->stopAnimation(ANIMATION_SOS_1);
        samplerPtr->queueSample(SAMPLE_SOS_02);
        break;
    case SAMPLE_SOS_02:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_SOS_02");
#endif
        this->stopAnimation(ANIMATION_SOS_2);
        samplerPtr->queueSample(SAMPLE_SOS_03);
        break;
    case SAMPLE_SOS_03:
#ifdef DEBUG_SERIAL
        Serial.println("EVENTS:: Stopped playing SAMPLE_SOS_03");
#endif
        this->stopAnimation(ANIMATION_SOS_3);
        break;
    default:
#ifdef DEBUG_SERIAL
#endif
        break;
    }
}

bool Events::allowStartAnimation(ANIMATION animation)
{

    if (this->currentAnimation != animation)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void Events::refreshAnimation(ANIMATION animation)
{
    char buffer[5] = {'\0'};
    switch (animation)
    {
    case ANIMATION_LASER_SHOOT:
        this->currentLaserSamplesPlaying++;
        this->laserShoots++;
        if (this->laserShoots >= 10000) // only 4 digits (right block)
        {
            this->laserShoots = 0;
        }
        snprintf(buffer, sizeof(buffer), "%04d", this->laserShoots);
        tm1638plusPtr->refreshTextOnRight7Segment(buffer, false, 0);
        break;
    case ANIMATION_SOS_1:
    case ANIMATION_SOS_2:
    case ANIMATION_SOS_3:
        break;
    case ANIMATION_ALARM_REVERB:
        tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER, 60, false, true);
        break;
    }
}

void Events::startAnimation(ANIMATION animation)
{
    if (animation != this->currentAnimation)
    {
        currentAnimation = animation;
        this->previousLedEffect = tm1638plusPtr->getCurrentLedAnimation();
        this->previousSevenSegmentAnimation = tm1638plusPtr->getCurrentSevenSegmentAnimation();
        switch (animation)
        {
        case ANIMATION_LASER_SHOOT:
            this->currentLaserSamplesPlaying++;
            this->laserShoots++;
            this->tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_INTERMITENT, 80);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_LASER, DEFAULT_7SEGMENT_MS_DELAY, this->laserShoots);
            break;
        case ANIMATION_SOS_1:
            this->tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_MORSE_LETTER_S, 100);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_SOS_1, 100);
            break;
        case ANIMATION_SOS_2:
            this->tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_MORSE_LETTER_O, 140);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_SOS_2, 140);
            break;
        case ANIMATION_SOS_3:
            this->tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_MORSE_LETTER_S, 100);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_SOS_3, 100);
            break;
        case ANIMATION_ALIEN_VOICE_1:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_1, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
        case ANIMATION_ALIEN_VOICE_2:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_2, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
        case ANIMATION_ALIEN_VOICE_3:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_3, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
        case ANIMATION_ALIEN_VOICE_4:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_4, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
            break;
        case ANIMATION_ALIEN_VOICE_5:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_5, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
            break;
        case ANIMATION_ALIEN_VOICE_6:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_6, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
            break;
        case ANIMATION_ALIEN_VOICE_7:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_7, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
            break;
        case ANIMATION_ALIEN_VOICE_8:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_8, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
            break;
        case ANIMATION_ALIEN_VOICE_9:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 100);
            tm1638plusPtr->setLedAnimationRandomDelay(1, 10, 25);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_9, 100);
            tm1638plusPtr->setSevenSegmentBothBlocksAnimationRandomDelay(80, 150, 1);
            break;
        case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_1:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_NOTES, 125);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_NOTES, 125);
            break;
        case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_2:
            break;
        case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_3:
            break;
        case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_4:
            break;
        case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_5:
            break;
        case ANIMATION_ALARM_REVERB:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER, 60);
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_1, 50);
            break;
        case ANIMATION_DIRTY_SYREN_1:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 300);
            // tm1638plusPtr->toggleLedAnimationInverseMode();
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_2, 300);
            break;
        case ANIMATION_DIRTY_SYREN_2:
            tm1638plusPtr->setLedAnimation(LED_ANIMATION_TYPE_VUMETER_MIRRORED, 400);
            tm1638plusPtr->toggleLedAnimationInverseMode();
            this->tm1638plusPtr->setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_3, 400);
            break;
        }
    }
    else
    {
        this->refreshAnimation(animation);
    }
}

void Events::stopAnimation(ANIMATION animation)
{
    bool stopAnimation = false;
    switch (animation)
    {
    case ANIMATION_LASER_SHOOT:

        if (this->currentLaserSamplesPlaying > 0)
        {
            this->currentLaserSamplesPlaying--;
        }
        if (this->currentLaserSamplesPlaying == 0)
        {
            stopAnimation = true;
        }
        break;
    case ANIMATION_SOS_1:
    case ANIMATION_SOS_2:
        stopAnimation = true;
        break;
    case ANIMATION_SOS_3:
        if (this->isPlayingSOSSamples)
        {
            this->isPlayingSOSSamples = false;
        }
        stopAnimation = true;
        break;
    case ANIMATION_ALIEN_VOICE_1:
    case ANIMATION_ALIEN_VOICE_2:
    case ANIMATION_ALIEN_VOICE_3:
    case ANIMATION_ALIEN_VOICE_4:
    case ANIMATION_ALIEN_VOICE_5:
    case ANIMATION_ALIEN_VOICE_6:
    case ANIMATION_ALIEN_VOICE_7:
    case ANIMATION_ALIEN_VOICE_8:
    case ANIMATION_ALIEN_VOICE_9:
        if (this->isPlayingAlienVoiceSamples)
        {
            this->isPlayingAlienVoiceSamples = false;
        }
        stopAnimation = true;
        break;
    case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_1:
        break;
    case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_2:
        break;
    case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_3:
        break;
    case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_4:
        break;
    case ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_5:
        if (this->isPlayingEncountersOnThirdPhaseSamples)
        {
            this->isPlayingEncountersOnThirdPhaseSamples = false;
        }
        stopAnimation = true;
        break;
    case ANIMATION_ALARM_REVERB:
    case SAMPLE_ALARM_REVERB_SEQ_1:
    case SAMPLE_ALARM_REVERB_SEQ_2:
    case SAMPLE_ALARM_REVERB_SEQ_3:
        this->isPlayingAlarmReverbSamples = false;
        stopAnimation = true;
        break;
    case ANIMATION_DIRTY_SYREN_1:
        this->isPlayingDirtySyren1Sample = false;
        stopAnimation = true;
        break;
    case ANIMATION_DIRTY_SYREN_2:
        this->isPlayingDirtySyren2Sample = false;
        stopAnimation = true;
        break;
    }
    if (stopAnimation)
    {
        this->currentAnimation = ANIMATION_DEFAULT;
        this->tm1638plusPtr->restoreDefaultLedAnimation();
        this->tm1638plusPtr->restoreDefaultSevenSegmentAnimation();
    }
}

void Events::loop(void)
{
    uint64_t currentTimestamp = millis();
    if (currentTimestamp - this->timerBackgroundSampleLastMillis > TIMER_BACKGROUND_SAMPLE_EVERY_MS)
    {
        this->timerBackgroundSampleLastMillis = currentTimestamp;
        if (this->timerBackgroundSample != SAMPLE_NONE)
        {
            switch (this->timerBackgroundSample)
            {
            case SAMPLE_ALARM_REVERB:
                this->isPlayingAlarmReverbSamples = true;
                break;
            case SAMPLE_DIRTY_SYREN_1:
                this->isPlayingDirtySyren1Sample = true;
                break;
            case SAMPLE_DIRTY_SYREN_2:
                this->isPlayingDirtySyren2Sample = true;
                break;
            }
            this->samplerPtr->queueSample(this->timerBackgroundSample);
        }
    }
}