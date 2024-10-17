#pragma once
#ifndef ParaEQ_h
#define ParaEQ_h

#include "../lookandfeel/Gradient.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

namespace viator
{

    class ParaEQ : public juce::Component
    {
    public:
        ParaEQ()
        {
        }

        ~ParaEQ() override
        {
        }

        void paint (juce::Graphics& g) override
        {
            g.fillAll(juce::Colours::green);
        }

        void resized() override
        {
        }

    private:

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParaEQ)
    };

}

#endif
