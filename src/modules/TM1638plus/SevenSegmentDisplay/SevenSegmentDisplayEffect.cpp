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
