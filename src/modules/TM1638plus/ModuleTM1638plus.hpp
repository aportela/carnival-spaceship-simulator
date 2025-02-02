
#ifndef MODULE_TM1638_PLUS
#define MODULE_TM1638_PLUS

#include <stdint.h>
#include <TM1638plus.h>

#include "Buttons/Buttons.hpp"
#include "Leds/ILedEffect.hpp"
#include "Leds/Effects/ScannerLedEffect.hpp"
#include "Leds/Effects/ChaseLedEffect.hpp"

#define MAX_BRIGHTNESS 8

enum LED_EFFECT_TYPE
{
    LED_EFFECT_TYPE_NONE = 0,
    LED_EFFECT_TYPE_SCANNER = 1,
    LED_EFFECT_TYPE_CHASE = 2,
};

class ModuleTM1638plus
{
private:
    TM1638plus *module = nullptr;

    Buttons *buttons = nullptr;
    ILedEffect *ledEffect = nullptr;
    LED_EFFECT_TYPE currentLedEffectType = LED_EFFECT_TYPE_CHASE;

public:
    ModuleTM1638plus(uint8_t strobePIN, uint8_t clockPIN, uint8_t dioPIN, bool highFreq);
    ~ModuleTM1638plus();

    bool loop(void);
};

#endif // MODULE_TM1638_PLUS
