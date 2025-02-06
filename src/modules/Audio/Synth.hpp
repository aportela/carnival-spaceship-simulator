
#ifndef MODULE_SYNTH
#define MODULE_SYNTH

#include <I2S.h>

#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16

enum Waveform
{
    SINE,
    SQUARE,
    SAWTOOTH,
    TRIANGLE
};

class Synth
{
private:
    I2S *i2s = nullptr;

public:
    Synth(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN);
    ~Synth(void);
    void generateTone(float frequency, int duration, Waveform waveformType);
};

#endif // MODULE_SYNTH
