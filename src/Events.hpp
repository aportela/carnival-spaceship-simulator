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
    ANIMATION_ALIEN_VOICE_5 = 9,
    ANIMATION_ALIEN_VOICE_6 = 10,
    ANIMATION_ALIEN_VOICE_7 = 11,
    ANIMATION_ALIEN_VOICE_8 = 12,
    ANIMATION_ALIEN_VOICE_9 = 13,
    ANIMATION_DIRTY_SYREN_1 = 14,
    ANIMATION_DIRTY_SYREN_2 = 15,
    ANIMATION_ALARM_REVERB = 16,
    ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_1 = 17,
    ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_2 = 18,
    ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_3 = 19,
    ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_4 = 20,
    ANIMATION_CLOSE_ENCOUNTERS_ON_THIRD_PHASE_5 = 21,
    ANIMATION_DEFAULT = 22,
};

class Events
{
private:
    ExternalButtons *externalButtonsPtr = nullptr;
    ModuleTM1638plus *tm1638plusPtr = nullptr;
    Sampler *samplerPtr = nullptr;

    uint8_t currentLaserSamplesPlaying = 0;
    bool isPlayingAlienVoiceSamples = false;
    bool isPlayingSOSSamples = false;
    bool isPlayingEncountersOnThirdPhaseSamples = false;
    bool isPlayingAlarmReverbSamples = false;
    bool isPlayingDirtySyren1Sample = false;
    bool isPlayingDirtySyren2Sample = false;
    uint16_t laserShoots = 0;

    LED_ANIMATION_TYPE previousLedEffect = LED_ANIMATION_TYPE_NONE;
    ANIMATION currentAnimation = ANIMATION_NONE;

    SEVEN_SEGMENT_ANIMATION_TYPE previousSevenSegmentAnimation = SEVEN_SEGMENT_ANIMATION_TYPE_NONE;
    SAMPLE lastAlienVoiceSamplePlayed = SAMPLE_NONE;

    bool allowStartAnimation(ANIMATION animation);
    void refreshAnimation(ANIMATION animation);

public:
    Events(ExternalButtons *externalButtonsPtr, ModuleTM1638plus *tm1638plusPtr, Sampler *samplerPtr);
    ~Events();
    void onExternalButton(EXTERNAL_BUTTON button);
    void onTM1638plusButton(TM1638plusBUTTON button);
    void onSampleStarted(SAMPLE sample);
    void onSampleStopped(SAMPLE sample);
    void startAnimation(ANIMATION animation);
    void stopAnimation(ANIMATION animation);
};

#endif // EVENTS_H
