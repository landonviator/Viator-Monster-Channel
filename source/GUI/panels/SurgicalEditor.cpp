#include "SurgicalEditor.h"

namespace viator
{

SurgicalEditor::SurgicalEditor()
{
}

SurgicalEditor::~SurgicalEditor()
{
}

void SurgicalEditor::paint (juce::Graphics& g)
{
    viator::ModuleEditor::paint(g);

    g.setColour(juce::Colours::black);
    g.setFont(juce::Font("Helvetica", 18.0f, juce::Font::FontStyleFlags::bold));
    g.drawFittedText("Surgical", getLocalBounds(), juce::Justification::centred, 1);
}

void SurgicalEditor::resized()
{
}

}
