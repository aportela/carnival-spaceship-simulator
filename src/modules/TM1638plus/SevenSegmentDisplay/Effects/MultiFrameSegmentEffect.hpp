#include <stdint.h>
#include <stdlib.h>

class MultiFrameSegmentEffect
{
public:
    MultiFrameSegmentEffect(const char *frames[], size_t frameCount, uint16_t frameTimeout = 0, const uint8_t startIndex = 0);
    ~MultiFrameSegmentEffect();

    void loop(void);
};
