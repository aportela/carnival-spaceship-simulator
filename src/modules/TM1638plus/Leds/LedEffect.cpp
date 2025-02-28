#include "LedEffect.hpp"
#include "Arduino.h"

LedEffect::LedEffect(TM1638plus *module, const uint16_t *maskedFrames, size_t frameCount, uint16_t msDelay) : module(module), msDelay(msDelay)
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
    if (this->useRandomDelay)
    {
        this->msDelay = random(this->minRandomMSDelay, this->maxRandomMSDelay) * this->randomMultiplier;
    }
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

void LedEffect::setDelay(uint16_t msDelay)
{
    this->msDelay = msDelay;
}

void LedEffect::setRandomDelay(uint16_t minRandomMSDelay, uint16_t maxRandomMSDelay, uint8_t randomMultiplier)
{
    if (minRandomMSDelay > 0 && maxRandomMSDelay > minRandomMSDelay && randomMultiplier > 0)
    {
        this->minRandomMSDelay = minRandomMSDelay;
        this->maxRandomMSDelay = maxRandomMSDelay;
        this->randomMultiplier = randomMultiplier;
        this->useRandomDelay = true;
    }
}

void LedEffect::disableAnimationLoopAtEnd(void)
{
    this->animationLoopAtEnd = false;
}

bool LedEffect::loop(void)
{
    if (this->refresh())
    {
        if (this->currentFrameIndex >= this->totalFrames)
        {
            if (this->animationLoopAtEnd)
            {
                this->currentFrameIndex = 0;
            }
        }
        uint16_t mask = this->frames[this->currentFrameIndex];
        if (inverse)
        {
            mask = ~mask;
        }
        this->module->setLEDs(mask);
        if (this->currentFrameIndex < this->totalFrames && this->animationLoopAtEnd)
        {
            this->currentFrameIndex++;
        }
        return (true);
    }
    else
    {
        return (false);
    }
}
