#ifndef EXTERNAL_BUTTONS_H
#define EXTERNAL_BUTTONS_H

#include <Bounce2.h>
#include "../../CommonDefines.hpp"

enum EXTERNAL_BUTTON
{
    EXTERNAL_BUTTON_NONE = 0,
    EXTERNAL_BUTTON_1 = 1,
    EXTERNAL_BUTTON_2 = 2,
    EXTERNAL_BUTTON_3 = 3,
    EXTERNAL_BUTTON_4 = 4,
    EXTERNAL_BUTTON_5 = 5,
};

#define TOTAL_EXTERNAL_BUTTONS 5
#define DEBOUNCE_TIME 25

class ExternalButtons
{
private:
    Bounce *buttons[TOTAL_EXTERNAL_BUTTONS] = {nullptr, nullptr, nullptr, nullptr, nullptr};
#ifndef BUTTON_MODE_INVERSE
    bool pressed = false;
#else
    bool pressed = true;
#endif

public:
    ExternalButtons(const uint8_t BUTTON_PINS[TOTAL_EXTERNAL_BUTTONS]);
    ~ExternalButtons();

    EXTERNAL_BUTTON getPressedButton(void);
};

#endif // EXTERNAL_BUTTONS_H
