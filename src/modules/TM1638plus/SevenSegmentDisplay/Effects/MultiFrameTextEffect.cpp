#include "MultiFrameTextEffect.hpp"

MultiFrameTextEffect::MultiFrameTextEffect(TM1638plus *module, const char *frames[], size_t frameCount, uint16_t frameTimeout, const uint8_t startIndex) : module(module), frameCount(frameCount), frameTimeout(frameTimeout), startIndex(startIndex)
{
    this->lastTimestamp = millis();
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
        uint64_t currentMillis = millis();
        if (currentMillis - this->lastTimestamp > this->frameTimeout)
        {
            this->lastTimestamp = currentMillis;
            this->module->displayText(this->frames[this->currentFrameIndex]);
            this->currentFrameIndex++;
            if (this->currentFrameIndex >= this->frameCount)
            {
                this->currentFrameIndex = 0;
            }
        }
    }
}