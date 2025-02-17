#include "SevenSegmentDisplayEffect.hpp"
#include "Arduino.h"

SevenSegmentDisplayEffect::SevenSegmentDisplayEffect(TM1638plus *module) : module(module)
{
    this->lastTimestamp = millis();
}

SevenSegmentDisplayEffect::~SevenSegmentDisplayEffect()
{
    this->module = nullptr;
}

bool SevenSegmentDisplayEffect::refresh(void)
{
    uint64_t timestamp = millis();
    if (timestamp - this->lastRefresh > this->msDelay)
    {
        this->lastRefresh = timestamp;
        return (true);
    }
    else
    {
        return (false);
    }
}

/*
uint8_t SevenSegmentDisplayEffect::toggleCurrentSpeed(void)
{
    if (this->currentSpeed <= MAX_SPEED)
    {
        this->currentSpeed *= 2;
        this->msDelay = this->currentSpeed * DEFAULT_MS_DELAY;
    }
    else
    {
        this->currentSpeed = 1;
    }
    this->msDelay = this->currentSpeed * DEFAULT_MS_DELAY;
    return (this->currentSpeed);
}
    */

/*

        const char *words[] = {
        "S.O.S.     ",
        " S.O.S.    ",
        "  S.O.S.   ",
        "   S.O.S.  ",
        "    S.O.S. ",
        "     S.O.S.",
        "    S.O.S. ",
        "   S.O.S.  ",
        "  S.O.S.   ",
        " S.O.S.    ",
        "S.O.S.     ",
        "CASA    ",
        " CASA   ",
        "  CASA  ",
        "   CASA ",
        "    CASA",
        "   CASA ",
        "  CASA  ",
        " CASA   ",
        "CASA    ",
        "CEAVA5  ",
        " CEAVA5 ",
        "  CEAVA5",
        " CEAVA5 ",
        "CEAVA5  ",
        " CEAVA5 ",
        "  CEAVA5",
        " CEAVA5 ",
        "CEAVA5  ",
    };

const char *words[] = {
    "PILI DE ",
    "ILI DE L",
    "LI DE LE",
    "I DE LEI",
    " DE LEIA",
    "DE LEIAO",
    " DE LEIA",
    "I DE LEI",
    "LI DE LE",
    "ILI DE L",
};

        this->totalFrames = sizeof(words) / sizeof(words[0]);
        // this->module->displayText(words[random(0, sizeof(words) / sizeof(words[0]))]);
        this->module->displayText(words[this->currentFrameIndex]);
        this->currentFrameIndex++;
        if (this->currentFrameIndex >= this->totalFrames)
        {
            this->currentFrameIndex = 0;
        }
        // const uint8_t seq[] = {SEGMENT_A, SEGMENT_B, SEGMENT_G, SEGMENT_E, SEGMENT_D, SEGMENT_C, SEGMENT_G, SEGMENT_F}; // A, B, G, E, D, C, G, F
        /*
        const uint8_t seq[] = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F}; // A, B, G, E, D, C, G, F
        this->totalFrames = sizeof(seq) / sizeof(seq[0]);
        if (this->currentFrameIndex >= this->totalFrames)
        {
            this->currentFrameIndex = 0;
        }
        this->module->display7Seg(0, seq[this->currentFrameIndex]);
        this->module->display7Seg(1, seq[this->currentFrameIndex]);
        this->module->display7Seg(2, seq[this->currentFrameIndex]);
        this->module->display7Seg(3, seq[this->currentFrameIndex]);
        this->module->display7Seg(4, seq[this->currentFrameIndex]);
        this->module->display7Seg(5, seq[this->currentFrameIndex]);
        this->module->display7Seg(6, seq[this->currentFrameIndex]);
        this->module->display7Seg(7, seq[this->currentFrameIndex]);
        this->currentFrameIndex++;

*/
