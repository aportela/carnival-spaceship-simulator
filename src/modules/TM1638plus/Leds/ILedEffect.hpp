#ifndef TM1638_PLUS_LED_EFFECT_INTERFACE_H
#define TM1638_PLUS_LED_EFFECT_INTERFACE_H

#define LED_NONE 0x0000
#define LED_1 0x0100
#define LED_2 0x0200
#define LED_3 0x0400
#define LED_4 0x0800
#define LED_5 0x1000
#define LED_6 0x2000
#define LED_7 0x4000
#define LED_8 0x8000

class ILedEffect
{
public:
    virtual ~ILedEffect() {}
    virtual bool loop(void) = 0;

    virtual bool toggleInverse(void) = 0;
    virtual uint8_t toggleCurrentSpeed(void) = 0;
};

#endif // TM1638_PLUS_LED_EFFECT_INTERFACE_H
