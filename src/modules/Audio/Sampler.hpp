
#ifndef MODULE_SAMPLER
#define MODULE_SAMPLER

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"
#include "AudioOutputMixer.h"

#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16

#define MAX_SIMULTANEOUS_VOICES 3

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
    SAMPLE_ALIEN_VOICE_01 = 30,
    SAMPLE_ALIEN_VOICE_02 = 31,
    SAMPLE_ALIEN_VOICE_03 = 32,
    SAMPLE_ALIEN_VOICE_04 = 33,

};

class Sampler
{
private:
    AudioGeneratorWAV *wav[MAX_SIMULTANEOUS_VOICES];
    AudioFileSourcePROGMEM *file[MAX_SIMULTANEOUS_VOICES];
    AudioOutputI2S *out;
    AudioOutputMixer *mixer;
    AudioOutputMixerStub *stub[MAX_SIMULTANEOUS_VOICES];
    SAMPLE currentSample = SAMPLE_NONE;
    bool doubleLaser = true;

public:
    Sampler(uint8_t I2S_BCK_PIN, uint8_t I2S_LRCK_PIN, uint8_t I2S_DATA_PIN);
    ~Sampler(void);
    void play(SAMPLE sample);
    SAMPLE getRandomSingleLaser(SAMPLE lastSample);
    SAMPLE getRandomDoubleLaser(SAMPLE lastSample);
    void loop(void);
    /*

    #include <stdio.h>

void reverseArray(int* arr, size_t size) {
    size_t start = 0;
    size_t end = size - 1;

    while (start < end) {
        // Intercambiar los elementos
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        ++start;
        --end;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    reverseArray(arr, size);

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", arr[i]);  // Salida: 5 4 3 2 1
    }

    return 0;
}
    */
};

#endif // MODULE_SAMPLER
