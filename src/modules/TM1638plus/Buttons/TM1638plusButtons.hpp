#ifndef TM1638_PLUS_BUTTONS_H
#define TM1638_PLUS_BUTTONS_H

#include <stdint.h>

#include <TM1638plus.h>

#define BUTTON_DEBOUNCE_MS 200

enum TM1638plusBUTTON
{
    TM1638plusBUTTON_NONE = 0x00,
    TM1638plusBUTTON_S1 = 0x01,
    TM1638plusBUTTON_S2 = 0x02,
    TM1638plusBUTTON_S3 = 0x04,
    TM1638plusBUTTON_S4 = 0x08,
    TM1638plusBUTTON_S5 = 0x10,
    TM1638plusBUTTON_S6 = 0x20,
    TM1638plusBUTTON_S7 = 0x40,
    TM1638plusBUTTON_S8 = 0x80,
};

class TM1638plusButtons
{
protected:
    TM1638plus *module = nullptr;
    uint64_t lastTimestamp = 0;

public:
    TM1638plusButtons(TM1638plus *module);
    ~TM1638plusButtons();

    uint8_t getPressedButtonsMask(void);
};

#endif // TM1638_PLUS_BUTTONS_H
