#include "CompEditor.h"
#include "../../PluginProcessor.h"

namespace viator
{

CompEditor::CompEditor(PluginProcessor& p, bool isCompOne) : audio_processor(p)
{
    isCompA = isCompOne;
    initCompDials();
    initButtons();
    addAndMakeVisible(grMeter);
    startTimerHz(24);
}

CompEditor::~CompEditor()
{
    for (const auto& dial : compDials)
    {
        dial->setLookAndFeel(nullptr);
    }

    for (const auto& button : buttons)
    {
        button->setLookAndFeel(nullptr);
    }

    stopTimer();
}

void CompEditor::paint (juce::Graphics& g)
{
    viator::ModuleEditor::paint(g);
}

void CompEditor::resized()
{
    // Calculate the initial coordinates and size
    auto compX = static_cast<int>(getWidth() * 0.018);
    auto compY = static_cast<int>(getHeight() * 0.1);
    auto compWidth = static_cast<int>(getWidth() * 0.16);
    const auto padding = static_cast<int>(getHeight() * 0.065);

    // Initialize an index to keep track of the current dial's position
    auto index = 0;

    // Place Dials
    for (auto& dial : compDials)
    {
        dial->setBounds(compX, compY, compWidth, compWidth);
        dial->setTextBoxStyle(juce::Slider::TextBoxBelow, false, dial->getWidth(), 32);
        compX += compWidth;

        // After placing the second dial (index 1), start a new row for the next set of dials
        if (index == 1)
        {
            compX = static_cast<int>(getWidth() * 0.018);
            compY += compWidth + padding;
        }

        index++;
    }

    // place GR Meter
    compWidth = compDials[compDials.size() - 1]->getX() - compDials[1]->getRight();
    grMeter.setBounds(compDials[1]->getRight(), compDials[1]->getY(), compWidth, compDials[1]->getHeight());

    // Place Buttons
    compWidth = static_cast<int>(compDials[0]->getWidth() * 0.5);
    compX = compDials[7]->getX() + static_cast<int>(compDials[7]->getWidth() * 0.25);
    compY = grMeter.getY() + static_cast<int>(grMeter.getHeight() * 0.13);
    const auto height = static_cast<int>(compWidth * 0.5);
    for (auto& button : buttons)
    {
        button->setBounds(compX, compY, compWidth, height);
        compY += height * 2;
    }
}

void CompEditor::initCompDials()
{
    for (int i = 0; i < 8; ++i)
    {
        auto compID = isCompA ?
            audio_processor.getParameterMap()._compOneSliderParams[i].paramID :
            audio_processor.getParameterMap()._compTwoSliderParams[i].paramID;
        compDials.emplace_back(std::make_unique<juce::Slider>());
        attachments.emplace_back(
            std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
                audio_processor.get_tree_state(),
                compID,
                *compDials[i]));

        compDials[i]->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        auto name = isCompA ?
            audio_processor.getParameterMap()._compOneSliderParams[i].paramName :
            audio_processor.getParameterMap()._compTwoSliderParams[i].paramName;
        compDials[i]->setName(name);
        compDials[i]->setLookAndFeel(&dial_laf);
        addAndMakeVisible(*compDials[i]);
    }

    compDials[4]->setLookAndFeel(&chicken_head_dial);
    compDials[5]->setLookAndFeel(&chicken_head_dial);
    compDials[6]->setLookAndFeel(&waveyLAF);
    compDials[7]->setLookAndFeel(&waveyLAF);
}

void CompEditor::timerCallback()
{
    auto reduction = isCompA ? audio_processor.getComp1().getGainReduction() : audio_processor.getComp2().getGainReduction();
    auto compOn = buttons[1]->getToggleState();
    auto notTiny = reduction <= -0.1;

    if (!notTiny || !compOn || !audio_processor.getIsPlaying())
    {
        reduction = 0.0f;
    }

    grMeter.setGR(reduction);
}

void CompEditor::initButtons()
{
    juce::StringArray buttonIDsA = {ViatorParameters::compOneTypeID, ViatorParameters::compOnePowerID};
    juce::StringArray buttonNamesA = {ViatorParameters::compOneTypeName, ViatorParameters::compOnePowerName};
    juce::StringArray buttonIDsB = {ViatorParameters::compTwoTypeID, ViatorParameters::compTwoPowerID};
    juce::StringArray buttonNamesB = {ViatorParameters::compTwoTypeName, ViatorParameters::compTwoPowerName};

    for (int i = 0; i < 2; ++i)
    {
        buttons.emplace_back(std::make_unique<juce::TextButton>());
        buttonAttachments.emplace_back(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audio_processor.get_tree_state(), isCompA ? buttonIDsA[i] : buttonIDsB[i], *buttons[i]));
        buttons[i]->setClickingTogglesState(true);
        buttons[i]->setButtonText(isCompA ? buttonNamesA[i] : buttonNamesB[i]);
        buttons[i]->setColour(juce::TextButton::ColourIds::buttonColourId,
                                   juce::Colours::black.withAlpha(0.25f));
        buttons[i]->setColour(juce::TextButton::ColourIds::buttonOnColourId,
                                   juce::Colour(161, 121, 83));
        buttons[i]->setColour(juce::ComboBox::ColourIds::outlineColourId,
                                   juce::Colour(120, 130, 140));
        buttons[i]->setLookAndFeel(&textBtnLAF);
        addAndMakeVisible(*buttons[i]);
    }
}

}
