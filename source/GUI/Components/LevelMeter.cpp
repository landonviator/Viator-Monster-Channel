#include "LevelMeter.h"

namespace viator
{

void LevelMeter::paint (juce::Graphics& g)
{
    float dBValue = juce::Decibels::gainToDecibels(smoothedGainReduction, -60.0f);

    // Custom mapping of dB to normalized values
    float normalizeddBValue;
    if (dBValue < -18.0f)
        normalizeddBValue = juce::jmap(dBValue, -60.0f, -18.0f, 0.0f, 0.6f);
    else if (dBValue < -3.0f)
        normalizeddBValue = juce::jmap(dBValue, -18.0f, -3.0f, 0.6f, 0.85f);
    else
        normalizeddBValue = juce::jmap(dBValue, -3.0f, 0.0f, 0.85f, 1.0f);

    float fillHeight = static_cast<float>(getHeight()) * normalizeddBValue;

    // Define the height for each segment
    float greenHeight = static_cast<float>(getHeight()) * 0.6f;  // 60% for green (-60 dB to -18 dB)
    float yellowHeight = static_cast<float>(getHeight()) * 0.25f; // 25% for yellow (-18 dB to -3 dB)
    float redHeight = static_cast<float>(getHeight()) * 0.15f;    // 15% for red (-3 dB to 0 dB)

    float cornerRadius = 3.0f;

    g.setColour(viator::colors::monster_translucent_black);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 3.0f);

    // Draw the green segment with a rounded bottom
    g.setColour(viator::colors::monster_meter_green);
    juce::Path greenPath;
    if (fillHeight > greenHeight)
    {
        greenPath.addRoundedRectangle(0.0f, getHeight() - greenHeight, static_cast<float>(getWidth()), greenHeight, cornerRadius, cornerRadius, false, false, true, true);
        g.fillPath(greenPath);
    }
    else
    {
        greenPath.addRoundedRectangle(0.0f, getHeight() - fillHeight, static_cast<float>(getWidth()), fillHeight, cornerRadius, cornerRadius, false, false, true, true);
        g.fillPath(greenPath);
        return;
    }

    // Draw the yellow segment (from -18 dB to -3 dB) without rounding
    g.setColour(viator::colors::monster_meter_yellow);
    if (fillHeight > greenHeight + yellowHeight)
    {
        g.fillRect(0.0f, getHeight() - greenHeight - yellowHeight, static_cast<float>(getWidth()), yellowHeight);
    }
    else
    {
        g.fillRect(0.0f, getHeight() - fillHeight, static_cast<float>(getWidth()), fillHeight - greenHeight);
        return;
    }

    // Draw the red segment with a rounded top
    g.setColour(viator::colors::monster_meter_red);
    juce::Path redPath;
    redPath.addRoundedRectangle(0.0f, getHeight() - fillHeight, static_cast<float>(getWidth()), fillHeight - greenHeight - yellowHeight, cornerRadius, cornerRadius, true, true, false, false);
    g.fillPath(redPath);
}

void LevelMeter::setLevel(float newLevel)
{
    auto reduction = juce::jlimit(0.0f, 1.0f, newLevel);
    smoothedGainReduction = reduction;
    repaint();
};

}
