#include "GRMeter.h"

namespace viator
{

GRMeter::GRMeter()
{
    // init shadow
    const auto shadow_color = juce::Colours::black;
    auto shadow = juce::DropShadow(shadow_color, 25, {});
    drop_shadow = std::make_unique<juce::DropShadower>(shadow);
    drop_shadow->setOwner(this);

    // init vector of gr guides
    for (int i = 0; i < 11; ++i)
    {
        grGuides.push_back(-i * 3);
    }
}

GRMeter::~GRMeter()
{
}

void GRMeter::paint (juce::Graphics& g)
{
    // style bg
    g.setColour(juce::Colour(120, 130, 140).withAlpha(0.1f));
    g.fillRoundedRectangle(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()), 6.0f);

    // draw guidelines
    g.setColour(muted_white);
    for (int i = 0; i < 11; ++i)
    {
        float x = getWidth() * (i / 10.0f);

        if (i != 0)
        {
            //g.drawLine(x, getHeight() * 0.11, x, getHeight(), 1.0f);
            g.setFont(juce::Font("Helvetica", getHeight() * 0.08, juce::Font::FontStyleFlags::plain));
            g.drawText(juce::String(grGuides[i]), x, 0, 40, 20, juce::Justification::left);
        }
    }

    // draw meter state
    g.setColour(gold);
    g.fillRect(0.0f, getHeight() * 0.25f, getWidth() * (smoothedGainReduction / -30.0f), getHeight() * 0.5f);
}

void GRMeter::resized()
{

}

void GRMeter::setGR(float newGR)
{
    auto reduction = juce::jlimit(-30.0f, 0.0f, newGR);
    smoothedGainReduction = (smoothingFactor * reduction) +
        ((1.0f - smoothingFactor) * smoothedGainReduction);
    repaint();
};

}
