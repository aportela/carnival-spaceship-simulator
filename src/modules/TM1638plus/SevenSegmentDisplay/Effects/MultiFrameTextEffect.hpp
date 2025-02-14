#include <stdint.h>

class MultiFrameTextEffect
{
public:
    MultiFrameTextEffect(const char *frames[], size_t frameCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0);
    ~MultiFrameTextEffect();

    void loop(void);
}