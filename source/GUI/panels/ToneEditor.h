#pragma once
#ifndef ToneEditor_h
#define ToneEditor_h
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "GUI/Components/ModuleEditor.h"
#include "GUI/Components/GraphicEQ.h"
#include "GUI/Components/ParaEQ.h"
#include "GUI/Components/PultecEQ.h"
#include "GUI/lookandfeel/TextButtonLAF.h"

namespace viator
{

class ToneEditor : public viator::ModuleEditor
{
public:
    ToneEditor(PluginProcessor&);
    ~ToneEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    PluginProcessor& audio_processor;

    std::unique_ptr<juce::DropShadower> drop_shadow;

    std::vector<std::unique_ptr<juce::TextButton>> page_buttons;
    void init_page_buttons();
    const int page_button_radio_id = 1000;
    viator::CustomTextButton text_button_laf;

    std::vector<std::unique_ptr<juce::Component>> eq_editors;
    void init_editors();
    void close_editors() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToneEditor)
};

}

#endif 
