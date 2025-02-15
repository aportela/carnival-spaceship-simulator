#include <stdint.h>
#include <TM1638plus.h>

class SimpleTextEffect
{
private:
    TM1638plus *module = nullptr;
    char *currentText = nullptr;
    uint8_t currentTextLength = 0;
    bool blink = false;
    bool visible = false;
    uint16_t blinkTimeout = 0;
    uint64_t lastTimestamp = 0;
    uint8_t startIndex = 0;
    uint8_t endIndex = 0;

    void showText(const char *text);
    void hideText(void);

public:
    SimpleTextEffect(TM1638plus *module, const char *text, bool blink = false, uint16_t blinkTimeout = 0, const uint8_t startIndex = 0, const uint8_t endIndex = TM_DISPLAY_SIZE);
    ~SimpleTextEffect();

    void loop(void);
};
