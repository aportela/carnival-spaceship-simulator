#ifndef TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_INTERFACE_H
#define TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_INTERFACE_H

class ISevenSegmentDisplayEffect
{
public:
    virtual ~ISevenSegmentDisplayEffect() {}
    virtual void loop(void) = 0;
    virtual bool isSimpleTextEffect() { return false; }
    virtual bool isMultiFrameTextEffect() { return false; }
    virtual bool isMultiFrameSegmentEffect() { return false; }
};

#endif // TM1638_PLUS_SEVEN_SEGMENT_DISPLAY_EFFECT_INTERFACE_H
