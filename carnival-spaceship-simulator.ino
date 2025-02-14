#include "src/modules/TM1638plus/ModuleTM1638plus.hpp"
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

void setup()
{
    const uint8_t BUTTON_PINS[TOTAL_BUTTONS] = {11, 12, 13, 14, 15};
    buttons = new ExternalButtons(BUTTON_PINS);
    Serial.begin(9600);
    controlPanel = new ModuleTM1638plus(STROBE_TM, CLOCK_TM, DIO_TM, true);
    sampler = new Sampler(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN);
    delay(2000);
    Serial.println("Starting...");
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
    controlPanel->loop();
    sampler->loop();
}
