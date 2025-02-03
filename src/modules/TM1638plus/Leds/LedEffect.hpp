#ifndef TM1638_PLUS_LED_EFFECT_H
#define TM1638_PLUS_LED_EFFECT_H

#define LED_NONE 0x0000
#define LED_1 0x0100
#define LED_2 0x0200
#define LED_3 0x0400
#define LED_4 0x0800
#define LED_5 0x1000
#define LED_6 0x2000
#define LED_7 0x4000
#define LED_8 0x8000

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
