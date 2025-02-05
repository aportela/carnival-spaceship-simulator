#include "ExternalButtons.hpp"

ExternalButtons::ExternalButtons(const uint8_t BUTTON_PINS[TOTAL_BUTTONS])
{
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        this->buttons[i] = new Bounce();
        this->buttons[i]->attach(BUTTON_PINS[i]);
        this->buttons[i]->interval(DEBOUNCE_TIME);
    }
}

ExternalButtons::~ExternalButtons()
{
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        delete this->buttons[i];
        this->buttons[i] = nullptr;
    }
}

EXTERNAL_BUTTON ExternalButtons::loop(void)
{
    if (this->pressed)
    {
        for (int i = 0; i < TOTAL_BUTTONS; i++)
        {
            this->buttons[i]->update();
            if (this->buttons[i]->rose())
            {
                this->pressed = false;
                return (EXTERNAL_BUTTON_NONE);
            }
        }
        return (EXTERNAL_BUTTON_NONE);
    }
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        this->buttons[i]->update();
        if (this->buttons[i]->fell())
        {
            this->pressed = true;
            return static_cast<EXTERNAL_BUTTON>(1 << i);
        }
    }
    return (EXTERNAL_BUTTON_NONE);
}
