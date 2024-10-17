#pragma once
#ifndef PreampEditor_h
#define PreampEditor_h

#include "GUI/Components/ModuleEditor.h"
#include "GUI/Components/DriveViewer.h"
#include "../lookandfeel/SliderLAF.h"
#include "Global/Globals.h"

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>

class PluginProcessor;

namespace viator
{

class PreampEditor final : public viator::ModuleEditor,
 public juce::ActionBroadcaster
{
public:
    explicit PreampEditor(PluginProcessor&);
    ~PreampEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    viator::DriveViewer& getViewer() {return drive_viewer;}

    std::vector<std::unique_ptr<juce::Slider>>& getSliders () { return sliders; }
    
private:

    PluginProcessor& audio_processor;

    std::unique_ptr<juce::DropShadower> drop_shadow;

    viator::DriveViewer drive_viewer;

    std::vector<std::unique_ptr<juce::Slider>> sliders;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> attachments;
    void init_sliders();

    const juce::StringArray slider_ids =
    {
        ViatorParameters::preamp_low_cutID, ViatorParameters::preamp_toneID,
        ViatorParameters::preamp_high_cutID, ViatorParameters::preamp_driveID,
        ViatorParameters::preamp_mixID, ViatorParameters::preamp_outputID
    };

    const juce::StringArray slider_names =
    {
        ViatorParameters::preamp_low_cutName, ViatorParameters::preamp_toneName,
        ViatorParameters::preamp_high_cutName, ViatorParameters::preamp_driveName,
        ViatorParameters::preamp_mixName, ViatorParameters::preamp_outputName
    };

    viator::CustomDial dial_laf;
    viator::CustomDial dial_lafFloat;
    viator::ChickenHeadDial chicken_head_dial;
    viator::WaveyDial waveyLAF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreampEditor)
};

}

#endif 
