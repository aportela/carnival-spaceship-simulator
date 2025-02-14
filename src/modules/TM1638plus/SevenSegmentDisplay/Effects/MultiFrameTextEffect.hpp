#include <stdint.h>
#include <stdlib.h>
#include <TM1638plus.h>

class MultiFrameTextEffect
{
private:
    TM1638plus *module = nullptr;
    const char **frames = nullptr;
    size_t frameCount = 0;
    uint16_t frameTimeout = 0;
    uint8_t startIndex = 0;
    uint8_t currentFrameIndex = 0;
    uint64_t lastTimestamp = 0;

public:
    MultiFrameTextEffect(TM1638plus *module, const char *frames[], size_t frameCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0);
    ~MultiFrameTextEffect();

    void loop(void);
};
