#ifndef TM1638_PLUS_BUTTONS_H
#define TM1638_PLUS_BUTTONS_H

#include <stdint.h>

#include <TM1638plus.h>

#define BUTTON_DEBOUNCE_MS 200

enum BUTTON_VALUE
{
    BUTTON_S1 = 0x01,
    BUTTON_S2 = 0x02,
    BUTTON_S3 = 0x04,
    BUTTON_S4 = 0x08,
    BUTTON_S5 = 0x10,
    BUTTON_S6 = 0x20,
    BUTTON_S7 = 0x40,
    BUTTON_S8 = 0x80,
};

class Buttons
{
protected:
    TM1638plus *module = nullptr;
    uint64_t lastTimestamp = 0;

public:
    Buttons(TM1638plus *module);
    ~Buttons();

    uint8_t loop(void);
};

#endif // TM1638_PLUS_BUTTONS_H
