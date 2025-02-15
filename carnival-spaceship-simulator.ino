#define DEBUG_SERIAL

#include "src/modules/ExternalButtons/ExternalButtons.hpp"
#include "src/modules/TM1638plus/ModuleTM1638plus.hpp"
#include "src/modules/Audio/Sampler.hpp"
#include "src/Events.hpp"

// TM1638 (model 1) module PIN SETTINGS
#define TM1638_STROBE_PIN 4 // strobe
#define TM1638_CLOCK_PIN 6  // clock
#define TM1638_DIO_PIN 7    // data

// Stereo DAC module PCM5102A PIN SETTINGS
#define DAC_I2S_BCK_PIN 26  // bit clock
#define DAC_I2S_LRCK_PIN 27 // left right clock
#define DAC_I2S_DATA_PIN 28 // data in

// External button PIN SETTINGS

#define EXTERNAL_BUTTON1_PIN 11
#define EXTERNAL_BUTTON2_PIN 12
#define EXTERNAL_BUTTON3_PIN 13
#define EXTERNAL_BUTTON4_PIN 14
#define EXTERNAL_BUTTON5_PIN 15

ExternalButtons *externalButtons = nullptr;
ModuleTM1638plus *tm1638plus = nullptr;
Sampler *sampler = nullptr;

Events *events = nullptr;

// available laser samples (for "shuffle" play)
const SAMPLE laserSamples[] = {SAMPLE_LASER1_SINGLE, SAMPLE_LASER2_SINGLE, SAMPLE_LASER3_SINGLE, SAMPLE_LASER4_SINGLE, SAMPLE_LASER1_DOUBLE, SAMPLE_LASER2_DOUBLE, SAMPLE_LASER3_DOUBLE, SAMPLE_LASER4_DOUBLE};
const uint8_t laserSamplesSize = sizeof(laserSamples) / sizeof(laserSamples[0]);
uint8_t currentLaserSamplesPlaying = 0;
uint16_t laserShoots = 0;

#define START_LED_EFFECT_TYPE LED_EFFECT_TYPE_SCANNER
LED_EFFECT_TYPE currentLedEffectType = LED_EFFECT_TYPE_NONE;

void displayLaserShootCount(uint16_t count)
{
    if (count >= 10000) // only 4 digits (right block)
    {
        // reset counter
        laserShoots = 0;
    }
    char buffer[5] = {'\0'};
    snprintf(buffer, sizeof(buffer), "%04d", count);
    tm1638plus->displayTextOnRight7Segment(buffer, false, 0);
}

void onSampleStartPlaying(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
        Serial.println("Started playing SAMPLE_LASER1_SINGLE");
        currentLaserSamplesPlaying++;
        displayLaserShootCount(++laserShoots);
        tm1638plus->displayTextOnLeft7Segment("1", true, 200);
        break;
    case SAMPLE_LASER2_SINGLE:
        Serial.println("Started playing SAMPLE_LASER2_SINGLE");
        currentLaserSamplesPlaying++;
        displayLaserShootCount(++laserShoots);
        tm1638plus->displayTextOnLeft7Segment("2", true, 200);
        break;
    case SAMPLE_LASER3_SINGLE:
        Serial.println("Started playing SAMPLE_LASER3_SINGLE");
        currentLaserSamplesPlaying++;
        displayLaserShootCount(++laserShoots);
        tm1638plus->displayTextOnLeft7Segment("3", true, 200);
        break;
    case SAMPLE_LASER4_SINGLE:
        Serial.println("Started playing SAMPLE_LASER4_SINGLE");
        currentLaserSamplesPlaying++;
        displayLaserShootCount(++laserShoots);
        tm1638plus->displayTextOnLeft7Segment("4", true, 200);
        break;
    case SAMPLE_LASER1_DOUBLE:
        Serial.println("Started playing SAMPLE_LASER1_DOUBLE");
        currentLaserSamplesPlaying++;
        displayLaserShootCount(laserShoots += 2);
        tm1638plus->displayTextOnLeft7Segment("11", true, 300);
        break;
    case SAMPLE_LASER2_DOUBLE:
        Serial.println("Started playing SAMPLE_LASER2_DOUBLE");
        currentLaserSamplesPlaying++;
        displayLaserShootCount(laserShoots += 2);
        tm1638plus->displayTextOnLeft7Segment("22", true, 300);
        break;
    case SAMPLE_LASER3_DOUBLE:
        Serial.println("Started playing SAMPLE_LASER3_DOUBLE");
        currentLaserSamplesPlaying++;
        displayLaserShootCount(laserShoots += 2);
        tm1638plus->displayTextOnLeft7Segment("33", true, 300);
        break;
    case SAMPLE_LASER4_DOUBLE:
        Serial.println("Started playing SAMPLE_LASER4_DOUBLE");
        currentLaserSamplesPlaying++;
        displayLaserShootCount(laserShoots += 2);
        tm1638plus->displayTextOnLeft7Segment("44", true, 300);
        break;
    case SAMPLE_ALARM_REVERB:
        Serial.println("Started playing SAMPLE_ALARM_REVERB");
        break;
    case SAMPLE_DIRTY_SYREN_1:
        Serial.println("Started playing SAMPLE_DIRTY_SYREN_1");
        break;
    case SAMPLE_DIRTY_SYREN_2:
        Serial.println("Started playing SAMPLE_DIRTY_SYREN_2");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
        Serial.println("Started playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5");
        break;
    case SAMPLE_SOS_01:
        Serial.println("Started playing SAMPLE_SOS_01");
        break;
    case SAMPLE_SOS_02:
        Serial.println("Started playing SAMPLE_SOS_02");
        break;
    case SAMPLE_SOS_03:
        Serial.println("Started playing SAMPLE_SOS_03");
        break;
    default:
        tm1638plus->displayTextOnLeft7Segment("    ", false, 0);
        break;
    }
}

void onSampleStopPlaying(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
        Serial.println("Stopped playing SAMPLE_LASER1_SINGLE");
        currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER2_SINGLE:
        Serial.println("Stopped playing SAMPLE_LASER2_SINGLE");
        currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER3_SINGLE:
        Serial.println("Stopped playing SAMPLE_LASER3_SINGLE");
        currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER4_SINGLE:
        Serial.println("Stopped playing SAMPLE_LASER4_SINGLE");
        currentLaserSamplesPlaying--;
        break;
    case SAMPLE_LASER1_DOUBLE:
        Serial.println("Stopped playing SAMPLE_LASER1_DOUBLE");
        currentLaserSamplesPlaying--;
        sampler->queueSample(SAMPLE_LASER1_SINGLE);
        break;
    case SAMPLE_LASER2_DOUBLE:
        Serial.println("Stopped playing SAMPLE_LASER2_DOUBLE");
        currentLaserSamplesPlaying--;
        sampler->queueSample(SAMPLE_LASER2_SINGLE);
        break;
    case SAMPLE_LASER3_DOUBLE:
        Serial.println("Stopped playing SAMPLE_LASER3_DOUBLE");
        currentLaserSamplesPlaying--;
        sampler->queueSample(SAMPLE_LASER3_SINGLE);
        break;
    case SAMPLE_LASER4_DOUBLE:
        Serial.println("Stopped playing SAMPLE_LASER4_DOUBLE");
        currentLaserSamplesPlaying--;
        sampler->queueSample(SAMPLE_LASER4_SINGLE);
        break;
    case SAMPLE_ALARM_REVERB:
        Serial.println("Stopped playing SAMPLE_ALARM_REVERB");
        break;
    case SAMPLE_DIRTY_SYREN_1:
        Serial.println("Stopped playing SAMPLE_DIRTY_SYREN_1");
        break;
    case SAMPLE_DIRTY_SYREN_2:
        Serial.println("Stopped playing SAMPLE_DIRTY_SYREN_2");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1");
        sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2");
        sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3");
        sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4");
        sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5");
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1");
        sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2");
        sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3");
        sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4");
        sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
        Serial.println("Stopped playing SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5");
        break;
    case SAMPLE_SOS_01:
        Serial.println("Stopped playing SAMPLE_SOS_01");
        sampler->queueSample(SAMPLE_SOS_02);
        break;
    case SAMPLE_SOS_02:
        Serial.println("Stopped playing SAMPLE_SOS_02");
        sampler->queueSample(SAMPLE_SOS_03);
        break;
    case SAMPLE_SOS_03:
        Serial.println("Stopped playing SAMPLE_SOS_03");
        break;
    }
    tm1638plus->displayTextOnLeft7Segment("    ", false, 0);
    tm1638plus->displayTextOnRight7Segment("    ", false, 0);
}

void setup()
{
    delay(2000);
    Serial.begin(9600);
#ifdef DEBUG_SERIAL
    Serial.println("########################################");
    Serial.println("Carnival spaceship simulator starting...");
    Serial.println("########################################");
#endif
    const uint8_t BUTTON_PINS[TOTAL_EXTERNAL_BUTTONS] = {EXTERNAL_BUTTON1_PIN, EXTERNAL_BUTTON2_PIN, EXTERNAL_BUTTON3_PIN, EXTERNAL_BUTTON4_PIN, EXTERNAL_BUTTON5_PIN};
#ifdef DEBUG_SERIAL
    Serial.print("Setting external buttons...");
#endif
    externalButtons = new ExternalButtons(BUTTON_PINS);
#ifdef DEBUG_SERIAL
    Serial.println("ok!");
    Serial.print("Setting TM1638plus module...");
#endif
    tm1638plus = new ModuleTM1638plus(TM1638_STROBE_PIN, TM1638_CLOCK_PIN, TM1638_DIO_PIN, true);
    tm1638plus->setLedEffect(START_LED_EFFECT_TYPE, DEFAULT_LED_MS_DELAY);
#ifdef DEBUG_SERIAL
    Serial.println("ok!");
    Serial.print("Setting PCM5102A module...");
#endif
    sampler = new Sampler(DAC_I2S_BCK_PIN, DAC_I2S_LRCK_PIN, DAC_I2S_DATA_PIN, onSampleStartPlaying, onSampleStopPlaying);
#ifdef DEBUG_SERIAL
    Serial.println("ok!");
    Serial.print("Setting global events handler...");
#endif
    events = new Events();
#ifdef DEBUG_SERIAL
    Serial.println("ok!");
    Serial.println("Playing init sample");
#endif
    sampler->play(SAMPLE_ALARM_REVERB);
}

void loop()
{
    // events->onExternalButton(externalButtons->loop());
    switch (externalButtons->loop())
    {
    case EXTERNAL_BUTTON_1:
#ifdef DEBUG_SERIAL
        Serial.println("External button 1 pressed... enqueue random laser sample");
#endif
        sampler->queueSample(laserSamples[random(0, laserSamplesSize)]);
        break;
    case EXTERNAL_BUTTON_2:
#ifdef DEBUG_SERIAL
        Serial.println("External button 2 pressed... enqueue random laser sample");
#endif
        sampler->queueSample(laserSamples[random(0, laserSamplesSize)]);
        break;
    case EXTERNAL_BUTTON_3:
#ifdef DEBUG_SERIAL
        Serial.println("External button 3 pressed");
#endif
        break;
    case EXTERNAL_BUTTON_4:
#ifdef DEBUG_SERIAL
        Serial.println("External button 4 pressed");
#endif
        break;
    case EXTERNAL_BUTTON_5:
#ifdef DEBUG_SERIAL
        Serial.println("External button 5 pressed");
#endif
        break;
    }
    TM1638plusBUTTON tm1638plusPressedButton = tm1638plus->checkPressedButton();
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
    tm1638plus->loop();
    sampler->loop();
}
