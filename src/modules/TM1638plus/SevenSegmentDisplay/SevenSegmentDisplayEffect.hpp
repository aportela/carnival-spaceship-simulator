#ifndef TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_H
#define TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_H

#define MAX_SPEED 16

#include <stdint.h>
#include <TM1638plus.h>

#define DEFAULT_MS_DELAY 32

class SevenSegmentDisplayEffect
{
protected:
    TM1638plus *module = nullptr;
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
