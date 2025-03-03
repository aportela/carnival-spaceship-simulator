#include <Arduino.h>
#include "Sampler.hpp"
#include "Samples.hpp"
#include "../../CommonDefines.hpp"

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
#ifdef DEBUG_SERIAL_MORE_DATA
        Serial.printf("SAMPLER:: adding sample %d into queue\n", sample);
#endif
        this->sampleQueue->push(sample);
#ifdef DEBUG_SERIAL_MORE_DATA
        Serial.printf("SAMPLER:: new queue size: %d\n", this->sampleQueue->size());
#endif
    }
    else
    {
#ifdef DEBUG_SERIAL_MORE_DATA
        Serial.println("SAMPLER:: SOS Sample not queued");
#endif
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
}

bool Sampler::play(SAMPLE sample)
{
    int8_t firstFreeVoiceIndex = this->getFirstFreeVoiceIndex();
    if (firstFreeVoiceIndex != -1)
    {
#ifdef DEBUG_SERIAL_MORE_DATA
        Serial.printf("SAMPLER:: playing sample %d on voice index %d\n", sample, firstFreeVoiceIndex);
#endif
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
        case SAMPLE_ALARM_REVERB_SEQ_1:
        case SAMPLE_ALARM_REVERB_SEQ_2:
        case SAMPLE_ALARM_REVERB_SEQ_3:
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
        case SAMPLE_ALIEN_VOICE_05:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_05_wav, alien_voice_05_wav_len);
            break;
        case SAMPLE_ALIEN_VOICE_06:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_06_wav, alien_voice_06_wav_len);
            break;
        case SAMPLE_ALIEN_VOICE_07:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_07_wav, alien_voice_07_wav_len);
            break;
        case SAMPLE_ALIEN_VOICE_08:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_08_wav, alien_voice_08_wav_len);
            break;
        case SAMPLE_ALIEN_VOICE_09:
            this->file[firstFreeVoiceIndex] = new AudioFileSourcePROGMEM(alien_voice_09_wav, alien_voice_09_wav_len);
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
#ifdef DEBUG_SERIAL_MORE_DATA
            Serial.printf("SAMPLER:: sample NONE not played\n", sample);
#endif
            return (true);
        }
    }
    else
    {
#ifdef DEBUG_SERIAL_MORE_DATA
        Serial.printf("SAMPLER:: can not play sample %d, all voices are in use\n", sample);
#endif
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
#ifdef DEBUG_SERIAL_MORE_DATA
                Serial.printf("SAMPLER:: sample %d playback ended\n", this->currentSample[i]);
#endif
                this->wav[i]->stop();
                delete this->wav[i];
                this->wav[i] = nullptr;
                delete this->file[i];
                this->file[i] = nullptr;
                this->stub[i]->stop();
                this->activeVoices[i] = false;
                if (this->currentSample[i] == SAMPLE_SOS_03)
                {
                    this->isPlayingSOSSample = false;
                }
                if (this->onSampleStopPlaying)
                {
                    this->onSampleStopPlaying(this->currentSample[i]);
                }
                this->currentSample[i] = SAMPLE_NONE;
            }
        }
    }
}
