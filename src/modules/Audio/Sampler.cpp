#include "Sampler.hpp"
#include "../../data/samples/laser.h"

Sampler::Sampler(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN)
{

    this->out = new AudioOutputI2S();
    this->mixer = new AudioOutputMixer(32, this->out);
    this->stub[0] = this->mixer->NewInput();
    this->stub[0]->SetGain(0.5);
}

Sampler::~Sampler()
{
    delete this->wav[0];
    delete this->mixer;
    delete this->stub[0];
    delete this->out;
}

void Sampler::play(SAMPLE sample)
{
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
        this->file[0] = new AudioFileSourcePROGMEM(laser_wav, laser_wav_len);
        this->wav[0] = new AudioGeneratorWAV();
        this->wav[0]->begin(this->file[0], this->stub[0]);
        break;
    }
}

void Sampler::loop(void)
{
    if (this->wav[0]->isRunning())
    {
        if (!this->wav[0]->loop())
        {
            this->wav[0]->stop();
            this->stub[0]->stop();
        }
    }
}