#ifndef TM1638_PLUS_MORSE_LED_EFFECT_H
#define TM1638_PLUS_MORSE_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class MorseLedEffect : public LedEffect
{
private:
    static const uint16_t letterSLedMasks[];
    static const uint16_t letterOLedMasks[];
    static const uint16_t emptyLetterLedMasks[];

public:
    MorseLedEffect(TM1638plus *module, uint16_t msDelay = DEFAULT_LED_MS_DELAY, const char letter = '\0');
    ~MorseLedEffect();
};

#endif // TM1638_PLUS_SOS_LED_EFFECT_H
