#include "Synth.hpp"

Synth::Synth(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN)
{
    this->i2s = new I2S(INPUT_PULLUP);
    this->i2s->setBCLK(I2S_BCK_PIN);
    this->i2s->setDATA(I2S_DATA_PIN);
    this->i2s->setMCLK(I2S_LRCK_PIN);
    this->i2s->setFrequency(SAMPLE_RATE);
    this->i2s->setBitsPerSample(BITS_PER_SAMPLE);
    this->i2s->begin();
}

Synth::~Synth()
{
    this->i2s->end();
    delete this->i2s;
    this->i2s = nullptr;
}

void Synth::generateTone(float frequency, int duration, Waveform waveformType)
{
    const int bufferSize = 64;
    int16_t sampleBuffer[bufferSize * 2];
    float phase = 0.0;
    float phaseIncrement = frequency / SAMPLE_RATE;

    int totalSamples = (SAMPLE_RATE * duration) / 1000;

    for (int i = 0; i < totalSamples; i += bufferSize)
    {
        int samplesToGenerate = min(bufferSize, totalSamples - i);

        for (int j = 0; j < samplesToGenerate; j++)
        {
            int16_t sample = 0;

            switch (waveformType)
            {
            case SINE:
                sample = sin(phase) * 32767;
                break;
            case SQUARE:
                sample = (sin(phase) >= 0) ? 32767 : -32767;
                break;
            case SAWTOOTH:
                sample = (phase < 1.0) ? (phase * 32767) : ((2.0 - phase) * 32767);
                break;
            case TRIANGLE:
                sample = (phase < 0.5) ? (phase * 65534 - 32767) : ((1.0 - phase) * 65534 - 32767);
                break;
            }

            sampleBuffer[j * 2] = sample;     // LEFT channel
            sampleBuffer[j * 2 + 1] = sample; // RIGHT channel

            phase += phaseIncrement;
            if (phase > 1.0)
            {
                phase -= 1.0;
            }
        }

        uint8_t *byteBuffer = reinterpret_cast<uint8_t *>(sampleBuffer);

        this->i2s->write(byteBuffer, samplesToGenerate * 2 * sizeof(int16_t));
    }
}
