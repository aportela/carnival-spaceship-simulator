#ifndef TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_SIMPLE_TEXT_H
#define TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_SIMPLE_TEXT_H

#include <stdint.h>
#include "../SevenSegmentDisplayEffect.hpp"

class SimpleTextEffect : public SevenSegmentDisplayEffect
{
private:
    char *currentText = nullptr;
    uint8_t currentTextLength = 0;
    bool blink = false;
    bool visible = false;
    uint8_t startIndex = 0;
    uint8_t endIndex = 0;

    void showText(const char *text);
    void hideText(void);

public:
    SimpleTextEffect(TM1638plus *module, const char *text, bool blink = false, uint16_t blinkTimeout = 0, const uint8_t startIndex = 0, const uint8_t endIndex = TM_DISPLAY_SIZE);
    ~SimpleTextEffect();

    void setText(const char *text, bool blink = false, uint16_t blinkTimeout = 0);
    void loop(void) override;

    bool isSimpleTextEffect() override { return true; }
};

#endif // TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_SIMPLE_TEXT_H
