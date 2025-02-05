#ifndef TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_H
#define TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_H

#define MAX_SPEED 16

#include <stdint.h>
#include <TM1638plus.h>

#define DEFAULT_MS_DELAY 32

/*

    Segments:

         AAAA
        F    B
        F    B
         GGGG
        E    C
        E    C
         DDDD
                DP

*/

#define SEGMENT_A 0x01
#define SEGMENT_B 0x02
#define SEGMENT_C 0x04
#define SEGMENT_D 0x08
#define SEGMENT_E 0x10
#define SEGMENT_F 0x20
#define SEGMENT_G 0x40
#define SEGMENT_DP 0x80

class SevenSegmentDisplayEffect
{
protected:
    TM1638plus *module = nullptr;
    size_t totalFrames = 0;
    size_t currentFrameIndex = 0;
    uint64_t lastRefresh = 0;
    uint8_t currentSpeed = 3;
    uint16_t msDelay = currentSpeed * DEFAULT_MS_DELAY;

public:
    SevenSegmentDisplayEffect(TM1638plus *module);
    ~SevenSegmentDisplayEffect();

    bool refresh(void);
    uint8_t toggleCurrentSpeed(void);
    bool loop(void);
};

#endif // TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_H
