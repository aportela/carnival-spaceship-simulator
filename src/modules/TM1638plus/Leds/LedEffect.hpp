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

#define MAX_SPEED 16

#include <stdint.h>
#include "ILedEffect.hpp"
#include <TM1638plus.h>

#define DEFAULT_LED_MS_DELAY 100

class LedEffect : public ILedEffect
{
protected:
    TM1638plus *module = nullptr;
    uint64_t lastRefresh = 0;
    bool inverse = false;
    uint16_t *frames = nullptr;
    size_t totalFrames = 0;
    size_t currentFrameIndex = 0;
    uint16_t msDelay = 0;

public:
    LedEffect(TM1638plus *module, const uint16_t *maskedFrames, size_t frameCount, uint16_t msDelay = DEFAULT_LED_MS_DELAY);
    ~LedEffect();

    bool refresh(void);
    bool toggleInverse(void) override;
    bool loop(void);
};

#endif // TM1638_PLUS_LED_EFFECT_H
