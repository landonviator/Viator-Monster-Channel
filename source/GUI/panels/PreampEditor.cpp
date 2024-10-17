#include "PreampEditor.h"
#include "../../PluginProcessor.h"

namespace viator
{

PreampEditor::PreampEditor(PluginProcessor &p) : audio_processor(p)
{
    init_sliders();
    addAndMakeVisible(drive_viewer);
}

PreampEditor::~PreampEditor()
{
    for (const auto &dial : sliders)
    {
        dial->setLookAndFeel(nullptr);
        dial->removeMouseListener(this);
    }
}

void PreampEditor::paint(juce::Graphics &g)
{
    viator::ModuleEditor::paint(g);
}

void PreampEditor::resized()
{
    viator::ModuleEditor::resized();

    drive_viewer.setBounds(
        getLocalBounds().withSizeKeepingCentre(
            static_cast<int>(getWidth() * 0.85),
            static_cast<int>(getHeight() * 0.25)).withY(
            static_cast<int>(getHeight() * 0.15)));

    auto size = static_cast<int>(getWidth() * 0.2);
    auto compY = static_cast<int>(getHeight() * 0.45);
    sliders[3]->setBounds(getLocalBounds().withSizeKeepingCentre(size, size).withY(compY));
    sliders[3]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, sliders[3]->getWidth(), 32);

    size = static_cast<int>(getWidth() * 0.12);
    auto compX = static_cast<int>(getWidth() * 0.07);
    compY = static_cast<int>(getHeight() * 0.56);
    auto padding = static_cast<int>(size * 0.9);

    for (int i = 0; i < 3; ++i)
    {
        sliders[i]->setBounds(compX, compY, size, size);
        sliders[i]->setTextBoxStyle(
            juce::Slider::TextBoxBelow,
            false,
            sliders[i]->getWidth(),
            32);
        compX += padding;
    }

    size = static_cast<int>(getWidth() * 0.16);
    compY = static_cast<int>(getHeight() * 0.5);
    compX = static_cast<int>(getWidth() * 0.6);
    padding = static_cast<int>(size);

    for (int i = 4; i < 6; ++i)
    {
        sliders[i]->setBounds(compX, compY, size, size);
        sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, sliders[i]->getWidth(), 32);
        compX += padding;
    }
}

void PreampEditor::init_sliders()
{
    for (int i = 0; i < slider_ids.size(); ++i)
    {
        sliders.emplace_back(std::make_unique<juce::Slider>());
        attachments.emplace_back(
            std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
                audio_processor.get_tree_state(),
                slider_ids[i],
                *sliders[i]
            )
        );

        sliders[i]->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        sliders[i]->setName(slider_names[i]);
        sliders[i]->setComponentID(slider_ids[i]);
        sliders[i]->addMouseListener(this, true);
        addAndMakeVisible(*sliders[i]);
    }

    waveyLAF.setDialValueType(WaveyDial::ValueType::kInt);
    sliders[0]->setLookAndFeel(&waveyLAF);
    sliders[0]->setTooltip("Adjust the Cutoff to filter out low-end frequencies, allowing only the higher frequencies "
                           "to pass through. \nUse this to clean up muddiness, tighten your mix, or create a crisp, "
                           "focused sound by removing unwanted bass.");
    sliders[1]->setLookAndFeel(&waveyLAF);
    sliders[1]->setTooltip("Use the Tone knob to boost or reduce the high frequencies, shaping the brightness and "
                           "clarity of your sound. \nIncrease for a sharper, more present tone, or decrease to smooth "
                           "out the highs and add warmth.");
    sliders[2]->setLookAndFeel(&waveyLAF);
    sliders[2]->setTooltip("Adjust the Lowpass Cutoff to filter out high-end frequencies, allowing only the lower "
                           "frequencies to pass through. Use this to soften harsh tones, create a warmer sound, or "
                           "achieve a more subdued and mellow character by removing treble content.");

    sliders[3]->setLookAndFeel(&chicken_head_dial);
    sliders[3]->setTooltip("Increase the Drive to add warmth and character by saturating your signal. \nHigher settings "
                           "introduce more harmonic richness, adding grit and intensity to your sound.");

    dial_laf.setDialValueType(CustomDial::ValueType::kInt);
    sliders[4]->setLookAndFeel(&dial_laf);
    sliders[4]->setTooltip("Balance the amount of saturation applied to your signal with the Mix knob. "
                           "\nIncrease for more harmonics and warmth, or dial it back to retain more of the original, cleaner sound.");
    dial_lafFloat.setDialValueType(CustomDial::ValueType::kFloat);
    sliders[5]->setLookAndFeel(&dial_lafFloat);
    sliders[5]->setTooltip("Adjust the Output level of the saturated signal with this knob. \nIncrease to enhance "
                           "the impact and presence of the processed sound, or \ndecrease to maintain a balanced mix "
                           "between the original and saturated tones.");

    sliders[0]->onValueChange = [this]()
    {
        const auto cutoff = juce::jmap(static_cast<float>(sliders[0]->getValue()), 20.0f, 10000.0f, 1.0f, 40.0f);
        drive_viewer.set_low_cutoff(cutoff);
        sendActionMessage("sliderChanged");
    };

    auto cutoff = juce::jmap(static_cast<float>(sliders[0]->getValue()), 20.0f, 10000.0f, 1.0f, 40.0f);
    drive_viewer.set_low_cutoff(cutoff);

    sliders[1]->onValueChange = [this]()
    {
        const auto gain = static_cast<float>(sliders[1]->getValue());
        drive_viewer.update_tone_filter(gain);
        sendActionMessage("sliderChanged");
    };

    const auto gain = static_cast<float>(sliders[1]->getValue());
    drive_viewer.update_tone_filter(gain);

    sliders[2]->onValueChange = [this]()
    {
        const auto cutoff = juce::jmap(static_cast<float>(sliders[2]->getValue()), 40.0f, 20000.0f, 160.0f, 2000.0f);
        drive_viewer.set_high_cutoff(cutoff);
        sendActionMessage("sliderChanged");
    };

    cutoff = juce::jmap(static_cast<float>(sliders[2]->getValue()), 40.0f, 20000.0f, 160.0f, 2000.0f);
    drive_viewer.set_high_cutoff(cutoff);

    sliders[3]->onValueChange = [this]()
    {
        drive_viewer.set_drive(static_cast<float>(sliders[3]->getValue()));
        sendActionMessage("sliderChanged");
    };

    drive_viewer.set_drive(static_cast<float>(sliders[3]->getValue()));

    sliders[4]->onValueChange = [this]()
    {
        drive_viewer.set_mix(static_cast<float>(sliders[4]->getValue()));
        sendActionMessage("sliderChanged");
    };

    drive_viewer.set_mix(static_cast<float>(sliders[4]->getValue()));

    sliders[5]->onValueChange = [this]()
    {
        drive_viewer.set_output(static_cast<float>(sliders[5]->getValue()));
        sendActionMessage("sliderChanged");
    };

    drive_viewer.set_output(static_cast<float>(sliders[5]->getValue()));

    drive_viewer.repaint();
}

}
