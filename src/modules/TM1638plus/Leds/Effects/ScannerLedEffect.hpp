#ifndef TM1638_PLUS_SCANNER_LED_EFFECT_H
#define TM1638_PLUS_SCANNER_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class ScannerLedEffect : public LedEffect
{
private:
    uint8_t LEDposition = 0;
    bool inc = true;

public:
    ScannerLedEffect(TM1638plus *module);
    ~ScannerLedEffect();

    bool loop(void) override;
};

#endif // TM1638_PLUS_SCANNER_LED_EFFECT_H
