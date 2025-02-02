#ifndef TM1638_PLUS_LED_EFFECT_H
#define TM1638_PLUS_LED_EFFECT_H

#include <stdint.h>
#include "ILedEffect.hpp"
#include <TM1638plus.h>

class LedEffect : public ILedEffect
{
protected:
    TM1638plus *module = nullptr;
    uint64_t lastRefresh = 0;

public:
    LedEffect(TM1638plus *module);
    ~LedEffect();

    virtual bool loop(void) = 0;

    bool refresh(void);
};

#endif // TM1638_PLUS_LED_EFFECT_H
