#include <Arduino.h>
#include "Sampler.hpp"
#include "Samples.hpp"

Sampler::Sampler(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN)
{
    randomSeed(analogRead(0));
    this->out = new AudioOutputI2S();
    this->mixer = new AudioOutputMixer(32, this->out);
    for (uint8_t i = 0; i < MAX_SIMULTANEOUS_VOICES; i++)
    {
        this->stub[i] = this->mixer->NewInput();
        this->stub[i]->SetGain(0.5);
        this->activeVoices[i] = false;
        this->file[i] = nullptr;
        this->wav[i] = nullptr;
    }
}

Sampler::~Sampler()
{
    for (uint8_t i = 0; i < MAX_SIMULTANEOUS_VOICES; i++)
    {
        delete this->wav[i];
        delete this->stub[i];
    }
    delete this->mixer;
    delete this->out;
}

int8_t Sampler::getFirstFreeVoiceIndex(void)
{
    for (uint8_t i = 0; i < MAX_SIMULTANEOUS_VOICES; i++)
    {
        if (this->activeVoices[i] == false)
        {
            return (i);
        }
    }
    return (-1);
}

void Sampler::play(SAMPLE sample)
{
    this->currentSample = sample;
    int8_t firstFreeVoiceIndex = this->getFirstFreeVoiceIndex();
    if (firstFreeVoiceIndex != -1)
    {
        Serial.printf("Playing sample %d on index %d\n", sample, firstFreeVoiceIndex);
        switch (sample)
        {
        case SAMPLE_LASER1_SINGLE:
        case SAMPLE_LASER1_DOUBLE:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(laser_01_wav, laser_01_wav_len);
            this->doubleLaser = sample == SAMPLE_LASER1_DOUBLE;
            break;
        case SAMPLE_LASER2_SINGLE:
        case SAMPLE_LASER2_DOUBLE:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(laser_02_wav, laser_02_wav_len);
            this->doubleLaser = sample == SAMPLE_LASER2_DOUBLE;
            break;
        case SAMPLE_LASER3_SINGLE:
        case SAMPLE_LASER3_DOUBLE:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(laser_03_wav, laser_03_wav_len);
            this->doubleLaser = sample == SAMPLE_LASER3_DOUBLE;
            break;
        case SAMPLE_LASER4_SINGLE:
        case SAMPLE_LASER4_DOUBLE:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(laser_04_wav, laser_04_wav_len);
            this->doubleLaser = sample == SAMPLE_LASER4_DOUBLE;
            break;
        case SAMPLE_ALARM_REVERB:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alarm_reverb_wav, alarm_reverb_wav_len);
            break;
        case SAMPLE_DIRTY_SYREN_1:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(dirty_syren_01_wav, dirty_syren_01_wav_len);
            break;
        case SAMPLE_DIRTY_SYREN_2:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(dirty_syren_02_wav, dirty_syren_02_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(low_tone_01_wav, low_tone_01_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(low_tone_02_wav, low_tone_02_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(low_tone_03_wav, low_tone_03_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(low_tone_04_wav, low_tone_04_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(low_tone_05_wav, low_tone_05_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(high_tone_01_wav, high_tone_01_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(high_tone_02_wav, high_tone_02_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(high_tone_03_wav, high_tone_03_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(high_tone_04_wav, high_tone_04_wav_len);
            break;
        case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(high_tone_05_wav, high_tone_05_wav_len);
            break;
        case SAMPLE_ALIEN_VOICE_01:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_01_wav, alien_voice_01_wav_len);
            break;
        case SAMPLE_ALIEN_VOICE_02:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_02_wav, alien_voice_02_wav_len);
            break;
        case SAMPLE_ALIEN_VOICE_03:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_03_wav, alien_voice_03_wav_len);
            break;
        case SAMPLE_ALIEN_VOICE_04:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_04_wav, alien_voice_04_wav_len);
            break;
        }
        if (sample != SAMPLE_NONE)
        {
            if (this->wav[firstFreeVoiceIndex] == nullptr)
            {
                this->wav[firstFreeVoiceIndex] = new AudioGeneratorWAV();
            }
            this->wav[firstFreeVoiceIndex]->begin(this->file[firstFreeVoiceIndex], this->stub[firstFreeVoiceIndex]);
            this->activeVoices[firstFreeVoiceIndex] = true;
        }
    }
    else
    {
        Serial.println("All voices are in use");
    }
}

SAMPLE Sampler::getRandomSingleLaser(SAMPLE lastSample)
{
    SAMPLE sample = SAMPLE_NONE;
    switch (random(1, 5))
    {
    case 1:
        if (lastSample != SAMPLE_LASER1_SINGLE)
        {
            sample = SAMPLE_LASER1_SINGLE;
        }
        break;
    case 2:
        if (lastSample != SAMPLE_LASER2_SINGLE)
        {
            sample = SAMPLE_LASER2_SINGLE;
        }
        break;
    case 3:
        if (lastSample != SAMPLE_LASER3_SINGLE)
        {
            sample = SAMPLE_LASER3_SINGLE;
        }
        break;
    case 4:
        if (lastSample != SAMPLE_LASER4_SINGLE)
        {
            sample = SAMPLE_LASER4_SINGLE;
        }
        break;
    }
    return (sample);
}

SAMPLE Sampler::getRandomDoubleLaser(SAMPLE lastSample)
{
    SAMPLE sample = SAMPLE_NONE;
    switch (random(1, 5))
    {
    case 1:
        if (lastSample != SAMPLE_LASER1_DOUBLE)
        {
            sample = SAMPLE_LASER1_DOUBLE;
        }
        break;
    case 2:
        if (lastSample != SAMPLE_LASER2_DOUBLE)
        {
            sample = SAMPLE_LASER2_DOUBLE;
        }
        break;
    case 3:
        if (lastSample != SAMPLE_LASER3_DOUBLE)
        {
            sample = SAMPLE_LASER3_DOUBLE;
        }
        break;
    case 4:
        if (lastSample != SAMPLE_LASER4_DOUBLE)
        {
            sample = SAMPLE_LASER4_DOUBLE;
        }
        break;
    }
    return (sample);
}

void Sampler::loop(void)
{
    for (uint8_t i = 0; i < MAX_SIMULTANEOUS_VOICES; i++)
    {
        if (this->wav[i] != nullptr && this->wav[i]->isRunning())
        {
            // Serial.printf("%d isRunning\n", i);
            if (!this->wav[i]->loop())
            {
                Serial.printf("%d Not looping, stopping\n", i);
                this->wav[i]->stop();
                delete this->wav[i];
                this->wav[i] = nullptr;
                delete this->file[i];
                this->file[i] = nullptr;
                this->stub[i]->stop();
                this->activeVoices[i] = false;
                switch (this->currentSample)
                {
                case SAMPLE_LASER1_DOUBLE:
                    if (this->doubleLaser)
                    {
                        this->play(SAMPLE_LASER1_DOUBLE);
                        this->doubleLaser = false;
                    }
                    else
                    {
                        this->currentSample = SAMPLE_NONE;
                    }
                    break;
                case SAMPLE_LASER2_DOUBLE:
                    if (this->doubleLaser)
                    {
                        this->play(SAMPLE_LASER2_DOUBLE);
                        this->doubleLaser = false;
                    }
                    else
                    {
                        this->currentSample = SAMPLE_NONE;
                    }
                    break;
                case SAMPLE_LASER3_DOUBLE:
                    if (this->doubleLaser)
                    {
                        this->play(SAMPLE_LASER3_DOUBLE);
                        this->doubleLaser = false;
                    }
                    else
                    {
                        this->currentSample = SAMPLE_NONE;
                    }
                    break;
                case SAMPLE_LASER4_DOUBLE:
                    if (this->doubleLaser)
                    {
                        this->play(SAMPLE_LASER4_DOUBLE);
                        this->doubleLaser = false;
                    }
                    else
                    {
                        this->currentSample = SAMPLE_NONE;
                    }
                    break;
                case SAMPLE_DIRTY_SYREN_1:
                    this->play(SAMPLE_DIRTY_SYREN_2);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
                    this->play(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
                    this->play(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
                    this->play(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
                    this->play(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
                    this->play(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
                    this->play(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
                    this->play(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
                    this->play(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5);
                    break;
                case SAMPLE_ALIEN_VOICE_01:
                    this->play(SAMPLE_ALIEN_VOICE_02);
                    break;
                case SAMPLE_ALIEN_VOICE_02:
                    this->play(SAMPLE_ALIEN_VOICE_03);
                    break;
                case SAMPLE_ALIEN_VOICE_03:
                    this->play(SAMPLE_ALIEN_VOICE_04);
                    break;
                default:
                    this->currentSample = SAMPLE_NONE;
                    break;
                    Serial.println("No more samples, stopping");
                }
            }
        }
    }
}
