#include <cstring>
#include "MultiFrameIndividualSegmentEffect.hpp"

MultiFrameIndividualSegmentEffect::MultiFrameIndividualSegmentEffect(TM1638plus *module, uint8_t **frames, size_t frameCount, size_t frameAffectedSegmentCount, uint16_t msDelay, const uint8_t startIndex, const uint8_t endIndex) : SevenSegmentDisplayEffect(module, msDelay), frameCount(frameCount), frameAffectedSegmentCount(frameAffectedSegmentCount), startIndex(startIndex), endIndex(endIndex)
{
    if (frames != nullptr && frameCount > 0)
    {
        this->frames = new uint8_t *[frameCount];
        for (size_t i = 0; i < frameCount; i++)
        {
            this->frames[i] = new uint8_t[frameAffectedSegmentCount];
            std::memcpy(this->frames[i], frames[i], frameAffectedSegmentCount * sizeof(uint8_t));
        }
    }
}

MultiFrameIndividualSegmentEffect::~MultiFrameIndividualSegmentEffect()
{
    if (this->frames)
    {
        for (size_t i = 0; i < this->frameCount; i++)
        {
            delete[] this->frames[i];
        }
        delete[] this->frames;
        this->frames = nullptr;
    }
}

void MultiFrameIndividualSegmentEffect::loop(void)
{
    if (this->frames && this->frameCount > 0)
    {
        if (this->refresh())
        {
            for (uint8_t i = startIndex; i < frameAffectedSegmentCount; i++)
            {
                this->module->display7Seg(i, this->frames[this->currentFrameIndex][i]);
            }
            this->currentFrameIndex++;
            if (this->currentFrameIndex >= this->frameCount)
            {
                this->currentFrameIndex = 0;
            }
        }
    }
}