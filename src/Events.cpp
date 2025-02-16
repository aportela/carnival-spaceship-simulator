#include "Events.hpp"
#include <Arduino.h>

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
        switch (button)
        {
        case EXTERNAL_BUTTON_1:
#ifdef DEBUG_SERIAL
                Serial.println("EVENTS:: external button 1 pressed... enqueue random laser sample");
#endif
                this->samplerPtr->queueSample(laserSamples[random(0, laserSamplesSize)]);
                break;
        case EXTERNAL_BUTTON_2:
#ifdef DEBUG_SERIAL
                Serial.println("EVENTS:: external button 2 pressed... enqueue random laser sample");
#endif
                this->samplerPtr->queueSample(laserSamples[random(0, laserSamplesSize)]);
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
                Serial.println("EVENTS:: external button 5 pressed");
#endif
                break;
        }
}

void Events::onTM1638plusButton(TM1638plusBUTTON button)
{
        if (button != TM1638plusBUTTON_NONE)
        {
                switch (button)
                {
                case TM1638plusBUTTON_S1:
                        Serial.println("TM1638plus button 1 pressed... toggle led effect");
                        this->tm1638plusPtr->toggleLedEffect();
                        break;
                case TM1638plusBUTTON_S2:
                        Serial.println("TM1638plus button 2 pressed...");
                        break;
                case TM1638plusBUTTON_S3:
                        Serial.println("TM1638plus button 3 pressed...");
                        break;
                case TM1638plusBUTTON_S4:
                        Serial.println("TM1638plus button 4 pressed...");
                        break;
                case TM1638plusBUTTON_S5:
                        Serial.println("TM1638plus button 5 pressed...");
                        break;
                case TM1638plusBUTTON_S6:
                        Serial.println("TM1638plus button 6 pressed...");
                        break;
                case TM1638plusBUTTON_S7:
                        Serial.println("TM1638plus button 7 pressed...");
                        break;
                case TM1638plusBUTTON_S8:
                        Serial.println("TM1638plus button 8 pressed...");
                        break;
                }
        }
}

void Events::onSampleStarted(SAMPLE sample)
{
        Serial.println("NEW");
        switch (sample)
        {
        case SAMPLE_LASER1_SINGLE:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_LASER1_SINGLE");
#endif
                // currentLaserSamplesPlaying++;
                // displayLaserShootCount(++laserShoots);
                tm1638plusPtr->displayTextOnLeft7Segment("1", true, 200);
                break;
        case SAMPLE_LASER2_SINGLE:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_LASER2_SINGLE");
#endif
                // currentLaserSamplesPlaying++;
                // displayLaserShootCount(++laserShoots);
                tm1638plusPtr->displayTextOnLeft7Segment("2", true, 200);
                break;
        case SAMPLE_LASER3_SINGLE:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_LASER3_SINGLE");
#endif
                // currentLaserSamplesPlaying++;
                // displayLaserShootCount(++laserShoots);
                tm1638plusPtr->displayTextOnLeft7Segment("3", true, 200);
                break;
        case SAMPLE_LASER4_SINGLE:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_LASER4_SINGLE");
#endif
                // currentLaserSamplesPlaying++;
                // displayLaserShootCount(++laserShoots);
                tm1638plusPtr->displayTextOnLeft7Segment("4", true, 200);
                break;
        case SAMPLE_LASER1_DOUBLE:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_LASER1_DOUBLE");
#endif
                // currentLaserSamplesPlaying++;
                // displayLaserShootCount(laserShoots += 2);
                tm1638plusPtr->displayTextOnLeft7Segment("11", true, 300);
                break;
        case SAMPLE_LASER2_DOUBLE:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_LASER2_DOUBLE");
#endif
                // currentLaserSamplesPlaying++;
                // displayLaserShootCount(laserShoots += 2);
                tm1638plusPtr->displayTextOnLeft7Segment("22", true, 300);
                break;
        case SAMPLE_LASER3_DOUBLE:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_LASER3_DOUBLE");
#endif
                // currentLaserSamplesPlaying++;
                // displayLaserShootCount(laserShoots += 2);
                tm1638plusPtr->displayTextOnLeft7Segment("33", true, 300);
                break;
        case SAMPLE_LASER4_DOUBLE:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_LASER4_DOUBLE");
#endif
                // currentLaserSamplesPlaying++;
                // displayLaserShootCount(laserShoots += 2);
                tm1638plusPtr->displayTextOnLeft7Segment("44", true, 300);
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
                break;
        case SAMPLE_SOS_02:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_SOS_02");
#endif
                break;
        case SAMPLE_SOS_03:
#ifdef DEBUG_SERIAL
                Serial.println("Started playing SAMPLE_SOS_03");
#endif
                break;
        default:
#ifdef DEBUG_SERIAL
#endif
                tm1638plusPtr->displayTextOnLeft7Segment("    ", false, 0);
                break;
        }
}

void Events::onSampleStopped(SAMPLE sample)
{
        Serial.println("NEW");
        switch (sample)
        {
        case SAMPLE_LASER1_SINGLE:
#ifdef DEBUG_SERIAL
                Serial.println("Stopped playing SAMPLE_LASER1_SINGLE");
#endif
                // currentLaserSamplesPlaying--;
                break;
        case SAMPLE_LASER2_SINGLE:
#ifdef DEBUG_SERIAL
                Serial.println("Stopped playing SAMPLE_LASER2_SINGLE");
#endif
                // currentLaserSamplesPlaying--;
                break;
        case SAMPLE_LASER3_SINGLE:
#ifdef DEBUG_SERIAL
                Serial.println("Stopped playing SAMPLE_LASER3_SINGLE");
#endif
                // currentLaserSamplesPlaying--;
                break;
        case SAMPLE_LASER4_SINGLE:
#ifdef DEBUG_SERIAL
                Serial.println("Stopped playing SAMPLE_LASER4_SINGLE");
#endif
                // currentLaserSamplesPlaying--;
                break;
        case SAMPLE_LASER1_DOUBLE:
#ifdef DEBUG_SERIAL
                Serial.println("Stopped playing SAMPLE_LASER1_DOUBLE");
#endif
                // currentLaserSamplesPlaying--;
                samplerPtr->queueSample(SAMPLE_LASER1_SINGLE);
                break;
        case SAMPLE_LASER2_DOUBLE:
#ifdef DEBUG_SERIAL
                Serial.println("Stopped playing SAMPLE_LASER2_DOUBLE");
#endif
                // currentLaserSamplesPlaying--;
                samplerPtr->queueSample(SAMPLE_LASER2_SINGLE);
                break;
        case SAMPLE_LASER3_DOUBLE:
#ifdef DEBUG_SERIAL
                Serial.println("Stopped playing SAMPLE_LASER3_DOUBLE");
#endif
                // currentLaserSamplesPlaying--;
                samplerPtr->queueSample(SAMPLE_LASER3_SINGLE);
                break;
        case SAMPLE_LASER4_DOUBLE:
#ifdef DEBUG_SERIAL
                Serial.println("Stopped playing SAMPLE_LASER4_DOUBLE");
#endif
                // currentLaserSamplesPlaying--;
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
                break;
        default:
#ifdef DEBUG_SERIAL
#endif
                break;
        }
        tm1638plusPtr->displayTextOnLeft7Segment("    ", false, 0);
        tm1638plusPtr->displayTextOnRight7Segment("    ", false, 0);
}

void Events::loop(void)
{
        if (this->externalButtonsPtr->getPressedButton() != EXTERNAL_BUTTON_NONE)
        {
                Serial.println("PULSADO");
        }
        // this->onExternalButton(this->externalButtonsPtr->getPressedButton());
        /*
        if (this->externalButtonsPtr)
        {
                Serial.println();
        }
                */
        //
        /*
        TM1638plusBUTTON tm1638plusPressedButton = tm1638plus->getPressedButton();
        if (tm1638plusPressedButton != TM1638plusBUTTON_NONE)
        {
            switch (tm1638plusPressedButton)
            {
            case TM1638plusBUTTON_S1:
    #ifdef DEBUG_SERIAL
                Serial.println("TM1638plus button 1 pressed");
    #endif
                switch (currentLedEffectType)
                {
                case LED_EFFECT_TYPE_NONE:
                    currentLedEffectType = LED_EFFECT_TYPE_SCANNER;
                    break;
                case LED_EFFECT_TYPE_SCANNER:
                    currentLedEffectType = LED_EFFECT_TYPE_CHASE;
                    break;
                case LED_EFFECT_TYPE_CHASE:
                    currentLedEffectType = LED_EFFECT_TYPE_VUMETER;
                    break;
                case LED_EFFECT_TYPE_VUMETER:
                    currentLedEffectType = LED_EFFECT_TYPE_VUMETER_MIRRORED;
                    break;
                case LED_EFFECT_TYPE_VUMETER_MIRRORED:
                    currentLedEffectType = LED_EFFECT_TYPE_ALTERNATE;
                    break;
                case LED_EFFECT_TYPE_ALTERNATE:
                    currentLedEffectType = LED_EFFECT_TYPE_INTERMITENT;
                    break;
                case LED_EFFECT_TYPE_INTERMITENT:
                    currentLedEffectType = LED_EFFECT_TYPE_NONE;
                    break;
                default:
                    currentLedEffectType = LED_EFFECT_TYPE_NONE;
                    break;
                }
                tm1638plus->setLedEffect(currentLedEffectType, DEFAULT_LED_MS_DELAY);
                break;
            case TM1638plusBUTTON_S2:
    #ifdef DEBUG_SERIAL
                Serial.println("TM1638plus button 2 pressed");
    #endif
                tm1638plus->toggleLedInverseMode();
                break;
            case TM1638plusBUTTON_S3:
    #ifdef DEBUG_SERIAL
                Serial.println("TM1638plus button 3 pressed");
    #endif
                break;
            case TM1638plusBUTTON_S4:
    #ifdef DEBUG_SERIAL
                Serial.println("TM1638plus button 4 pressed");
    #endif
                // tm1638plus->toggleSevenSegmentEffect();
                break;
            case TM1638plusBUTTON_S5:
    #ifdef DEBUG_SERIAL
                Serial.println("TM1638plus button 5 pressed");
    #endif
                // tm1638plus->toggleSevenSegmentSpeed();
                break;
            case TM1638plusBUTTON_S6:
    #ifdef DEBUG_SERIAL
                Serial.println("TM1638plus button 6 pressed");
    #endif
                // tm1638plus->toggleSevenSegmentSpeed();
                break;
            case TM1638plusBUTTON_S7:
    #ifdef DEBUG_SERIAL
                Serial.println("TM1638plus button 6 pressed");
    #endif

                // sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1);
                break;
            case TM1638plusBUTTON_S8:
    #ifdef DEBUG_SERIAL
                Serial.println("TM1638plus button 6 pressed");
    #endif
                // sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1);
                break;
            }
        }
        */
}
