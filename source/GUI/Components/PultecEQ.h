#pragma once
#ifndef PultecEQ_h
#define PultecEQ_h

#include "../lookandfeel/Gradient.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

namespace viator
{

    class PultecEQ : public juce::Component
    {
    public:
        PultecEQ()
        {
        }

        ~PultecEQ() override
        {
        }

        void paint (juce::Graphics& g) override
        {
            g.fillAll(juce::Colours::blue);
        }

        void resized() override
        {
        }

    private:

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PultecEQ)
    };

}

#endif 
