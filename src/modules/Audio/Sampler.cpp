#include <Arduino.h>
#include "Sampler.hpp"
#include "Samples.hpp"

Sampler::Sampler(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN, sampleEventCallback onSampleStartPlaying, sampleEventCallback onSampleStopPlaying) : onSampleStartPlaying(onSampleStartPlaying), onSampleStopPlaying(onSampleStopPlaying)
{
    randomSeed(analogRead(0));
    this->sampleQueue = new std::queue<SAMPLE>();
    this->out = new AudioOutputI2S();
    this->mixer = new AudioOutputMixer(32, this->out);
    for (uint8_t i = 0; i < MAX_SIMULTANEOUS_VOICES; i++)
    {
        this->currentSample[i] = SAMPLE_NONE;
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
    delete this->sampleQueue;
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

void Sampler::queueSample(SAMPLE sample)
{
    if (!(sample == SAMPLE_SOS_01 && this->isPlayingSOSSample)) // only allow 1 SOS sample at time
    {
        // Serial.printf("Push sample %d into queue\n", sample);
        this->sampleQueue->push(sample);
        // Serial.printf("New queue size: %d\n", this->sampleQueue->size());
    }
    else
    {
        Serial.println("not queue");
    }
}

void Sampler::playQueue(void)
{
    if (!this->sampleQueue->empty())
    {
        SAMPLE sample = this->sampleQueue->front();
        if (this->play(sample))
        {
            this->sampleQueue->pop();
        }
    }
    else
    {
        // Serial.println("Queue is empty");
    }
}

bool Sampler::play(SAMPLE sample)
{
    int8_t firstFreeVoiceIndex = this->getFirstFreeVoiceIndex();
    if (firstFreeVoiceIndex != -1)
    {
        // Serial.printf("Playing sample %d on index %d\n", sample, firstFreeVoiceIndex);
        this->currentSample[firstFreeVoiceIndex] = sample;
        switch (sample)
        {
        case SAMPLE_LASER1_SINGLE:
        case SAMPLE_LASER1_DOUBLE:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(laser_01_wav, laser_01_wav_len);
            break;
        case SAMPLE_LASER2_SINGLE:
        case SAMPLE_LASER2_DOUBLE:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(laser_02_wav, laser_02_wav_len);
            break;
        case SAMPLE_LASER3_SINGLE:
        case SAMPLE_LASER3_DOUBLE:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(laser_03_wav, laser_03_wav_len);
            break;
        case SAMPLE_LASER4_SINGLE:
        case SAMPLE_LASER4_DOUBLE:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(laser_04_wav, laser_04_wav_len);
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
        case SAMPLE_SOS_01:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(morse_letter_s_wav, morse_letter_s_wav_len);
            this->isPlayingSOSSample = true;
            break;
        case SAMPLE_SOS_02:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(morse_letter_o_wav, morse_letter_o_wav_len);
            break;
        case SAMPLE_SOS_03:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(morse_letter_s_wav, morse_letter_s_wav_len);
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
            if (this->onSampleStartPlaying)
            {
                this->onSampleStartPlaying(sample);
            }
            return (true);
        }
        else
        {
            return (true);
        }
    }
    else
    {
        // Serial.println("All voices are in use");
        return (false);
    }
}

void Sampler::loop(void)
{
    this->playQueue();
    for (uint8_t i = 0; i < MAX_SIMULTANEOUS_VOICES; i++)
    {
        if (this->wav[i] != nullptr && this->wav[i]->isRunning())
        {
            if (!this->wav[i]->loop())
            {
                // Serial.printf("%d Sample ends (not looping), stopping sample\n", i);
                this->wav[i]->stop();
                delete this->wav[i];
                this->wav[i] = nullptr;
                delete this->file[i];
                this->file[i] = nullptr;
                this->stub[i]->stop();
                this->activeVoices[i] = false;
                if (this->onSampleStopPlaying)
                {
                    this->onSampleStopPlaying(this->currentSample[i]);
                }
                switch (this->currentSample[i])
                {
                case SAMPLE_LASER1_DOUBLE:
                    this->queueSample(SAMPLE_LASER1_SINGLE);
                    break;
                case SAMPLE_LASER2_DOUBLE:
                    this->queueSample(SAMPLE_LASER2_SINGLE);
                    break;
                case SAMPLE_LASER3_DOUBLE:
                    this->queueSample(SAMPLE_LASER3_SINGLE);
                    break;
                case SAMPLE_LASER4_DOUBLE:
                    this->queueSample(SAMPLE_LASER4_SINGLE);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1:
                    this->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2:
                    this->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3:
                    this->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4:
                    this->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1:
                    this->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2:
                    this->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3:
                    this->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4);
                    break;
                case SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4:
                    this->queueSample(SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5);
                    break;
                case SAMPLE_ALIEN_VOICE_01:
                    this->queueSample(SAMPLE_ALIEN_VOICE_02);
                    break;
                case SAMPLE_ALIEN_VOICE_02:
                    this->queueSample(SAMPLE_ALIEN_VOICE_03);
                    break;
                case SAMPLE_ALIEN_VOICE_03:
                    this->queueSample(SAMPLE_ALIEN_VOICE_04);
                    break;
                case SAMPLE_SOS_01:
                    this->queueSample(SAMPLE_SOS_02);
                    break;
                case SAMPLE_SOS_02:
                    this->queueSample(SAMPLE_SOS_03);
                    break;
                case SAMPLE_SOS_03:
                    this->isPlayingSOSSample = false;
                    break;
                default:
                    break;
                }
                this->currentSample[i] = SAMPLE_NONE;
            }
        }
    }
}
