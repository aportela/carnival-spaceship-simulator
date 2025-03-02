#ifndef MODULE_TM1638_PLUS_H
#define MODULE_TM1638_PLUS_H

#include <cstdint>
#include <cstring>
#include <TM1638plus.h>

#include "Buttons/TM1638plusButtons.hpp"
#include "SevenSegmentDisplay/ISevenSegmentDisplayEffect.hpp"
#include "Leds/ILedEffect.hpp"
#include "Leds/Effects/ScannerLedEffect.hpp"
#include "Leds/Effects/ChaseLedEffect.hpp"
#include "Leds/Effects/VuMeterLedEffect.hpp"
#include "Leds/Effects/VuMeterMirroredLedEffect.hpp"
#include "Leds/Effects/AlternateLedEffect.hpp"
#include "Leds/Effects/IntermitentLedEffect.hpp"
#include "Leds/Effects/MorseLedEffect.hpp"
#include "Leds/Effects/NotesLedEffect.hpp"
#include "SevenSegmentDisplay/Effects/SimpleTextEffect.hpp"
#include "SevenSegmentDisplay/Effects/MultiFrameTextEffect.hpp"
#include "SevenSegmentDisplay/Effects/MultiFrameSegmentEffect.hpp"
#include "SevenSegmentDisplay/Effects/MultiFrameIndividualSegmentEffect.hpp"

#define MAX_BRIGHTNESS 8

enum LED_ANIMATION_TYPE
{
    LED_ANIMATION_TYPE_NONE = 0,
    LED_ANIMATION_TYPE_SCANNER = 1,
    LED_ANIMATION_TYPE_CHASE = 2,
    LED_ANIMATION_TYPE_VUMETER = 3,
    LED_ANIMATION_TYPE_VUMETER_MIRRORED = 4,
    LED_ANIMATION_TYPE_ALTERNATE = 5,
    LED_ANIMATION_TYPE_INTERMITENT = 6,
    // CUSTOM SAMPLE LED ANIMATIONS
    LED_ANIMATION_TYPE_MORSE_LETTER_S = 7,
    LED_ANIMATION_TYPE_MORSE_LETTER_O = 8,
    LED_ANIMATION_TYPE_NOTES = 9,
};

enum SEVEN_SEGMENT_BLOCKS
{
    SEVEN_SEGMENT_BLOCK_LEFT = 1,
    SEVEN_SEGMENT_BLOCK_RIGHT = 2,
    SEVEN_SEGMENT_BLOCK_BOTH = 3,
};

enum SEVEN_SEGMENT_ANIMATION_TYPE
{
    SEVEN_SEGMENT_ANIMATION_TYPE_NONE = 0,
    SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_1 = 1,
    SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_2 = 2,
    SEVEN_SEGMENT_ANIMATION_TYPE_FULL_PATTERN_3 = 3,
    SEVEN_SEGMENT_ANIMATION_TYPE_LASER = 4,
    SEVEN_SEGMENT_ANIMATION_TYPE_SOS_1 = 5,
    SEVEN_SEGMENT_ANIMATION_TYPE_SOS_2 = 6,
    SEVEN_SEGMENT_ANIMATION_TYPE_SOS_3 = 7,
    SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_1 = 8,
    SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_2 = 9,
    SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_3 = 10,
    SEVEN_SEGMENT_ANIMATION_TYPE_ALIEN_VOICE_4 = 11,
    SEVEN_SEGMENT_ANIMATION_TYPE_ALARM_REVERB = 12,
    SEVEN_SEGMENT_ANIMATION_TYPE_DIRTY_SYREN_1 = 13,
    SEVEN_SEGMENT_ANIMATION_TYPE_DIRTY_SYREN_2 = 14,
    SEVEN_SEGMENT_ANIMATION_TYPE_NOTES = 15,
    SEVEN_SEGMENT_ANIMATION_TYPE_WAVE = 16,
    SEVEN_SEGMENT_ANIMATION_TYPE_MESSAGE_1 = 20, // "PILI DE LEIRO"
};

class ModuleTM1638plus
{
private:
    TM1638plus *modulePtr = nullptr;

    TM1638plusButtons *buttonsPtr = nullptr;

    ILedEffect *currentLedAnimationPtr = nullptr;
    LED_ANIMATION_TYPE currentLedAnimationType = LED_ANIMATION_TYPE_NONE;
    LED_ANIMATION_TYPE defaultLedAnimationType = LED_ANIMATION_TYPE_NONE;
    uint16_t defaultLedAnimationMSDelay = 0;

    SEVEN_SEGMENT_ANIMATION_TYPE currentSevenSegmentAnimationType = SEVEN_SEGMENT_ANIMATION_TYPE_NONE;
    SEVEN_SEGMENT_ANIMATION_TYPE defaultSevenSegmentAnimationType = SEVEN_SEGMENT_ANIMATION_TYPE_NONE;
    uint16_t defaultSevenSegmentAnimationMSDelay = 0;

    ISevenSegmentDisplayEffect *SevenSegmentLeftBlockPtr = nullptr;  // first 4 seven segments
    ISevenSegmentDisplayEffect *SevenSegmentRightBlockPtr = nullptr; // last 4 seven segments
    ISevenSegmentDisplayEffect *SevenSegmentBothBlocksPtr = nullptr; // all 8 (4 left + 4 right) seven segments

    void clearSevenSegmentBlock(SEVEN_SEGMENT_BLOCKS block);

    void setSevenSegmentLaserAnimation(uint16_t laserShoots);
    void updateSevenSegmentLaserCountAnimationText(uint16_t laserShoots);

    void setSevenSegmentOscilloscopeAnimation(void);

public:
    ModuleTM1638plus(uint8_t strobePIN, uint8_t clockPIN, uint8_t dioPIN, bool highFreq);
    ~ModuleTM1638plus();

    void reset(void);

    TM1638plusBUTTON getPressedButton(void);

    LED_ANIMATION_TYPE getCurrentLedAnimation(void);
    void toggleLedAnimation();
    void toggleLedAnimationInverseMode(void);
    void setLedAnimation(LED_ANIMATION_TYPE animation, uint16_t msDelay = DEFAULT_LED_MS_DELAY, bool isDefault = false);
    void setLedAnimationRandomDelay(uint16_t minRandomMSDelay, uint16_t maxRandomMSDelay, uint8_t randomMultiplier = 0);
    void restoreDefaultLedAnimation(void);

    SEVEN_SEGMENT_ANIMATION_TYPE getCurrentSevenSegmentAnimation(void);
    void toggleSevenSegmentAnimation();
    void setSevenSegmentAnimation(SEVEN_SEGMENT_ANIMATION_TYPE animation, uint16_t msDelay = DEFAULT_SEVEN_SEGMENT_MS_DELAY, uint16_t extraData = 0, bool isDefault = false);
    void setSevenSegmentBothBlocksAnimationRandomDelay(uint16_t minRandomMSDelay, uint16_t maxRandomMSDelay, uint8_t randomMultiplier = 0);
    void restoreDefaultSevenSegmentAnimation(void);

    void freeSevenSegmentLeftBlock(void);
    void freeSevenSegmentRightBlock(void);
    void freeSevenSegmentBothBlocks(void);

    void displayTextOnLeft7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0, bool freePrevious = false);
    void displayTextOnRight7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0, bool freePrevious = false);
    void displayTextOnFull7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0, bool freePrevious = false);
    void refreshTextOnLeft7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);
    void refreshTextOnRight7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);
    void refreshTextOnFull7Segment(const char *text, bool blink = false, uint16_t blinkTimeout = 0);

    void displayMultiFrameTextEffect(const char *frames[], size_t frameCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0, bool freePrevious = false);
    void displayMultiFrameSevenSegmentEffect(const uint8_t frames[], size_t frameCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0, const uint8_t endIndex = 7, bool freePrevious = false);
    void displayMultiFrameIndividualSevenSegmentEffect(uint8_t **frames, size_t frameCount, size_t frameAffectedSegmentCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0, const uint8_t endIndex = 7, bool freePrevious = false);

    void loop(void);
};

#endif // MODULE_TM1638_PLUS_H
