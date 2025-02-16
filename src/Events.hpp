#ifndef EVENTS_H
#define EVENTS_H

#include "modules/ExternalButtons/ExternalButtons.hpp"
#include "modules/TM1638plus/ModuleTM1638plus.hpp"
#include "modules/TM1638plus/Buttons/TM1638plusButtons.hpp"
#include "modules/Audio/Sampler.hpp"

class Events
{
private:
    ExternalButtons *externalButtonsPtr = nullptr;
    ModuleTM1638plus *tm1638plusPtr = nullptr;
    Sampler *samplerPtr = nullptr;

    uint8_t currentLaserSamplesPlaying = 0;
    uint16_t laserShoots = 0;

    void loop(void);

public:
    Events(ExternalButtons *externalButtonsPtr, ModuleTM1638plus *tm1638plusPtr, Sampler *samplerPtr);
    ~Events();
    void onExternalButton(EXTERNAL_BUTTON button);
    void onTM1638plusButton(TM1638plusBUTTON button);
    void onSampleStarted(SAMPLE sample);
    void onSampleStopped(SAMPLE sample);
};

#endif // EVENTS_H
