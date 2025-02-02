#include "LedEffect.hpp"
#include "Arduino.h"

LedEffect::LedEffect(TM1638plus *module) : module(module)
{
}

LedEffect::~LedEffect()
{
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
    if (this->currentSpeed <= 16)
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
