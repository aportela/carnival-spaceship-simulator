
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
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_1 = 2,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_2 = 3,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_3 = 4,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_4 = 5,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_LOW_TONE_5 = 6,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_1 = 7,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_2 = 8,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_3 = 9,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_4 = 10,
    SAMPLE_CLOSE_ENCOUNTERS_OF_THE_THIRD_KIND_HIGH_TONE_5 = 11,
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
    void loop(void);
};

#endif // MODULE_SAMPLER
