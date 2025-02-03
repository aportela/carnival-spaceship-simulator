#ifndef TM1638_PLUS_SCANNER_LED_EFFECT_H
#define TM1638_PLUS_SCANNER_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class ScannerLedEffect : public LedEffect
{
private:
    static const uint16_t individualLedMasks[14];

public:
    ScannerLedEffect(TM1638plus *module);
    ~ScannerLedEffect();
};

#endif // TM1638_PLUS_SCANNER_LED_EFFECT_H
