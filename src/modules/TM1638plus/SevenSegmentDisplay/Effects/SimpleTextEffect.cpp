#include "SimpleTextEffect.hpp"
#include <string.h>

SimpleTextEffect::SimpleTextEffect(TM1638plus *module, const char *text, bool blink, uint16_t blinkTimeout, const uint8_t startIndex, const uint8_t endIndex) : module(module), blink(blink), blinkTimeout(blinkTimeout), startIndex(startIndex), endIndex(endIndex)
{
    this->lastTimestamp = millis();
    this->currentTextLength = strlen(text);
    this->showText(text);
    this->visible = true;
    if (this->blink)
    {
        this->currentText = new char[this->currentTextLength + 1];
        strcpy(this->currentText, text);
    }
}

SimpleTextEffect::~SimpleTextEffect()
{
    if (this->currentText != nullptr)
    {
        delete this->currentText;
        this->currentText = nullptr;
    }
}

void SimpleTextEffect::showText(const char *text)
{
    // copy from https://github.com/gavinlyonsrepo/TM1638plus/blob/master/src/TM1638plus.cpp to allow start text from custom index
    uint8_t currentIndex = this->startIndex;
    char c, pos;
    pos = 0;
    while ((c = (*text++)) && currentIndex < TM_DISPLAY_SIZE && currentIndex <= this->endIndex)
    {
        if (*text == '.' && c != '.')
        {
            this->module->displayASCIIwDot(currentIndex++, c);
            text++;
        }
        else
        {
            this->module->displayASCII(currentIndex++, c);
        }
    }
}

void SimpleTextEffect::hideText(void)
{
    for (uint8_t i = 0; i <= this->endIndex; i++)
    {
        this->module->displayASCII(i, ' ');
    }
}

void SimpleTextEffect::loop(void)
{
    if (this->blink)
    {
        uint64_t currentMillis = millis();
        if (currentMillis - this->lastTimestamp > this->blinkTimeout)
        {
            this->lastTimestamp = currentMillis;
            if (!this->visible)
            {
                this->showText(this->currentText);
            }
            else
            {
                this->hideText();
            }
            this->visible = !this->visible;
        }
    }
}