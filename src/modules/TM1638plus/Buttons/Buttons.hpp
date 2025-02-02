#ifndef TM1638_PLUS_BUTTONS_H
#define TM1638_PLUS_BUTTONS_H

#include <stdint.h>

#include <TM1638plus.h>

class Buttons
{
protected:
    TM1638plus *module = nullptr;

public:
    Buttons(TM1638plus *module);
    ~Buttons();

    bool loop(void);
};

#endif // TM1638_PLUS_BUTTONS_H
