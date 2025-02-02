#ifndef TM1638_PLUS_SCANNER_LED_EFFECT_H
#define TM1638_PLUS_SCANNER_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

#define DEFAULT_LED_ANIMATION_DELAY 64

class ScannerLedEffect : public LedEffect
{
private:
    uint8_t LEDposition = 0;
    bool inc = true;
    uint8_t delayMS = DEFAULT_LED_ANIMATION_DELAY;

public:
    ScannerLedEffect(TM1638plus *module);
    ~ScannerLedEffect();

    bool loop(void) override;
};

#endif // TM1638_PLUS_SCANNER_LED_EFFECT_H
