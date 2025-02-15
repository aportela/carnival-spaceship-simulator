#include "modules/Audio/Sampler.hpp"
#include "modules/ExternalButtons/ExternalButtons.hpp"
#include "modules/TM1638plus/Buttons/TM1638plusButtons.hpp"

class Events
{
public:
    Events(void);
    ~Events();

    void onExternalButton(EXTERNAL_BUTTON button);
    void onTM1638plusBUTTON(TM1638plusBUTTON button);
    void onSampleStarted(SAMPLE sample);
    void onSampleStopped(SAMPLE sample);
};
