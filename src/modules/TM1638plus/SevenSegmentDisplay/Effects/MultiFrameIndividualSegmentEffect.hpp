#include <stdint.h>
#include <stdlib.h>
#include "../SevenSegmentDisplayEffect.hpp"

class MultiFrameIndividualSegmentEffect : public SevenSegmentDisplayEffect
{
private:
    uint8_t **frames = nullptr;
    size_t frameCount = 0;
    size_t frameAffectedSegmentCount = 0;
    uint8_t startIndex = 0;
    uint8_t endIndex = 0;
    uint8_t currentFrameIndex = 0;

public:
    MultiFrameIndividualSegmentEffect(TM1638plus *module, uint8_t **frames, size_t frameCount, size_t frameAffectedSegmentCount, uint16_t msDelay = 0, const uint8_t startIndex = 0, const uint8_t endIndex = 7);
    ~MultiFrameIndividualSegmentEffect();

    void loop(void);

    bool isMultiFrameIndividualSegmentEffect() override { return true; }
};
