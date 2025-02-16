#include "src/modules/ExternalButtons/ExternalButtons.hpp"
#include "src/modules/TM1638plus/ModuleTM1638plus.hpp"
#include "src/modules/Audio/Sampler.hpp"
#include "src/Events.hpp"
#include "src/CommonDefines.hpp"

// External button PIN SETTINGS
#define EXTERNAL_BUTTON1_PIN 11
#define EXTERNAL_BUTTON2_PIN 12
#define EXTERNAL_BUTTON3_PIN 13
#define EXTERNAL_BUTTON4_PIN 14
#define EXTERNAL_BUTTON5_PIN 15

// TM1638 (model 1) module PIN SETTINGS
#define TM1638_STROBE_PIN 4 // strobe
#define TM1638_CLOCK_PIN 6  // clock
#define TM1638_DIO_PIN 7    // data

// Stereo DAC module PCM5102A PIN SETTINGS
#define DAC_I2S_BCK_PIN 26  // bit clock
#define DAC_I2S_LRCK_PIN 27 // left right clock
#define DAC_I2S_DATA_PIN 28 // data in

ExternalButtons *externalButtonsPtr = nullptr;
ModuleTM1638plus *tm1638plusPtr = nullptr;
Sampler *samplerPtr = nullptr;

Events *eventsPtr = nullptr;

#define START_LED_EFFECT_TYPE LED_EFFECT_TYPE_SCANNER
LED_EFFECT_TYPE currentLedEffectType = LED_EFFECT_TYPE_NONE;

void displayLaserShootCount(uint16_t count)
{
    if (count >= 10000) // only 4 digits (right block)
    {
        // reset counter
        // laserShoots = 0;
    }
    char buffer[5] = {'\0'};
    snprintf(buffer, sizeof(buffer), "%04d", count);
    tm1638plusPtr->displayTextOnRight7Segment(buffer, false, 0);
}

void onSampleStartPlaying(SAMPLE sample)
{
    eventsPtr->onSampleStarted(sample);
}

void onSampleStopPlaying(SAMPLE sample)
{
    eventsPtr->onSampleStopped(sample);
}

void setup()
{
    delay(500);
#ifdef DEBUG_SERIAL
    Serial.begin(115200);
    while (!Serial)
    {
        yield();
        delay(10);
    };
    Serial.println("########################################");
    Serial.println("Carnival spaceship simulator starting...");
    Serial.println("########################################");
    Serial.print("MAIN:: setting external buttons...");
#endif
    const uint8_t BUTTON_PINS[TOTAL_EXTERNAL_BUTTONS] = {EXTERNAL_BUTTON1_PIN, EXTERNAL_BUTTON2_PIN, EXTERNAL_BUTTON3_PIN, EXTERNAL_BUTTON4_PIN, EXTERNAL_BUTTON5_PIN};
    externalButtonsPtr = new ExternalButtons(BUTTON_PINS);
#ifdef DEBUG_SERIAL
    Serial.println("ok!");
    Serial.print("MAIN:: setting TM1638plus module...");
#endif
    tm1638plusPtr = new ModuleTM1638plus(TM1638_STROBE_PIN, TM1638_CLOCK_PIN, TM1638_DIO_PIN, true);
    if (START_LED_EFFECT_TYPE != LED_EFFECT_TYPE_NONE)
    {
        tm1638plusPtr->setLedEffect(START_LED_EFFECT_TYPE, DEFAULT_LED_MS_DELAY);
    }
#ifdef DEBUG_SERIAL
    Serial.println("ok!");
    Serial.print("MAIN:: setting PCM5102A module...");
#endif
    samplerPtr = new Sampler(DAC_I2S_BCK_PIN, DAC_I2S_LRCK_PIN, DAC_I2S_DATA_PIN, onSampleStartPlaying, onSampleStopPlaying);
#ifdef DEBUG_SERIAL
    Serial.println("ok!");
    Serial.print("MAIN:: setting global eventsPtr handler...");
#endif
    eventsPtr = new Events(externalButtonsPtr, tm1638plusPtr, samplerPtr);
#ifdef DEBUG_SERIAL
    Serial.println("ok!");
    Serial.println("MAIN:: playing init sample");
#endif
    samplerPtr->play(SAMPLE_ALARM_REVERB);
#ifdef DEBUG_SERIAL
    Serial.println("MAIN:: setup end");
#endif
}

void loop()
{
    eventsPtr->onExternalButton(externalButtonsPtr->getPressedButton());
    eventsPtr->onTM1638plusButton(tm1638plusPtr->getPressedButton());
    tm1638plusPtr->loop();
    samplerPtr->loop();
}
