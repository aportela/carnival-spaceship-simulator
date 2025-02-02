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
    if (timestamp - this->lastRefresh > 64)
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