#include "ModuleEditor.h"

namespace viator
{

ModuleEditor::ModuleEditor()
{
    // const auto shadow_color = juce::Colours::black.withAlpha(0.5f);
    // auto shadow = juce::DropShadow(shadow_color, 25, {});
    //
    // drop_shadow = std::make_unique<juce::DropShadower>(shadow);
    // drop_shadow->setOwner(this);
}

ModuleEditor::~ModuleEditor()
{

}

void ModuleEditor::paint (juce::Graphics& g)
{
    init_background(g);
}

void ModuleEditor::resized()
{

}

void ModuleEditor::init_background(juce::Graphics& g) const
{
    const auto width = static_cast<float>(getWidth());
    const auto height = static_cast<float>(getHeight());
    g.setColour(viator::colors::monster_translucent_black);
    g.fillRoundedRectangle(5, 5, width - 5, height - 5, 10.0f);

    g.setColour(viator::colors::monster_outline);
    g.drawRoundedRectangle(5, 5, width - 7, height - 7, 10.0f, 2.0f);
}

}
