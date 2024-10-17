#include "ConsoleEditor.h"

namespace viator
{

ConsoleEditor::ConsoleEditor()
{
}

ConsoleEditor::~ConsoleEditor()
{
}

void ConsoleEditor::paint (juce::Graphics& g)
{
    viator::ModuleEditor::paint(g);

    g.setColour(juce::Colours::black);
    g.setFont(juce::Font("Helvetica", 18.0f, juce::Font::FontStyleFlags::bold));
    g.drawFittedText("Console", getLocalBounds(), juce::Justification::centred, 1);
}

void ConsoleEditor::resized()
{
}

}
