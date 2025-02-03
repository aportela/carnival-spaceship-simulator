#ifndef TM1638_PLUS_LED_EFFECT_H
#define TM1638_PLUS_LED_EFFECT_H

#include <stdint.h>
#include "ILedEffect.hpp"
#include <TM1638plus.h>

#define DEFAULT_MS_DELAY 32

class LedEffect : public ILedEffect
{
protected:
    TM1638plus *module = nullptr;
    uint64_t lastRefresh = 0;
    bool inverse = false;
    uint8_t currentSpeed = 8;
    uint16_t msDelay = currentSpeed * DEFAULT_MS_DELAY;

public:
    LedEffect(TM1638plus *module);
    ~LedEffect();

    virtual bool loop(void) = 0;

    bool refresh(void);
    bool toggleInverse(void) override;
    uint8_t toggleCurrentSpeed(void) override;
};

#endif // TM1638_PLUS_LED_EFFECT_H
