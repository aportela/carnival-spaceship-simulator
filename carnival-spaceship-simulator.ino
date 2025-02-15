#include "src/modules/TM1638plus/ModuleTM1638plus.hpp"
#include "src/modules/TM1638plus/Buttons/TM1638plusButtons.hpp"
#include "src/modules/Audio/Sampler.hpp"
#include "src/modules/ExternalButtons/ExternalButtons.hpp"

ExternalButtons *buttons = nullptr;
ModuleTM1638plus *controlPanel = nullptr;
Sampler *sampler = nullptr;

#define STROBE_TM 4 // strobe
#define CLOCK_TM 6  // clock
#define DIO_TM 7    // data

#define I2S_BCK_PIN 26  // Bit Clock
#define I2S_LRCK_PIN 27 // Left Right Clock
#define I2S_DATA_PIN 28 // Data In

const SAMPLE laserSamples[] = {SAMPLE_LASER1_SINGLE, SAMPLE_LASER2_SINGLE, SAMPLE_LASER3_SINGLE, SAMPLE_LASER4_SINGLE, SAMPLE_LASER1_DOUBLE, SAMPLE_LASER2_DOUBLE, SAMPLE_LASER3_DOUBLE, SAMPLE_LASER4_DOUBLE};
const uint8_t laserSamplesSize = sizeof(laserSamples) / sizeof(laserSamples[0]);

LED_EFFECT_TYPE currentLedEffectType = LED_EFFECT_TYPE_SCANNER;

uint16_t laserShoots = 0;

void displayLaserShootCount(uint16_t count)
{
    if (count >= 10000) // only 4 digits (right block)
    {
        // reset counter
        laserShoots = 0;
    }
    char buffer[5] = {'\0'};
    snprintf(buffer, sizeof(buffer), "%04d", count);
    controlPanel->displayTextOnRight7Segment(buffer, false, 0);
}

void onSampleStartPlaying(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
        Serial.println("Started playing SAMPLE_LASER1_SINGLE");
        displayLaserShootCount(++laserShoots);
        controlPanel->displayTextOnLeft7Segment("1", true, 200);
        break;
    case SAMPLE_LASER2_SINGLE:
        Serial.println("Started playing SAMPLE_LASER2_SINGLE");
        displayLaserShootCount(++laserShoots);
        controlPanel->displayTextOnLeft7Segment("2", true, 200);
        break;
    case SAMPLE_LASER3_SINGLE:
        Serial.println("Started playing SAMPLE_LASER3_SINGLE");
        displayLaserShootCount(++laserShoots);
        controlPanel->displayTextOnLeft7Segment("3", true, 200);
        break;
    case SAMPLE_LASER4_SINGLE:
        Serial.println("Started playing SAMPLE_LASER4_SINGLE");
        displayLaserShootCount(++laserShoots);
        controlPanel->displayTextOnLeft7Segment("4", true, 200);
        break;
    case SAMPLE_LASER1_DOUBLE:
        Serial.println("Started playing SAMPLE_LASER1_DOUBLE");
        displayLaserShootCount(laserShoots += 2);
        controlPanel->displayTextOnLeft7Segment("11", true, 300);
        break;
    case SAMPLE_LASER2_DOUBLE:
        Serial.println("Started playing SAMPLE_LASER2_DOUBLE");
        displayLaserShootCount(laserShoots += 2);
        controlPanel->displayTextOnLeft7Segment("22", true, 300);
        break;
    case SAMPLE_LASER3_DOUBLE:
        Serial.println("Started playing SAMPLE_LASER3_DOUBLE");
        displayLaserShootCount(laserShoots += 2);
        controlPanel->displayTextOnLeft7Segment("33", true, 300);
        break;
    case SAMPLE_LASER4_DOUBLE:
        Serial.println("Started playing SAMPLE_LASER4_DOUBLE");
        displayLaserShootCount(laserShoots += 2);
        controlPanel->displayTextOnLeft7Segment("44", true, 300);
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
        controlPanel->displayTextOnLeft7Segment("    ", false, 0);
        break;
    }
}

void onSampleStopPlaying(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
        Serial.println("Stopped playing SAMPLE_LASER1_SINGLE");
        break;
    case SAMPLE_LASER2_SINGLE:
        Serial.println("Stopped playing SAMPLE_LASER2_SINGLE");
        break;
    case SAMPLE_LASER3_SINGLE:
        Serial.println("Stopped playing SAMPLE_LASER3_SINGLE");
        break;
    case SAMPLE_LASER4_SINGLE:
        Serial.println("Stopped playing SAMPLE_LASER4_SINGLE");
        break;
    case SAMPLE_LASER1_DOUBLE:
        Serial.println("Stopped playing SAMPLE_LASER1_DOUBLE");
        sampler->queueSample(SAMPLE_LASER1_SINGLE);
        break;
    case SAMPLE_LASER2_DOUBLE:
        Serial.println("Stopped playing SAMPLE_LASER2_DOUBLE");
        sampler->queueSample(SAMPLE_LASER2_SINGLE);
        break;
    case SAMPLE_LASER3_DOUBLE:
        Serial.println("Stopped playing SAMPLE_LASER3_DOUBLE");
        sampler->queueSample(SAMPLE_LASER3_SINGLE);
        break;
    case SAMPLE_LASER4_DOUBLE:
        Serial.println("Stopped playing SAMPLE_LASER4_DOUBLE");
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
    controlPanel->displayTextOnLeft7Segment("    ", false, 0);
    controlPanel->displayTextOnRight7Segment("    ", false, 0);
}

void setup()
{
    delay(2000);
    Serial.println("Starting...");
    const uint8_t BUTTON_PINS[TOTAL_BUTTONS] = {11, 12, 13, 14, 15};
    buttons = new ExternalButtons(BUTTON_PINS);
    Serial.begin(9600);
    controlPanel = new ModuleTM1638plus(STROBE_TM, CLOCK_TM, DIO_TM, true);
    sampler = new Sampler(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN, onSampleStartPlaying, onSampleStopPlaying);
    controlPanel->setLedEffect(currentLedEffectType, DEFAULT_LED_MS_DELAY);
    sampler->play(SAMPLE_ALARM_REVERB);
}

void loop()
{
    switch (buttons->loop())
    {
    case EXTERNAL_BUTTON_1:
        Serial.println("BUTTON1");
        sampler->queueSample(laserSamples[random(0, laserSamplesSize)]);
        break;
    case EXTERNAL_BUTTON_2:
        Serial.println("BUTTON2");
        sampler->queueSample(laserSamples[random(0, laserSamplesSize)]);
        break;
    case EXTERNAL_BUTTON_3:
        Serial.println("BUTTON3");
        // sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1);
        sampler->queueSample(SAMPLE_DIRTY_SYREN_1);
        break;
    case EXTERNAL_BUTTON_4:
        Serial.println("BUTTON4");
        // sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1);
        sampler->queueSample(SAMPLE_DIRTY_SYREN_2);
        break;
    case EXTERNAL_BUTTON_5:
        Serial.println("BUTTON5");
        sampler->queueSample(SAMPLE_SOS_01);
        break;
    }
    TM1638plusBUTTON controlPanelPressedButton = controlPanel->checkPressedButton();
    if (controlPanelPressedButton != TM1638plusBUTTON_NONE)
    {
        Serial.println("Control panel button pressed");
        switch (controlPanelPressedButton)
        {
        case TM1638plusBUTTON_S1:
            switch (currentLedEffectType)
            {
            case LED_EFFECT_TYPE_NONE:
                currentLedEffectType = LED_EFFECT_TYPE_SCANNER;
                break;
            case LED_EFFECT_TYPE_SCANNER:
                currentLedEffectType = LED_EFFECT_TYPE_CHASE;
                break;
            case LED_EFFECT_TYPE_CHASE:
                currentLedEffectType = LED_EFFECT_VUMETER;
                break;
            case LED_EFFECT_VUMETER:
                currentLedEffectType = LED_EFFECT_VUMETER_MIRRORED;
                break;
            case LED_EFFECT_VUMETER_MIRRORED:
                currentLedEffectType = LED_EFFECT_ALTERNATE;
                break;
            case LED_EFFECT_ALTERNATE:
                currentLedEffectType = LED_EFFECT_INTERMITENT;
                break;
            case LED_EFFECT_INTERMITENT:
                currentLedEffectType = LED_EFFECT_TYPE_NONE;
                break;
            default:
                currentLedEffectType = LED_EFFECT_TYPE_NONE;
                break;
            }
            controlPanel->setLedEffect(currentLedEffectType, DEFAULT_LED_MS_DELAY);
            break;
        case TM1638plusBUTTON_S2:
            controlPanel->toggleLedInverseMode();
            break;
        case TM1638plusBUTTON_S3:
            break;
        case TM1638plusBUTTON_S4:
            controlPanel->toggleSevenSegmentEffect();
            break;
        case TM1638plusBUTTON_S5:
            // controlPanel->toggleSevenSegmentSpeed();
            break;
        case TM1638plusBUTTON_S7:
            sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1);
            break;
        case TM1638plusBUTTON_S8:
            sampler->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1);
            break;
        }
    }
    controlPanel->loop();
    sampler->loop();
}
