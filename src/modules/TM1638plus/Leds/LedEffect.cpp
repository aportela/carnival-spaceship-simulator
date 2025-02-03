#include "LedEffect.hpp"
#include "Arduino.h"

LedEffect::LedEffect(TM1638plus *module, const uint16_t *maskedFrames, size_t frameCount) : module(module)
{
    this->totalFrames = frameCount;
    this->frames = new uint16_t[frameCount];
    for (size_t i = 0; i < frameCount; i++)
    {
        this->frames[i] = maskedFrames[i];
    }
}

LedEffect::~LedEffect()
{
    delete[] this->frames;
    this->frames = nullptr;
    this->module = nullptr;
}

bool LedEffect::refresh(void)
{
    uint64_t timestamp = millis();
    if (timestamp - this->lastRefresh > this->msDelay)
    {
        this->lastRefresh = timestamp;
        return (true);
    }
    else
    {
        return (false);
    }
}

bool LedEffect::toggleInverse(void)
{
    this->inverse = !this->inverse;
    return (this->inverse);
}

uint8_t LedEffect::toggleCurrentSpeed(void)
{
    if (this->currentSpeed <= MAX_SPEED)
    {
        this->currentSpeed *= 2;
        this->msDelay = this->currentSpeed * DEFAULT_MS_DELAY;
    }
    else
    {
        this->currentSpeed = 1;
    }
    this->msDelay = this->currentSpeed * DEFAULT_MS_DELAY;
    return (this->currentSpeed);
}

bool LedEffect::loop(void)
{
    if (this->refresh())
    {
        if (this->currentFrameIndex >= this->totalFrames)
        {
            this->currentFrameIndex = 0;
        }
        uint16_t mask = this->frames[this->currentFrameIndex];
        if (inverse)
        {
            mask = ~mask;
        }
        this->module->setLEDs(mask);
        this->module->displayIntNum(this->currentFrameIndex, false, TMAlignTextRight);
        this->currentFrameIndex++;
        return (true);
    }
    else
    {
        return (false);
    }
}
