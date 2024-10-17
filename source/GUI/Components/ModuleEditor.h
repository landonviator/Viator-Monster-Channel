#pragma once
#ifndef ModuleEditor_h
#define ModuleEditor_h

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "../lookandfeel/Gradient.h"
#include "../look.h"

namespace viator
{

class ModuleEditor : public juce::Component
{
public:
    ModuleEditor();
    ~ModuleEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
private:

    std::unique_ptr<juce::DropShadower> drop_shadow;

    void init_background(juce::Graphics& g) const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleEditor)
};

}

#endif 
