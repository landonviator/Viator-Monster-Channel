#pragma once
#ifndef ConsoleEditor_h
#define ConsoleEditor_h
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "GUI/Components/ModuleEditor.h"

namespace viator
{

class ConsoleEditor : public viator::ModuleEditor
{
public:
    ConsoleEditor();
    ~ConsoleEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
private:

    std::unique_ptr<juce::DropShadower> drop_shadow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsoleEditor)
};

}

#endif 
