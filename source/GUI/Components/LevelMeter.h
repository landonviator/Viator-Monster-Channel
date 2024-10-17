#pragma once
#ifndef LevelMeter_h
#define LevelMeter_h

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include "../lookandfeel/Gradient.h"
#include "../look.h"

namespace viator
{

class LevelMeter : public juce::Component
{
public:
    LevelMeter() = default;

    void paint (juce::Graphics&) override;

    void setLevel(float newLevel);

    float getReduction()
    {
        return smoothedGainReduction;
    }

private:

    float smoothedGainReduction = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};

}

#endif 
