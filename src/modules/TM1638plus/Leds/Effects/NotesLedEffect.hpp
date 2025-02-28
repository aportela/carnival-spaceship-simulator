#ifndef TM1638_PLUS_NOTES_LED_EFFECT_H
#define TM1638_PLUS_NOTES_LED_EFFECT_H

#include <stdint.h>
#include "../LedEffect.hpp"
#include <TM1638plus.h>

class NotesLedEffect : public LedEffect
{
private:
    static const uint16_t individualLedMasks[];

public:
    NotesLedEffect(TM1638plus *module, uint16_t msDelay = DEFAULT_LED_MS_DELAY);
    ~NotesLedEffect();
};

#endif // TM1638_PLUS_NOTES_LED_EFFECT_H
