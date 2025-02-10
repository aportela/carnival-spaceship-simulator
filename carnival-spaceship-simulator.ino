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

void setup()
{
    const uint8_t BUTTON_PINS[TOTAL_BUTTONS] = {11, 12, 13, 14, 15};
    buttons = new ExternalButtons(BUTTON_PINS);
    Serial.begin(9600);
    controlPanel = new ModuleTM1638plus(STROBE_TM, CLOCK_TM, DIO_TM, true);
    sampler = new Sampler(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN);
    Serial.println("Playing");
    sampler->play(SAMPLE_LASER1_SINGLE);
}

const float frequencies[] = {392.00, 440.00, 349.23, 174.61, 261.63};

void loop()
{
    switch (buttons->loop())
    {
    case EXTERNAL_BUTTON_1:
        sampler->play(SAMPLE_LASER1_SINGLE);
        Serial.println("BUTTON1");
        break;
    case EXTERNAL_BUTTON_2:
        sampler->play(SAMPLE_LASER1_SINGLE);
        Serial.println("BUTTON2");
        break;
    case EXTERNAL_BUTTON_3:
        sampler->play(SAMPLE_LASER1_SINGLE);
        Serial.println("BUTTON3");
        break;
    case EXTERNAL_BUTTON_4:
        sampler->play(SAMPLE_LASER1_SINGLE);
        Serial.println("BUTTON4");
        break;
    case EXTERNAL_BUTTON_5:
        sampler->play(SAMPLE_LASER1_SINGLE);
        Serial.println("BUTTON5");
        break;
    }
    controlPanel->loop();
    sampler->loop();
}
