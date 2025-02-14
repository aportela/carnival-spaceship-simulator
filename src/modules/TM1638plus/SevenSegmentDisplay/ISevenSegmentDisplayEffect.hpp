#ifndef TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_INTERFACE_H
#define TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_INTERFACE_H

class ISevenSegmentDisplayEffect
{
public:
    virtual ~ISevenSegmentDisplayEffect() {}
    virtual bool loop(void) = 0;
};

#endif // TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_INTERFACE_H
