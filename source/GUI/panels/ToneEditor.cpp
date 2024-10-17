#include "ToneEditor.h"

namespace viator
{

ToneEditor::ToneEditor(PluginProcessor& p) : audio_processor(p)
{
    init_editors();
    init_page_buttons();
}

ToneEditor::~ToneEditor()
{
    for (const auto& button : page_buttons)
    {
        button->setLookAndFeel(nullptr);
    }
}

void ToneEditor::paint (juce::Graphics& g)
{
    viator::ModuleEditor::paint(g);
}

void ToneEditor::resized()
{
    // PAGE BUTTON POSITIONS
    const auto padding = static_cast<int>(getParentComponent()->getWidth() * 0.025);
    const auto compWidth = static_cast<int>(getParentComponent()->getWidth() * 0.075);
    const auto compY = static_cast<int>(getHeight() * 0.05);
    const auto compHeight = static_cast<int>(getParentComponent()->getHeight() * 0.066);

    page_buttons[1]->setBounds(getLocalBounds()
        .withSizeKeepingCentre(compWidth, compHeight).withY(compY));
    const auto bounds = page_buttons[1]->getBounds();
    page_buttons[0]->setBounds(bounds.withX(bounds.getX() - compWidth - padding));
    page_buttons[2]->setBounds(bounds.withX(bounds.getRight() + padding));

    for (const auto& editor : eq_editors)
    {
        editor->setBounds(getLocalBounds()
        .withSizeKeepingCentre(static_cast<int>(getWidth() * 0.95),
            static_cast<int>(getHeight() - page_buttons[0]->getBottom() - 5))
        .withY(page_buttons[0]->getBottom()));
    }
}

void ToneEditor::init_page_buttons()
{
    const juce::StringArray button_texts = {"Graphic", "Para", "Tube"};

    for (int i = 0; i < button_texts.size(); ++i)
    {
        page_buttons.emplace_back(std::make_unique<juce::TextButton>());
        page_buttons[i]->setButtonText(button_texts[i]);
        page_buttons[i]->setRadioGroupId(page_button_radio_id);
        page_buttons[i]->setClickingTogglesState(true);
        page_buttons[i]->setColour(juce::TextButton::ColourIds::buttonColourId,
            juce::Colours::black.withAlpha(0.25f));
        page_buttons[i]->setColour(juce::TextButton::ColourIds::buttonOnColourId,
            juce::Colour(161, 121, 83));
        page_buttons[i]->setColour(juce::ComboBox::ColourIds::outlineColourId,
            juce::Colour(120, 130, 140));
        page_buttons[i]->setLookAndFeel(&text_button_laf);
        addAndMakeVisible(*page_buttons[i]);

        // EDITOR SHOW/HIDE LOGIC
        page_buttons[i]->onClick = [this, i]()
        {
            close_editors();
            eq_editors[i]->setVisible(true);
        };

        page_buttons[0]->triggerClick();
    }
}

void ToneEditor::close_editors() const
{
    for (auto& editor : eq_editors)
    {
        editor->setVisible(false);
    }
}

void ToneEditor::init_editors()
{
    eq_editors.emplace_back(std::make_unique<viator::GraphicEQEditor>(audio_processor));
    eq_editors.emplace_back(std::make_unique<viator::ParaEQ>());
    eq_editors.emplace_back(std::make_unique<viator::PultecEQ>());

    for (const auto& module_editor : eq_editors)
    {
        addAndMakeVisible(*module_editor);
        module_editor->setVisible(false);
    }
}

}
