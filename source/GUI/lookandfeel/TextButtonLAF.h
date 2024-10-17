#pragma once
#ifndef TextButtonLAF_h
#define TextButtonLAF_h

#include <juce_gui_basics/juce_gui_basics.h>

namespace viator
{
    class CustomTextButton final : public juce::LookAndFeel_V4
    {
        public:
        CustomTextButton() = default;
        
        void drawButtonBackground (juce::Graphics& g,
                                   juce::Button& button,
                                   const juce::Colour& backgroundColour,
                                   bool shouldDrawButtonAsHighlighted,
                                   bool shouldDrawButtonAsDown) override;
        
        juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override;
        
        void drawButtonText (juce::Graphics& g, juce::TextButton& button,
                             bool boolshouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    };
}

#endif
