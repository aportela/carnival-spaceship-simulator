#include <cstring>
#include <Arduino.h>
#include "src/modules/ExternalButtons/ExternalButtons.hpp"
#include "src/modules/TM1638plus/ModuleTM1638plus.hpp"
#include "src/modules/Audio/Sampler.hpp"
#include "src/Events.hpp"
#include "src/CommonDefines.hpp"

ExternalButtons *externalButtonsPtr = nullptr;
ModuleTM1638plus *tm1638plusPtr = nullptr;
Sampler *samplerPtr = nullptr;

Events *eventsPtr = nullptr;

uint64_t lastDirtySyrenMillis = millis();

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
    randomSeed(analogRead(A0));
    delay(500);
#ifdef DEBUG_SERIAL
    Serial.begin(115200);
    while (!Serial && millis() < 500)
    {
        yield();
        delay(10);
    };
    Serial.println("########################################");
    Serial.println("Carnival spaceship simulator starting...");
    Serial.println("########################################");
    Serial.println("MAIN:: begin setup() method");
    Serial.println("MAIN:: begin setting external buttons");
#endif
    const uint8_t BUTTON_PINS[TOTAL_EXTERNAL_BUTTONS] = {EXTERNAL_BUTTON1_PIN, EXTERNAL_BUTTON2_PIN, EXTERNAL_BUTTON3_PIN, EXTERNAL_BUTTON4_PIN, EXTERNAL_BUTTON5_PIN};
    externalButtonsPtr = new ExternalButtons(BUTTON_PINS);
#ifdef DEBUG_SERIAL
    Serial.println("MAIN:: end setting external buttons");
    Serial.println("MAIN:: begin setting TM1638plus module");
#endif
    tm1638plusPtr = new ModuleTM1638plus(TM1638_STROBE_PIN, TM1638_CLOCK_PIN, TM1638_DIO_PIN, true);
#ifdef START_LED_ANIMATION_TYPE
    if (START_LED_ANIMATION_TYPE != LED_ANIMATION_TYPE_NONE)
    {
        tm1638plusPtr->setLedAnimation(START_LED_ANIMATION_TYPE, START_LED_ANIMATION_DELAY, true);
    }
#endif
#ifdef START_SEVEN_SEGMENT_ANIMATION_TYPE
    if (START_SEVEN_SEGMENT_ANIMATION_TYPE != SEVEN_SEGMENT_ANIMATION_TYPE_NONE)
    {
        tm1638plusPtr->setSevenSegmentAnimation(START_SEVEN_SEGMENT_ANIMATION_TYPE, START_SEVEN_SEGMENT_ANIMATION_DELAY, 0, true);
    }
#endif
#ifdef DEBUG_SERIAL
    Serial.println("MAIN:: end setting TM1638plus module");
    Serial.println("MAIN:: begin setting PCM5102A module");
#endif
    samplerPtr = new Sampler(DAC_I2S_BCK_PIN, DAC_I2S_LRCK_PIN, DAC_I2S_DATA_PIN, onSampleStartPlaying, onSampleStopPlaying);
#ifdef DEBUG_SERIAL
    Serial.println("MAIN:: end setting PCM5102A module");
    Serial.println("MAIN:: begin setting global eventsPtr handler");
#endif
    eventsPtr = new Events(externalButtonsPtr, tm1638plusPtr, samplerPtr);
#ifdef DEBUG_SERIAL
    Serial.println("MAIN:: end setting global eventsPtr handler");
    Serial.println("MAIN:: playing init sample");
#endif
    samplerPtr->play(SAMPLE_ALARM_REVERB);
#ifdef DEBUG_SERIAL
    Serial.println("MAIN:: end setup() method");
#endif
}

void loop()
{
    eventsPtr->onExternalButton(externalButtonsPtr->getPressedButton());
    eventsPtr->onTM1638plusButton(tm1638plusPtr->getPressedButton());
    eventsPtr->loop();
    tm1638plusPtr->loop();
    samplerPtr->loop();
}
