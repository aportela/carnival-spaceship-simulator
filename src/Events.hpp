#ifndef EVENTS_H
#define EVENTS_H

#include "modules/ExternalButtons/ExternalButtons.hpp"
#include "modules/TM1638plus/ModuleTM1638plus.hpp"
#include "modules/TM1638plus/Buttons/TM1638plusButtons.hpp"
#include "modules/Audio/Sampler.hpp"

enum ANIMATION
{
    ANIMATION_NONE = 0,
    ANIMATION_LASER_SHOOT = 1,
    ANIMATION_SOS_1 = 2,
    ANIMATION_SOS_2 = 3,
    ANIMATION_SOS_3 = 4,
    ANIMATION_ALIEN_VOICE_1 = 5,
    ANIMATION_ALIEN_VOICE_2 = 6,
    ANIMATION_ALIEN_VOICE_3 = 7,
    ANIMATION_ALIEN_VOICE_4 = 8,
};

class Events
{
private:
    ExternalButtons *externalButtonsPtr = nullptr;
    ModuleTM1638plus *tm1638plusPtr = nullptr;
    Sampler *samplerPtr = nullptr;

    uint8_t currentLaserSamplesPlaying = 0;
    uint16_t laserShoots = 0;

    LED_EFFECT_TYPE previousLedEffect = LED_EFFECT_TYPE_NONE;
    ANIMATION currentAnimation = ANIMATION_NONE;

    void display7SegmentLaserAnimation(void);

public:
    Events(ExternalButtons *externalButtonsPtr, ModuleTM1638plus *tm1638plusPtr, Sampler *samplerPtr);
    ~Events();
    void onExternalButton(EXTERNAL_BUTTON button);
    void onTM1638plusButton(TM1638plusBUTTON button);
    void onSampleStarted(SAMPLE sample);
    void onSampleStopped(SAMPLE sample);
    void startAnimation(ANIMATION animation);
    void stopAnimation();
};

#endif // EVENTS_H
