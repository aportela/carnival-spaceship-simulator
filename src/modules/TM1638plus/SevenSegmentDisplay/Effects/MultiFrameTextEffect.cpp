#include "MultiFrameTextEffect.hpp"

MultiFrameTextEffect::MultiFrameTextEffect(TM1638plus *module, const char *frames[], size_t frameCount, uint16_t msDelay, const uint8_t startIndex, const uint8_t startFrameIndex) : SevenSegmentDisplayEffect(module, msDelay), frameCount(frameCount), startIndex(startIndex)
{
    if (frames != nullptr && frameCount > 0)
    {
        this->frames = new const char *[frameCount];
        for (size_t i = 0; i < frameCount; ++i)
        {
            size_t length = strlen(frames[i]) + 1;
            this->frames[i] = new char[length];
            strcpy(const_cast<char *>(this->frames[i]), frames[i]);
        }
    }
}

MultiFrameTextEffect::~MultiFrameTextEffect()
{
    if (this->frames)
    {
        for (size_t i = 0; i < frameCount; ++i)
        {
            delete[] this->frames[i];
        }
        delete[] this->frames;
    }
    this->frames = nullptr;
}

void MultiFrameTextEffect::loop(void)
{
    if (this->frames && this->frameCount > 0)
    {
        if (this->refresh())
        {
            this->module->displayText(this->frames[this->currentFrameIndex]);
            this->currentFrameIndex++;
            if (this->currentFrameIndex >= this->frameCount)
            {
                this->currentFrameIndex = 0;
            }
        }
    }
}