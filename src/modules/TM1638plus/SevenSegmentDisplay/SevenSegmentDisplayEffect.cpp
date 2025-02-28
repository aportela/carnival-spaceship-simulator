#include "SevenSegmentDisplayEffect.hpp"
#include "Arduino.h"

SevenSegmentDisplayEffect::SevenSegmentDisplayEffect(TM1638plus *module, uint16_t msDelay) : module(module), msDelay(msDelay)
{
    this->lastTimestamp = millis();
}

SevenSegmentDisplayEffect::~SevenSegmentDisplayEffect()
{
    this->module = nullptr;
}

bool SevenSegmentDisplayEffect::refresh(void)
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

void SevenSegmentDisplayEffect::setDelay(uint16_t msDelay)
{
    this->msDelay = msDelay;
}

void SevenSegmentDisplayEffect::setRandomDelay(uint16_t minRandomMSDelay, uint16_t maxRandomMSDelay, uint8_t randomMultiplier)
{
    if (minRandomMSDelay > 0 && maxRandomMSDelay > minRandomMSDelay && randomMultiplier > 0)
    {
        this->minRandomMSDelay = minRandomMSDelay;
        this->maxRandomMSDelay = maxRandomMSDelay;
        this->randomMultiplier = randomMultiplier;
        this->useRandomDelay = true;
    }
}
