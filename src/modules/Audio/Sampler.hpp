
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
};

class Sampler
{
private:
    AudioGeneratorWAV *wav[2];
    AudioFileSourcePROGMEM *file[2];
    AudioOutputI2S *out;
    AudioOutputMixer *mixer;
    AudioOutputMixerStub *stub[2];

public:
    Sampler(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN);
    ~Sampler(void);
    void play(SAMPLE sample);
    void loop(void);
};

#endif // MODULE_SAMPLER
