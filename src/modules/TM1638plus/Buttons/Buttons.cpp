#include "Buttons.hpp"

Buttons::Buttons(TM1638plus *module) : module(module)
{
}

Buttons::~Buttons()
{
    this->module = nullptr;
}

bool Buttons::loop(void)
{
    uint8_t buttons = this->module->readButtons();
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
    // Serial.println(buttons, HEX);
    this->module->displayIntNum(buttons, true, TMAlignTextLeft);
}