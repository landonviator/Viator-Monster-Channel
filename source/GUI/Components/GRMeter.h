#pragma once
#ifndef GRMeter_h
#define GRMeter_h

#include "../lookandfeel/Gradient.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

namespace viator
{

class GRMeter : public juce::Component
{
public:
    GRMeter();
    ~GRMeter() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setGR(float newGR);
    float getReduction() {return smoothedGainReduction;}

private:

    std::unique_ptr<juce::DropShadower> drop_shadow;

    juce::Colour muted_white = juce::Colour(120, 130, 140);
    const juce::Colour gold = juce::Colour(161, 121, 83);

    std::vector<int> grGuides;

    const float smoothingFactor = 0.6f;
    float smoothedGainReduction = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GRMeter)
};

}

#endif 
