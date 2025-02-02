#include "ScannerLedEffect.hpp"

const uint16_t ScannerLedEffect::individualLedMasks[8] = {0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000};

ScannerLedEffect::ScannerLedEffect(TM1638plus *module) : LedEffect(module)
{
}

ScannerLedEffect::~ScannerLedEffect()
{
}

bool ScannerLedEffect::loop(void)
{
    if (this->refresh())
    {
        this->inc = (this->currentLedIndex == 7) ? false : (this->currentLedIndex == 0 ? true : this->inc);
        uint16_t mask = this->individualLedMasks[currentLedIndex];
        if (inverse)
        {
            mask = 0xFFFF & ~mask;
        }
        this->module->setLEDs(mask);
        this->currentLedIndex = (this->currentLedIndex + (this->inc ? 1 : -1)) % 8;
        if (this->currentLedIndex < 0)
        {
            this->currentLedIndex += 8;
        }
        return (true);
    }
    else
    {
        return (false);
    }
}
