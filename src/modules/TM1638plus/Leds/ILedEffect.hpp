#ifndef TM1638_PLUS_LED_EFFECT_INTERFACE_H
#define TM1638_PLUS_LED_EFFECT_INTERFACE_H

class ILedEffect
{
public:
    virtual ~ILedEffect() {}
    virtual bool loop(void) = 0;
};

#endif // TM1638_PLUS_LED_EFFECT_INTERFACE_H
