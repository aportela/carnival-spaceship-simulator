#ifndef TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_MULTIFRAME_SEGMENT_EFFECT_H
#define TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_MULTIFRAME_SEGMENT_EFFECT_H

#include <stdint.h>
#include <stdlib.h>
#include "../SevenSegmentDisplayEffect.hpp"

class MultiFrameSegmentEffect : public SevenSegmentDisplayEffect
{
private:
    uint8_t *frames = nullptr;
    size_t frameCount = 0;
    uint8_t startIndex = 0;
    uint8_t endIndex = 0;
    uint8_t currentFrameIndex = 0;

public:
    MultiFrameSegmentEffect(TM1638plus *module, const uint8_t frames[], size_t frameCount, uint16_t msDelay = 0, const uint8_t startIndex = 0, const uint8_t endIndex = 7);
    ~MultiFrameSegmentEffect();

    void loop(void);

    bool isMultiFrameSegmentEffect() override { return true; }
};

#endif // TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_MULTIFRAME_SEGMENT_EFFECT_H
