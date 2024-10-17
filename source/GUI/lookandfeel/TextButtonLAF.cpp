#include "TextButtonLAF.h"

namespace viator
{

void CustomTextButton::drawButtonBackground (juce::Graphics& g,
                                             juce::Button& button,
                                             const juce::Colour& backgroundColour,
                                             bool shouldDrawButtonAsHighlighted,
                                             bool shouldDrawButtonAsDown)
{
    constexpr auto cornerSize = 6.0f;
    const auto bounds = button.getLocalBounds().toFloat().reduced (3.0f, 3.0f);

    auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                      .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);

    g.setColour (baseColour);
    g.fillRoundedRectangle(bounds, cornerSize);

    const auto outlineColor = button.getToggleState() ? juce::Colour() : button.findColour (juce::ComboBox::outlineColourId);
    g.setColour (outlineColor);
    g.drawRoundedRectangle (bounds, cornerSize, 2.0f);
}

juce::Font CustomTextButton::getTextButtonFont (juce::TextButton& button, int buttonHeight)
{
    const float font_size = static_cast<float>(buttonHeight) * 0.4f;
    using font_style = juce::Font::FontStyleFlags;
    return juce::Font {"Arial", font_size, font_style::plain};
}

void CustomTextButton::drawButtonText (juce::Graphics& g, juce::TextButton& button,
                                       bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    const juce::Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);

    g.setColour (button.findColour (button.getToggleState() ? juce::TextButton::textColourOnId
                                    : juce::TextButton::textColourOffId)
                 .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    const auto bounds = button.getLocalBounds().reduced (3.0f, 3.0f);
    g.drawFittedText (button.getButtonText(), bounds, juce::Justification::centred, 1);
}



} // namespace
