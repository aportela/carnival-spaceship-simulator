#include "SevenSegmentDisplayEffect.hpp"
#include "Arduino.h"

SevenSegmentDisplayEffect::SevenSegmentDisplayEffect(TM1638plus *module) : module(module)
{
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

uint8_t SevenSegmentDisplayEffect::toggleCurrentSpeed(void)
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

bool SevenSegmentDisplayEffect::loop(void)
{
    if (this->refresh())
    {
        const char *words[] = {
            "[------]",
            "[--||--]",
            "[-|--|-]",
            "[|----|]",
            "[|    |]",
            "[ |  | ]",
            "[  ||  ]",
            "[      ]",
        };
        this->module->displayText(words[random(0, sizeof(words) / sizeof(words[0]))]);
        return (true);
    }
    else
    {
        return (false);
    }
}
