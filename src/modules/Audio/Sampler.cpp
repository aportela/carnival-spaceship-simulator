#include "Sampler.hpp"
#include "Samples.hpp"

Sampler::Sampler(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN)
{
    randomSeed(analogRead(0));
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
    this->currentSample = sample;
    switch (sample)
    {
    case SAMPLE_LASER1_SINGLE:
        this->file[0] = new AudioFileSourcePROGMEM(laser_01_wav, laser_01_wav_len);
        break;
    case SAMPLE_LASER2_SINGLE:
        this->file[0] = new AudioFileSourcePROGMEM(laser_02_wav, laser_02_wav_len);
        break;
    case SAMPLE_LASER3_SINGLE:
        this->file[0] = new AudioFileSourcePROGMEM(laser_03_wav, laser_03_wav_len);
        break;
    case SAMPLE_LASER4_SINGLE:
        this->file[0] = new AudioFileSourcePROGMEM(laser_04_wav, laser_04_wav_len);
        break;
    case SAMPLE_ALARM_REVERB:
        this->file[0] = new AudioFileSourcePROGMEM(alarm_reverb_wav, alarm_reverb_wav_len);
        break;
    case SAMPLE_DIRTY_SYREN_1:
        this->file[0] = new AudioFileSourcePROGMEM(dirty_syren_01_wav, dirty_syren_01_wav_len);
        break;
    case SAMPLE_DIRTY_SYREN_2:
        this->file[0] = new AudioFileSourcePROGMEM(dirty_syren_02_wav, dirty_syren_02_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
        this->file[0] = new AudioFileSourcePROGMEM(low_tone_01_wav, low_tone_01_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
        this->file[0] = new AudioFileSourcePROGMEM(low_tone_02_wav, low_tone_02_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
        this->file[0] = new AudioFileSourcePROGMEM(low_tone_03_wav, low_tone_03_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
        this->file[0] = new AudioFileSourcePROGMEM(low_tone_04_wav, low_tone_04_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5:
        this->file[0] = new AudioFileSourcePROGMEM(low_tone_05_wav, low_tone_05_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
        this->file[0] = new AudioFileSourcePROGMEM(high_tone_01_wav, high_tone_01_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
        this->file[0] = new AudioFileSourcePROGMEM(high_tone_02_wav, high_tone_02_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
        this->file[0] = new AudioFileSourcePROGMEM(high_tone_03_wav, high_tone_03_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
        this->file[0] = new AudioFileSourcePROGMEM(high_tone_04_wav, high_tone_04_wav_len);
        break;
    case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5:
        this->file[0] = new AudioFileSourcePROGMEM(high_tone_05_wav, high_tone_05_wav_len);
        break;
    case SAMPLE_ALIEN_VOICE_01:
        this->file[0] = new AudioFileSourcePROGMEM(alien_voice_01_wav, alien_voice_01_wav_len);
        break;
    case SAMPLE_ALIEN_VOICE_02:
        this->file[0] = new AudioFileSourcePROGMEM(alien_voice_02_wav, alien_voice_02_wav_len);
        break;
    case SAMPLE_ALIEN_VOICE_03:
        this->file[0] = new AudioFileSourcePROGMEM(alien_voice_03_wav, alien_voice_03_wav_len);
        break;
    case SAMPLE_ALIEN_VOICE_04:
        this->file[0] = new AudioFileSourcePROGMEM(alien_voice_04_wav, alien_voice_04_wav_len);
        break;
    }
    if (sample != SAMPLE_NONE)
    {
        this->wav[0] = new AudioGeneratorWAV();
        this->wav[0]->begin(this->file[0], this->stub[0]);
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

void Sampler::loop(void)
{
    if (this->wav[0]->isRunning())
    {
        if (!this->wav[0]->loop())
        {
            this->wav[0]->stop();
            this->stub[0]->stop();
            switch (this->currentSample)
            {
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
            }
        }
    }
}
