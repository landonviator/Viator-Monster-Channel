#pragma once

#include "PluginProcessor.h"
#include "BinaryData.h"
#include "GUI/lookandfeel/Gradient.h"
#include "GUI/panels/PreampEditor.h"
#include "GUI/panels/SurgicalEditor.h"
#include "GUI/panels/CompEditor.h"
#include "GUI/panels/ToneEditor.h"
#include "GUI/panels/ConsoleEditor.h"
#include "GUI/panels/info_panel.h"
#include "GUI/utils/window.h"
#include "GUI/lookandfeel/TextButtonLAF.h"
#include "GUI/lookandfeel/MenuLAF.h"
#include "GUI/lookandfeel/SliderLAF.h"
#include "GUI/Components/LevelMeter.h"
#include "GUI/look.h"

//==============================================================================
class PluginEditor :
        public juce::AudioProcessorEditor
    , public juce::ActionListener
 , public juce::Timer
{
public:
    explicit PluginEditor (PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& audio_processor;

    std::vector<std::unique_ptr<juce::TextButton>> page_buttons;
    void init_page_buttons();
    const int page_button_radio_id = 1000;
    viator::CustomTextButton text_button_laf;

    std::vector<std::unique_ptr<viator::ModuleEditor>> module_editors;
    void init_editors();
    void close_editors() const;

    void actionListenerCallback(const juce::String &message) override;

    juce::ComboBox hq_menu;
    void init_hq_menu();

    juce::ComboBox stereo_menu;
    void init_stereo_menu();

    std::unique_ptr<juce::DrawableButton> power_button, settings_button, preset_a_button, preset_b_button;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> power_att;
    void setControlButtonProps(std::unique_ptr<juce::DrawableButton>& button,
                               const juce::Drawable* offImage,
                               const juce::Drawable* onImage,
                               const juce::String& name);
    void init_buttons();
    void apply_preset(bool isPresetA);
    void save_preset(const juce::String& param, float paramValue) const;

    viator::CustomMenu menuLAF;

    std::vector<std::unique_ptr<juce::Slider>> sliders;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAtts;
    viator::Fader faderLAF;
    void initSliders();
    void applyInputToDriveViewer() const;
    void applyOutputToDriveViewer() const;

    viator::LevelMeter input_meter;
    viator::LevelMeter output_meter;

    viator::InfoPanel info_panel;

    void timerCallback() override;

    juce::Label tooltip_window;
    void init_tooltip_window();

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit(const juce::MouseEvent& e) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};