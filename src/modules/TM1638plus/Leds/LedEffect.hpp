#ifndef TM1638_PLUS_LED_EFFECT_H
#define TM1638_PLUS_LED_EFFECT_H

#include <stdint.h>
#include "ILedEffect.hpp"
#include <TM1638plus.h>

class LedEffect : public ILedEffect
{
protected:
    TM1638plus *module = nullptr;

public:
    LedEffect(TM1638plus *module);
    ~LedEffect();

    virtual bool loop(void) = 0;
};

#endif // TM1638_PLUS_LED_EFFECT_H
