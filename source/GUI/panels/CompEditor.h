#pragma once
#ifndef CompEditor_h
#define CompEditor_h
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "GUI/Components/ModuleEditor.h"
#include "GUI/Components/GRMeter.h"
#include "../lookandfeel/SliderLAF.h"
#include "../lookandfeel/TextButtonLAF.h"

class PluginProcessor;

namespace viator
{

class CompEditor : public viator::ModuleEditor
    , private juce::Timer
{
public:
    explicit CompEditor(PluginProcessor&, bool isCompOne);
    ~CompEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
private:

    PluginProcessor& audio_processor;

    bool isCompA = true;

    std::unique_ptr<juce::DropShadower> drop_shadow;

    std::vector<std::unique_ptr<juce::Slider>> compDials;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> attachments;
    viator::CustomDial dial_laf;
    viator::ChickenHeadDial chicken_head_dial;
    viator::WaveyDial waveyLAF;
    void initCompDials();

    viator::GRMeter grMeter;

    void timerCallback() override;

    std::vector<std::unique_ptr<juce::TextButton>> buttons;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>> buttonAttachments;
    CustomTextButton textBtnLAF;
    void initButtons();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompEditor)
};

}

#endif 
