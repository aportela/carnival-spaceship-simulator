#include "MultiFrameSegmentEffect.hpp"

MultiFrameSegmentEffect::MultiFrameSegmentEffect(TM1638plus *module, const uint8_t frames[], size_t frameCount, uint16_t msDelay, const uint8_t startIndex, const uint8_t endIndex) : SevenSegmentDisplayEffect(module, msDelay), frameCount(frameCount), startIndex(startIndex), endIndex(endIndex)
{
    if (frames != nullptr && frameCount > 0)
    {
        this->frames = new uint8_t[frameCount];
        for (size_t i = 0; i < frameCount; ++i)
        {
            memcpy(this->frames, frames, frameCount * sizeof(uint8_t));
        }
    }
}

MultiFrameSegmentEffect::~MultiFrameSegmentEffect()
{
    if (this->frames)
    {
        delete[] this->frames;
        this->frames = nullptr;
    }
}

void MultiFrameSegmentEffect::loop(void)
{
    if (this->frames && this->frameCount > 0)
    {
        if (this->refresh())
        {
            for (uint8_t i = this->startIndex; i <= this->endIndex; i++)
            {
                this->module->display7Seg(i, this->frames[this->currentFrameIndex]);
            }
            this->currentFrameIndex++;
            if (this->currentFrameIndex >= this->frameCount)
            {
                this->currentFrameIndex = 0;
            }
        }
    }
}