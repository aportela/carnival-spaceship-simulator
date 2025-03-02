#ifndef TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_H
#define TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_H

#define MAX_SPEED 16

#include <stdint.h>
#include <TM1638plus.h>
#include "ISevenSegmentDisplayEffect.hpp"

#define DEFAULT_SEVEN_SEGMENT_MS_DELAY 100
#define DEFAULT_7SEGMENT_MS_DELAY 100 // TODO: REMOVE
#define DEFAULT_SEVEN_SEGMENT_TEXT_EFFECT_MS_DELAY 300
#define DEFAULT_SEVEN_SEGMENT_LASER_EFFECT_MS_DELAY 60

/*

    Segments:

         AAAA
        F    B
        F    B
         GGGG
        E    C
        E    C
         DDDD
                DP

*/

#define SEGMENT_NONE 0x00
#define SEGMENT_A 0x01
#define SEGMENT_B 0x02
#define SEGMENT_C 0x04
#define SEGMENT_D 0x08
#define SEGMENT_E 0x10
#define SEGMENT_F 0x20
#define SEGMENT_G 0x40
#define SEGMENT_DP 0x80

class SevenSegmentDisplayEffect : public ISevenSegmentDisplayEffect
{
protected:
    TM1638plus *module = nullptr;
    size_t totalFrames = 0;
    size_t currentFrameIndex = 0;
    uint64_t lastRefresh = 0;
    uint8_t currentSpeed = 7;
    uint16_t msDelay = currentSpeed * DEFAULT_7SEGMENT_MS_DELAY;
    bool useRandomDelay = false;
    uint8_t randomMultiplier = 1;
    uint16_t minRandomMSDelay = 0;
    uint16_t maxRandomMSDelay = 0;
    uint64_t lastTimestamp = 0;

    bool refresh(void);

public:
    SevenSegmentDisplayEffect(TM1638plus *module, uint16_t msDelay = DEFAULT_7SEGMENT_MS_DELAY);
    ~SevenSegmentDisplayEffect();

    void setDelay(uint16_t msDelay) override;
    void setRandomDelay(uint16_t minRandomMSDelay, uint16_t maxRandomMSDelay, uint8_t randomMultiplier = 1) override;
    virtual void loop(void) = 0;

    virtual bool isSimpleTextEffect() { return false; }
    virtual bool isMultiFrameTextEffect() { return false; }
    virtual bool isMultiFrameSegmentEffect() { return false; }
    virtual bool isMultiFrameIndividualSegmentEffect() { return false; }
};

#endif // TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_H
