#include "SimpleTextEffect.hpp"
#include <string.h>

SimpleTextEffect::SimpleTextEffect(TM1638plus *module, const char *text, bool blink = false, unit16_t blinkTimeout = 0, const uint8_t startIndex = 0, const uint8_t endIndex = 0) : module(module), blink(blink), blinkTimeout(blinkTimeout), startIndex(startIndex), endIndex(endIndex)
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
    uint8_t currentIndex = this->startIndex;
    for (uint8_t i = 0; i < currentTextLength && currentIndex <= this->endIndex; i++)
    {
        char c = *text[i];
        this->module->displayASCII(currentIndex, c);
        this->currentIndex++;
    }
    while (currentIndex < this->endIndex)
    {
        this->module->displayASCII(currentIndex, ' ');
        currentIndex++;
    }
}

void SimpleTextEffect::hideText(void)
{
    uint8_t currentIndex = this->startIndex;
    for (uint8_t i = 0; i < currentTextLength; i++)
    {
        this->module->displayASCII(currentIndex, ' ');
        this->currentIndex++;
    }
}

SimpleTextEffect::loop(void)
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
                this->clearText();
            }
            this->visible = !this->visible;
        }
    }
}