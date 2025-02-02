#include "src/modules/TM1638plus/ModuleTM1638plus.hpp"

#define STROBE_TM 4 // strobe = GPIO connected to strobe line of module
#define CLOCK_TM 6  // clock = GPIO connected to clock line of module
#define DIO_TM 7    // data = GPIO connected to data line of module

ModuleTM1638plus *controlPanel = nullptr;

void setup()
{
    Serial.begin(9600);
    delay(100);
    controlPanel = new ModuleTM1638plus(STROBE_TM, CLOCK_TM, DIO_TM, false);
}

void loop()
{
    controlPanel->loop();
}
