#ifndef TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_MULTIFRAME_TEXT_EFFECT_H
#define TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_MULTIFRAME_TEXT_EFFECT_H

#include <stdint.h>
#include <stdlib.h>
#include "../SevenSegmentDisplayEffect.hpp"

class MultiFrameTextEffect : public SevenSegmentDisplayEffect
{
private:
    const char **frames = nullptr;
    size_t frameCount = 0;
    uint8_t startIndex = 0;
    uint8_t currentFrameIndex = 0;

public:
    MultiFrameTextEffect(TM1638plus *module, const char *frames[], size_t frameCount, uint16_t msDelay = 0, const uint8_t startIndex = 0, const uint8_t startFrameIndex = 0);
    ~MultiFrameTextEffect();

    void loop(void);

    bool isMultiFrameTextEffect() override { return true; }
};

#endif // TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_MULTIFRAME_TEXT_EFFECT_H
