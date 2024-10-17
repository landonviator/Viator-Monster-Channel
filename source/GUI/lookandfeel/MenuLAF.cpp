#include "MenuLAF.h"

namespace viator
{
    CustomMenu::CustomMenu()
    {
        
    }

    void CustomMenu::drawComboBox (juce::Graphics& g, int width, int height, bool,
                                       int, int, int, int, juce::ComboBox& box)
    {
        box.getLookAndFeel().setColour(juce::PopupMenu::ColourIds::backgroundColourId,
                                       juce::Colours::black.brighter(0.05f).withAlpha(0.9f));
        constexpr auto cornerSize = 3.0f;
        const juce::Rectangle<int> boxBounds (box.getLocalBounds().reduced(3.0f, 3.0f));

        g.setColour (juce::Colour());
        g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

        g.setColour (viator::colors::monster_comp_outline);
        g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 2.0f);

        const auto arrowWidth = height * 0.4;
        const juce::Rectangle<int> arrowZone (width - arrowWidth * 1.5, 0, arrowWidth, height);
        juce::Path path;
        path.startNewSubPath ((float) arrowZone.getX() + arrowZone.getWidth() * 0.1, (float) arrowZone.getCentreY() - arrowZone.getHeight() * 0.05);
        path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + arrowZone.getHeight() * 0.1);
        path.lineTo ((float) arrowZone.getRight() - arrowZone.getWidth() * 0.1, (float) arrowZone.getCentreY() - arrowZone.getHeight() * 0.05);
        
        g.strokePath (path, juce::PathStrokeType (1.0f));
    }

    void CustomMenu::positionComboBoxText (juce::ComboBox& box, juce::Label& label)
    {
        label.setInterceptsMouseClicks(false, false);
        label.setBounds (box.getLocalBounds());
        label.setJustificationType(_justification);

        const float font_size = static_cast<float>(box.getHeight()) * 0.5f;
        using font_style = juce::Font::FontStyleFlags;
        const auto font = viator::Fonts::regular(font_size);
        label.setFont (font);
    }

void CustomMenu::drawComboBoxTextWhenNothingSelected (juce::Graphics& g, juce::ComboBox& box, juce::Label& label)
{
    g.setColour(box.findColour(juce::ComboBox::textColourId));
    const float font_size = static_cast<float>(label.getHeight()) * 0.5f;
    using font_style = juce::Font::FontStyleFlags;
    const auto font = viator::Fonts::regular(font_size);

    g.setFont (font);

    const auto textArea = label.getLocalBounds().withX(10);

    g.drawFittedText (box.getTextWhenNothingSelected(), textArea, label.getJustificationType(),
                      juce::jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                      label.getMinimumHorizontalScale());
}

void CustomMenu::drawPopupMenuItem (juce::Graphics& g, const juce::Rectangle<int>& area,
                                        const bool isSeparator, const bool isActive,
                                        const bool isHighlighted, const bool isTicked,
                                        const bool hasSubMenu, const juce::String& text,
                                        const juce::String& shortcutKeyText,
                                        const juce::Drawable* icon, const juce::Colour* const textColourToUse)
{
    if (isSeparator)
    {
        auto r = area.reduced (5, 0);
        r.removeFromTop (r.getHeight() / 2 - 1);

        g.setColour (juce::Colour (0x33000000));
        g.fillRect (r.removeFromTop (1));

        g.setColour (juce::Colour (0x66ffffff));
        g.fillRect (r.removeFromTop (1));
    }
    else
    {
        auto textColour = findColour (juce::PopupMenu::textColourId);

        if (textColourToUse != nullptr)
            textColour = *textColourToUse;

        auto r = area;

        if (isHighlighted)
        {
            g.setColour (viator::colors::monster_comp_outline);
            g.fillRect (r);

            g.setColour (textColour);
        }
        else
        {
            g.setColour (textColour);
        }

        if (! isActive)
            g.setOpacity (0.3f);

        const float font_size = static_cast<float>(area.getHeight()) * 0.4f;
        const auto font = viator::Fonts::regular(font_size);

        g.setFont (font);

        if (hasSubMenu)
        {
            const auto arrowH = 0.6f * getPopupMenuFont().getAscent();

            const auto x = (float) r.removeFromRight ((int) arrowH).getX();
            const auto halfH = (float) r.getCentreY();

            juce::Path p;
            p.addTriangle (x, halfH - arrowH * 0.5f,
                           x, halfH + arrowH * 0.5f,
                           x + arrowH * 0.6f, halfH);

            g.fillPath (p);
        }

        r.removeFromRight (3);

        if (text == "User" || text == "Factory" || text == "Save" || text == "Load")
        {
            g.drawFittedText (text, r, juce::Justification::centred, 1);
        }

        else
        {
            g.drawFittedText (text, r.withX(static_cast<int>(area.getWidth() * 0.1)),
                              juce::Justification::centredLeft, 1);
        }

        if (shortcutKeyText.isNotEmpty())
        {
            juce::Font f2 (font);
            f2.setHeight (f2.getHeight() * 0.4f);
            f2.setHorizontalScale (0.95f);
            g.setFont (f2);

            g.drawText (shortcutKeyText, r, juce::Justification::centred, true);
        }
    }
}

void CustomMenu::getIdealPopupMenuItemSize (const juce::String& text, const bool isSeparator, int standardMenuItemHeight, int& idealWidth, int& idealHeight)
{
    if (isSeparator)
    {
        idealWidth = 50;
        idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight / 2 : 10;
    }

    else
    {
        juce::Font font (getPopupMenuFont());

        if (standardMenuItemHeight > 0 && font.getHeight() > (float) standardMenuItemHeight / 1.3f)
        font.setHeight ((float) standardMenuItemHeight / 1.3f);

        idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight : juce::roundToInt (font.getHeight() * 1.3f);
        idealWidth = idealHeight * 3;
    }
}

void CustomMenu::drawLabel (juce::Graphics& g, juce::Label& label)
{
    g.fillAll (label.findColour (juce::Label::backgroundColourId));

    if (! label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const juce::Font font (getLabelFont (label));

        g.setColour (label.findColour (juce::Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);

        auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

        g.drawFittedText (label.getText(), textArea, _justification,
                          juce::jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());

        g.setColour (label.findColour (juce::Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (juce::Label::outlineColourId));
    }

    g.drawRect (label.getLocalBounds());
}

    void CustomMenu::drawPopupMenuBackground (juce::Graphics& g, [[maybe_unused]] int width, [[maybe_unused]] int height)
    {
        g.fillAll (findColour (juce::PopupMenu::backgroundColourId));
    }

}
