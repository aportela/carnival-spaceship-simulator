
#ifndef MODULE_SAMPLER
#define MODULE_SAMPLER

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"
#include "AudioOutputMixer.h"

#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16

enum SAMPLE
{
    SAMPLE_NONE = 0,
    SAMPLE_LASER1_SINGLE = 1,
    SAMPLE_LASER2_SINGLE = 2,
    SAMPLE_LASER3_SINGLE = 3,
    SAMPLE_LASER4_SINGLE = 4,
    SAMPLE_ALARM_REVERB = 5,
    SAMPLE_DIRTY_SYREN_1 = 6,
    SAMPLE_DIRTY_SYREN_2 = 7,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1 = 12,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2 = 13,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3 = 14,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4 = 15,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5 = 16,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1 = 17,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2 = 18,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3 = 19,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4 = 20,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5 = 21,
    SAMPLE_ALIEN_VOICE_01 = 30,
    SAMPLE_ALIEN_VOICE_02 = 31,
    SAMPLE_ALIEN_VOICE_03 = 32,
    SAMPLE_ALIEN_VOICE_04 = 33,

};

class Sampler
{
private:
    AudioGeneratorWAV *wav[2];
    AudioFileSourcePROGMEM *file[2];
    AudioOutputI2S *out;
    AudioOutputMixer *mixer;
    AudioOutputMixerStub *stub[2];
    SAMPLE currentSample = SAMPLE_NONE;

public:
    Sampler(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN);
    ~Sampler(void);
    void play(SAMPLE sample);
    SAMPLE getRandomSingleLaser(SAMPLE lastSample);
    void loop(void);
};

#endif // MODULE_SAMPLER
