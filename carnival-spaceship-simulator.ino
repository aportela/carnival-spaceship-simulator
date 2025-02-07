#include "src/modules/TM1638plus/ModuleTM1638plus.hpp"
#include "src/modules/Audio/Synth.hpp"
#include "src/modules/Audio/Sampler.hpp"

ModuleTM1638plus *controlPanel = nullptr;
Synth *synth = nullptr;
Sampler *sampler = nullptr;

#define I2S_BCK_PIN 26  // Bit Clock
#define I2S_LRCK_PIN 27 // Left Right Clock
#define I2S_DATA_PIN 28 // Data In

void setup()
{
    Serial.begin(9600);
    delay(2000);
    // controlPanel = new ModuleTM1638plus(STROBE_TM, CLOCK_TM, DIO_TM, true);
    // synth = new Synth(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN);
    sampler = new Sampler(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN);
    sampler->play(SAMPLE_LASER1_SINGLE);
}

const float frequencies[] = {392.00, 440.00, 349.23, 174.61, 261.63};

void loop()
{
    // controlPanel->loop();
    /*

    for (uint8_t i = 0; i < 5; i++)
    {
        synth->generateTone(frequencies[i], 1000, SINE);
        delay(50);
    }
    delay(2000);
    */
    sampler->loop();

    // delay(2000);
}
