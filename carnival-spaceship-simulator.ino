#include "src/modules/TM1638plus/ModuleTM1638plus.hpp"
#include "src/modules/Audio/Synth.hpp"

ModuleTM1638plus *controlPanel = nullptr;
Synth *synth = nullptr;

#define I2S_BCK_PIN 26  // Bit Clock
#define I2S_LRCK_PIN 27 // Left Right Clock
#define I2S_DATA_PIN 28 // Data In

void setup()
{
    Serial.begin(9600);
    delay(1000);
    // controlPanel = new ModuleTM1638plus(STROBE_TM, CLOCK_TM, DIO_TM, true);
    synth = new Synth(I2S_BCK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN);
}

const float frequencies[] = {392.00, 440.00, 349.23, 174.61, 261.63};

void loop()
{
    // controlPanel->loop();
    for (uint8_t i = 0; i < 5; i++)
    {
        synth->generateTone(frequencies[i], 1000, SINE);
        delay(50);
    }
    delay(2000);
}
