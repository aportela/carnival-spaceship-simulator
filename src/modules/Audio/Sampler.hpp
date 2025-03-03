
#ifndef MODULE_SAMPLER
#define MODULE_SAMPLER

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"
#include "AudioOutputMixer.h"

#include <queue>

#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16

#define MAX_SIMULTANEOUS_VOICES 4

enum SAMPLE
{
    SAMPLE_NONE = 0,
    SAMPLE_LASER1_SINGLE = 1,
    SAMPLE_LASER2_SINGLE = 2,
    SAMPLE_LASER3_SINGLE = 3,
    SAMPLE_LASER4_SINGLE = 4,
    SAMPLE_LASER1_DOUBLE = 5,
    SAMPLE_LASER2_DOUBLE = 6,
    SAMPLE_LASER3_DOUBLE = 7,
    SAMPLE_LASER4_DOUBLE = 8,
    SAMPLE_ALARM_REVERB = 9,
    SAMPLE_DIRTY_SYREN_1 = 10,
    SAMPLE_DIRTY_SYREN_2 = 11,
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
    SAMPLE_ALIEN_VOICE_01 = 22,
    SAMPLE_ALIEN_VOICE_02 = 23,
    SAMPLE_ALIEN_VOICE_03 = 24,
    SAMPLE_ALIEN_VOICE_04 = 25,
    SAMPLE_ALIEN_VOICE_05 = 26,
    SAMPLE_ALIEN_VOICE_06 = 27,
    SAMPLE_ALIEN_VOICE_07 = 28,
    SAMPLE_ALIEN_VOICE_08 = 29,
    SAMPLE_ALIEN_VOICE_09 = 30,
    SAMPLE_SOS_01 = 31,
    SAMPLE_SOS_02 = 32,
    SAMPLE_SOS_03 = 33,
    SAMPLE_ALARM_REVERB_SEQ_1 = 34,
    SAMPLE_ALARM_REVERB_SEQ_2 = 35,
    SAMPLE_ALARM_REVERB_SEQ_3 = 36,
};

typedef void (*sampleEventCallback)(SAMPLE);

// available laser samples (for "shuffle" play)

class Sampler
{
private:
    std::queue<SAMPLE> *sampleQueue;

    AudioGeneratorWAV *wav[MAX_SIMULTANEOUS_VOICES];
    AudioFileSourcePROGMEM *file[MAX_SIMULTANEOUS_VOICES];
    AudioOutputI2S *out;
    AudioOutputMixer *mixer;
    AudioOutputMixerStub *stub[MAX_SIMULTANEOUS_VOICES];
    bool activeVoices[MAX_SIMULTANEOUS_VOICES];
    SAMPLE currentSample[MAX_SIMULTANEOUS_VOICES];
    bool isPlayingSOSSample = false;

    sampleEventCallback onSampleStartPlaying;
    sampleEventCallback onSampleStopPlaying;

    int8_t getFirstFreeVoiceIndex(void);

public:
    static constexpr SAMPLE laserSamples[] = {SAMPLE_LASER1_SINGLE, SAMPLE_LASER2_SINGLE, SAMPLE_LASER3_SINGLE, SAMPLE_LASER4_SINGLE, SAMPLE_LASER1_DOUBLE, SAMPLE_LASER2_DOUBLE, SAMPLE_LASER3_DOUBLE, SAMPLE_LASER4_DOUBLE};
    static constexpr uint8_t laserSamplesSize = sizeof(Sampler::laserSamples) / sizeof(Sampler::laserSamples[0]);

    Sampler(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN, sampleEventCallback onSampleStartPlaying, sampleEventCallback onSampleStopPlaying);
    ~Sampler(void);
    void queueSample(SAMPLE sample);
    void playQueue(void);
    bool play(SAMPLE sample);
    void loop(void);
};

#endif // MODULE_SAMPLER
