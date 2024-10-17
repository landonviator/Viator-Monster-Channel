#pragma once
#ifndef GraphicEQ_h
#define GraphicEQ_h

#include "../lookandfeel/SliderLAF.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "../../PluginProcessor.h"

namespace viator
{

class GraphicEQEditor final : public juce::Component
{
public:
    explicit GraphicEQEditor(PluginProcessor& p) : audio_processor(p)
    {
        initSliders();
    }

    ~GraphicEQEditor() override
    {
        for (const auto& slider : sliders)
        {
            slider->setLookAndFeel(nullptr);
        }
    }

    void paint (juce::Graphics& g) override
    {
    }

    void resized() override
    {
        auto compX = static_cast<int>(getWidth() * 0.018);
        const auto compY = static_cast<int>(getHeight() * 0.1);
        const auto compWidth = static_cast<int>(getWidth() * 0.083);
        const auto compHeight = static_cast<int>(getHeight() * 0.8);
        const auto padding = static_cast<int>(getHeight() * 0.05);
        for (const auto& slider : sliders)
        {
            slider->setBounds(compX, compY, compWidth, compHeight);
            slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, slider->getWidth(), static_cast<int>(compHeight * 0.1));
            compX += compWidth + padding;
        }
    }
    
private:
    PluginProcessor& audio_processor;

    std::vector<std::unique_ptr<juce::Slider>> sliders;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAtts;
    Fader faderLAF;
    void initSliders()
    {
        constexpr int numSliders = 10;
        const auto graphicCutoffs = ViatorParameters::graphicEQCutoffs;

        for (int i = 0; i < numSliders; ++i)
        {
            sliders.emplace_back(std::make_unique<juce::Slider>());
            sliderAtts.emplace_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                (audio_processor.get_tree_state(), "graphicEQGainID" + juce::String(i), *sliders[i]));
            sliders[i]->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
            sliders[i]->setName(juce::String(graphicCutoffs[i]) + " Hz");
            sliders[i]->setLookAndFeel(&faderLAF);
            addAndMakeVisible(*sliders[i]);
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicEQEditor)
};

}

#endif 
