#include "TM1638plusButtons.hpp"
#include "Arduino.h"

TM1638plusButtons::TM1638plusButtons(TM1638plus *module) : module(module)
{
}

TM1638plusButtons::~TM1638plusButtons()
{
    this->module = nullptr;
}

uint8_t TM1638plusButtons::getPressedButtonsMask(void)
{
    uint64_t timestamp = millis();
    if (timestamp - this->lastTimestamp >= BUTTON_DEBOUNCE_MS)
    {
        this->lastTimestamp = timestamp;
        /* buttons contains a byte with values of button s8s7s6s5s4s3s2s1
        HEX  :  Switch no : Binary
        0x01 : S1 Pressed  0000 0001
        0x02 : S2 Pressed  0000 0010
        0x04 : S3 Pressed  0000 0100
        0x08 : S4 Pressed  0000 1000
        0x10 : S5 Pressed  0001 0000
        0x20 : S6 Pressed  0010 0000
        0x40 : S7 Pressed  0100 0000
        0x80 : S8 Pressed  1000 0000
        */
        return (this->module->readButtons());
    }
    else
    {
        return (TM1638plusBUTTON_NONE);
    }
}