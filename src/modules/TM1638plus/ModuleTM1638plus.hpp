#ifndef MODULE_TM1638_PLUS_H
#define MODULE_TM1638_PLUS_H

#include <stdint.h>
#include <TM1638plus.h>

#include "Buttons/TM1638plusButtons.hpp"
#include "SevenSegmentDisplay/ISevenSegmentDisplayEffect.hpp"
// #include "SevenSegmentDisplay/SevenSegmentDisplayEffect.hpp"
#include "Leds/ILedEffect.hpp"
#include "Leds/Effects/ScannerLedEffect.hpp"
#include "Leds/Effects/ChaseLedEffect.hpp"
#include "Leds/Effects/VuMeterLedEffect.hpp"
#include "Leds/Effects/VuMeterMirroredLedEffect.hpp"
#include "Leds/Effects/AlternateLedEffect.hpp"
#include "Leds/Effects/IntermitentLedEffect.hpp"
#include "Leds/Effects/MorseLedEffect.hpp"
#include "SevenSegmentDisplay/Effects/SimpleTextEffect.hpp"
#include "SevenSegmentDisplay/Effects/MultiFrameTextEffect.hpp"
#include "SevenSegmentDisplay/Effects/MultiFrameSegmentEffect.hpp"
#include "SevenSegmentDisplay/Effects/MultiFrameIndividualSegmentEffect.hpp"

#define MAX_BRIGHTNESS 8

enum LED_EFFECT_TYPE
{
    LED_EFFECT_TYPE_NONE = 0,
    LED_EFFECT_TYPE_SCANNER = 1,
    LED_EFFECT_TYPE_CHASE = 2,
    LED_EFFECT_TYPE_VUMETER = 3,
    LED_EFFECT_TYPE_VUMETER_MIRRORED = 4,
    LED_EFFECT_TYPE_ALTERNATE = 5,
    LED_EFFECT_TYPE_INTERMITENT = 6,
    LED_EFFECT_TYPE_MORSE_LETTER_S = 7,
    LED_EFFECT_TYPE_MORSE_LETTER_O = 8,
};

enum SEVEN_SEGMENT_BLOCKS
{
    SEVEN_SEGMENT_BLOCK_LEFT = 1,
    SEVEN_SEGMENT_BLOCK_RIGHT = 2,
    SEVEN_SEGMENT_BLOCK_BOTH = 3,
};

class ModuleTM1638plus
{
private:
    TM1638plus *module = nullptr;

    TM1638plusButtons *buttons = nullptr;

    ILedEffect *ledEffect = nullptr;
    LED_EFFECT_TYPE currentLedEffectType = LED_EFFECT_TYPE_NONE;

    ISevenSegmentDisplayEffect *SevenSegmentLeftBlock = nullptr;  // first 4 seven segments
    ISevenSegmentDisplayEffect *SevenSegmentRightBlock = nullptr; // last 4 seven segments
    ISevenSegmentDisplayEffect *SevenSegmentBothBlocks = nullptr; // all 8 (4 left + 4 right) seven segments

public:
    ModuleTM1638plus(uint8_t strobePIN, uint8_t clockPIN, uint8_t dioPIN, bool highFreq);
    ~ModuleTM1638plus();

    TM1638plusBUTTON getPressedButton(void);

    void toggleSevenSegmentEffect(void);

    void toggleLedEffect(uint16_t msDelay = DEFAULT_LED_MS_DELAY);
    LED_EFFECT_TYPE getCurrentLedEffect(void);
    void setLedEffect(LED_EFFECT_TYPE effect, uint16_t msDelay = DEFAULT_LED_MS_DELAY);
    void toggleLedInverseMode(void);

    void clearSevenSegmentBlock(SEVEN_SEGMENT_BLOCKS block);

    void freeSevenSegmentLeftBlock();
    void freeSevenSegmentRightBlock();
    void freeSevenSegmentBothBlocks();

    void displayTextOnLeft7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);
    void displayTextOnRight7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);
    void displayTextOnFull7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);
    void refreshTextOnLeft7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);
    void refreshTextOnRight7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);
    void refreshTextOnFull7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);

    void displayMultiFrameTextEffect(const char *frames[], size_t frameCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0);
    void displayMultiFrameSevenSegmentEffect(const uint8_t frames[], size_t frameCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0, const uint8_t endIndex = 7);
    void displayMultiFrameIndividualSevenSegmentEffect(uint8_t **frames, size_t frameCount, size_t frameAffectedSegmentCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0, const uint8_t endIndex = 7);

    void loop(void);
};

#endif // MODULE_TM1638_PLUS_H
