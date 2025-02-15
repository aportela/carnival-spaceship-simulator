#include "ExternalButtons.hpp"

ExternalButtons::ExternalButtons(const uint8_t BUTTON_PINS[TOTAL_EXTERNAL_BUTTONS])
{
    for (int i = 0; i < TOTAL_EXTERNAL_BUTTONS; i++)
    {
        this->buttons[i] = new Bounce();
        this->buttons[i]->attach(BUTTON_PINS[i], INPUT_PULLUP);
        this->buttons[i]->interval(DEBOUNCE_TIME);
    }
}

ExternalButtons::~ExternalButtons()
{
    for (int i = 0; i < TOTAL_EXTERNAL_BUTTONS; i++)
    {
        delete this->buttons[i];
        this->buttons[i] = nullptr;
    }
}

EXTERNAL_BUTTON ExternalButtons::getPressedButton(void)
{
    if (this->pressed)
    {
        for (int i = 0; i < TOTAL_EXTERNAL_BUTTONS; i++)
        {
            this->buttons[i]->update();
#ifndef BUTTON_MODE_INVERSE
            if (this->buttons[i]->rose())
#else
            if (this->buttons[i]->fell())
#endif
            {
                this->pressed = false;
                return (EXTERNAL_BUTTON_NONE);
            }
        }
        return (EXTERNAL_BUTTON_NONE);
    }
    for (int i = 0; i < TOTAL_EXTERNAL_BUTTONS; i++)
    {
        this->buttons[i]->update();
#ifndef BUTTON_MODE_INVERSE
        if (this->buttons[i]->fell())
#else
        if (this->buttons[i]->rose())
#endif
        {
            this->pressed = true;
            // return static_cast<EXTERNAL_BUTTON>(1 << i);
            return static_cast<EXTERNAL_BUTTON>(i + 1);
        }
    }
    return (EXTERNAL_BUTTON_NONE);
}
