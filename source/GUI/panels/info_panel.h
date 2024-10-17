#pragma once
#ifndef info_panel_h
#define info_panel_h
#include "BinaryData.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "../look.h"

namespace viator
{

class InfoPanel : public juce::Component
{
 public:
    InfoPanel()
    {
        const auto shadow_color = viator::colors::monster_shadow_color;
        auto shadow = juce::DropShadow(shadow_color, 25, {});

        drop_shadow = std::make_unique<juce::DropShadower>(shadow);
        drop_shadow->setOwner(this);

        thanksTextEditor.setMultiLine(true);
        thanksTextEditor.setReadOnly(true);
        thanksTextEditor.setCaretVisible(false);
        thanksTextEditor.setText(
            "A special thanks to Michelangelo Nottoli and his great repository of SVG icons https://github.com/fefanto/fontaudio.");
        thanksTextEditor.setJustification(juce::Justification::centred);
        thanksTextEditor.setColour(juce::TextEditor::ColourIds::textColourId, viator::colors::monster_text_color);
        thanksTextEditor.setColour(juce::TextEditor::ColourIds::highlightedTextColourId,
                                   viator::colors::monster_translucent_black);
        thanksTextEditor.setColour(juce::TextEditor::ColourIds::highlightColourId, viator::colors::monster_text_color);
        thanksTextEditor.setColour(juce::TextEditor::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
        thanksTextEditor.setColour(juce::TextEditor::ColourIds::outlineColourId, juce::Colours::transparentBlack);
        thanksTextEditor.applyColourToAllText(viator::colors::monster_text_color);
        addAndMakeVisible(thanksTextEditor);

        set_button_props(patreon_button,
                         BinaryData::patreonsvgrepocom_svg,
                         BinaryData::patreonsvgrepocom_svgSize,
                         "Patreon",
                         juce::Colour(255, 66, 77),
                         viator::colors::monster_comp_outline,
                         viator::colors::monster_text_color);

        patreon_button->onClick = [this]()
        {
            juce::URL url("https://www.patreon.com/ViatorDSP");
            url.launchInDefaultBrowser();
        };

        set_button_props(gumroad_button,
                         BinaryData::gumroadsvgrepocom_svg,
                         BinaryData::gumroadsvgrepocom_svgSize,
                         "Gumroad",
                         juce::Colour(0, 0, 0),
                         viator::colors::monster_comp_outline,
                         viator::colors::monster_text_color);

        gumroad_button->onClick = [this]()
        {
            juce::URL url("https://viatordsp.gumroad.com/");
            url.launchInDefaultBrowser();
        };

        set_button_props(discord_button,
                         BinaryData::discordaltsvgrepocom_svg,
                         BinaryData::discordaltsvgrepocom_svgSize,
                         "Discord",
                         juce::Colour(0, 0, 0),
                         viator::colors::monster_comp_outline,
                         viator::colors::monster_text_color);

        discord_button->onClick = [this]()
        {
            juce::URL url("https://discord.gg/Rv5MEWgwwQ");
            url.launchInDefaultBrowser();
        };

        set_button_props(manual_button,
                         BinaryData::brochuresvgrepocom_svg,
                         BinaryData::brochuresvgrepocom_svgSize,
                         "Manual",
                         juce::Colour(0, 0, 0),
                         viator::colors::monster_comp_outline,
                         viator::colors::monster_text_color);

        manual_button->onClick = [this]()
        {
            juce::URL url("https://github.com/landonviator/Monster-Channel/blob/main/Monster%20Channel%20Manual.md");
            url.launchInDefaultBrowser();
        };

        set_button_props(support_button,
                         BinaryData::supportsvgrepocom_svg,
                         BinaryData::supportsvgrepocom_svgSize,
                         "Support",
                         juce::Colour(128, 129, 132),
                         viator::colors::monster_comp_outline,
                         viator::colors::monster_text_color);

        support_button->onClick = [this]()
        {
            juce::URL url("viatordsp@gmail.com");
            url.launchInDefaultBrowser();
        };

        set_button_props(license_button,
                         BinaryData::licensesvgrepocom_svg,
                         BinaryData::licensesvgrepocom_svgSize,
                         "License",
                         juce::Colour(0, 0, 0),
                         viator::colors::monster_comp_outline,
                         viator::colors::monster_text_color);

        license_button->onClick = [this]()
        {
            juce::URL url("https://github.com/landonviator/Monster-Channel/blob/main/Monster-Channel-EULA.md");
            url.launchInDefaultBrowser();
        };
    }

    void paint(juce::Graphics &g) override
    {
        // VARS
        g.fillAll(viator::colors::monster_info_bg);
        g.setFont(viator::Fonts::bold(static_cast<float>(getHeight()) * hero_text_size));
        auto bounds = getLocalBounds();

        // TITLE TEXT
        auto title_bounds = bounds.removeFromTop(getHeight() / 4);
        g.setColour(viator::colors::monster_text_color);
        g.drawFittedText("Monster Channel v1.0.0",
                         title_bounds,
                         juce::Justification::centred, 2);

        // THANKS TEXT
        g.setFont(viator::Fonts::regular(static_cast<float>(getHeight()) * paragraph_text_size));
        g.drawFittedText(
            "A sincere thanks to all who use my plugins and support my creative journey. \r\nYour enthusiasm "
            "and feedback inspires me to keep innovating and improving. \r\nTogether, we are making the world "
            "of audio more vibrant and accessible.",
            title_bounds.translated(0, getHeight() * 0.06),
            juce::Justification::centredBottom,
            3);

        // TEXT FOR EACH ICON
        auto icons_bounds = bounds.removeFromTop(getHeight() / 4);
        const auto button_width = static_cast<int>(static_cast<float>(bounds.getWidth()) / 15.0f);
        const auto space_leftover = getWidth() - button_width;
        const auto padding = static_cast<int>(static_cast<float>(space_leftover) / 7.0f);
        g.setFont(viator::Fonts::bold(static_cast<float>(getHeight()) * minor_text_size));
        g.drawFittedText("Support Me!",
                         icons_bounds.removeFromLeft(button_width)
                             .withSizeKeepingCentre(button_width, button_width)
                             .translated(padding, static_cast<int>(static_cast<float>(button_width) * 1.25f)),
                         juce::Justification::centredBottom, 1);

        icons_bounds.removeFromLeft(button_width);
        g.drawFittedText("Other Plugins!",
                         icons_bounds.removeFromLeft(button_width)
                             .withSizeKeepingCentre(button_width, button_width)
                             .translated(padding, static_cast<int>(static_cast<float>(button_width) * 1.25f)),
                         juce::Justification::centredBottom, 1);

        icons_bounds.removeFromLeft(button_width);
        g.drawFittedText("Join Discord!",
                         icons_bounds.removeFromLeft(button_width)
                             .withSizeKeepingCentre(button_width, button_width)
                             .translated(padding, static_cast<int>(static_cast<float>(button_width) * 1.25f)),
                         juce::Justification::centredBottom, 1);

        icons_bounds.removeFromLeft(button_width);
        g.drawFittedText("Manual!",
                         icons_bounds.removeFromLeft(button_width)
                             .withSizeKeepingCentre(button_width, button_width)
                             .translated(padding, static_cast<int>(static_cast<float>(button_width) * 1.25f)),
                         juce::Justification::centredBottom, 1);

        icons_bounds.removeFromLeft(button_width);
        g.drawFittedText("Get Support!",
                         icons_bounds.removeFromLeft(button_width)
                             .withSizeKeepingCentre(button_width, button_width)
                             .translated(padding, static_cast<int>(static_cast<float>(button_width) * 1.25f)),
                         juce::Justification::centredBottom, 1);

        icons_bounds.removeFromLeft(button_width);
        g.drawFittedText("EULA!",
                         icons_bounds.removeFromLeft(button_width)
                             .withSizeKeepingCentre(button_width, button_width)
                             .translated(padding, static_cast<int>(static_cast<float>(button_width) * 1.25f)),
                         juce::Justification::centredBottom, 1);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        const auto button_width = static_cast<int>(static_cast<float>(bounds.getWidth()) / 15.0f);
        const auto space_leftover = getWidth() - button_width;
        const auto padding = static_cast<int>(static_cast<float>(space_leftover) / 7.0f);

        if (patreon_button)
        {
            patreon_button->setBounds(bounds.removeFromLeft(button_width)
                                          .withSizeKeepingCentre(button_width, button_width)
                                          .translated(padding, 0.0f));
        }

        if (gumroad_button)
        {
            bounds.removeFromLeft(button_width);
            gumroad_button->setBounds(bounds.removeFromLeft(button_width)
                                          .withSizeKeepingCentre(button_width, button_width)
                                          .translated(padding, 0.0f));
        }

        if (discord_button)
        {
            bounds.removeFromLeft(button_width);
            discord_button->setBounds(bounds.removeFromLeft(button_width)
                                          .withSizeKeepingCentre(button_width,
                                                                 static_cast<int>(static_cast<float>(button_width)
                                                                     * 0.8f))
                                          .translated(padding, 0.0f));
        }

        if (manual_button)
        {
            bounds.removeFromLeft(button_width);
            manual_button->setBounds(bounds.removeFromLeft(button_width)
                                         .withSizeKeepingCentre(button_width, button_width)
                                         .translated(padding, 0.0f));
        }

        if (support_button)
        {
            bounds.removeFromLeft(button_width);
            support_button->setBounds(bounds.removeFromLeft(button_width)
                                          .withSizeKeepingCentre(button_width, button_width)
                                          .translated(padding, 0.0f));
        }

        if (license_button)
        {
            bounds.removeFromLeft(button_width);
            license_button->setBounds(bounds.removeFromLeft(button_width)
                                          .withSizeKeepingCentre(button_width, button_width)
                                          .translated(padding, 0.0f));
        }

        thanksTextEditor.setBounds(0, getHeight() * 0.9, getWidth(), getHeight() / 10);
        thanksTextEditor.applyFontToAllText(viator::Fonts::regular(static_cast<float>(getHeight()) * paragraph_text_size));
    }

 private:

    std::unique_ptr<juce::DropShadower> drop_shadow;

    static constexpr float hero_text_size { 0.05f };
    static constexpr float paragraph_text_size { 0.035f };
    static constexpr float minor_text_size { 0.02f };

    std::unique_ptr<juce::DrawableButton> patreon_button,
        gumroad_button, discord_button, manual_button, support_button, license_button;

    juce::TextEditor thanksTextEditor;

    void set_button_props(std::unique_ptr<juce::DrawableButton> &button,
                          const void *imageData,
                          int dataSize,
                          const juce::String &name,
                          juce::Colour originalColor,
                          juce::Colour newColorOff,
                          juce::Colour newColorOn)
    {
        button = std::make_unique<juce::DrawableButton>(name, juce::DrawableButton::ButtonStyle::ImageStretched);
        const std::unique_ptr<juce::Drawable> imageOff{
            juce::Drawable::createFromImageData(imageData, dataSize)};
        const std::unique_ptr<juce::Drawable> imageOn{
            juce::Drawable::createFromImageData(imageData, dataSize)};
        imageOff->replaceColour(originalColor, newColorOff);
        imageOn->replaceColour(originalColor, newColorOn);
        button->setImages(imageOff.get(), imageOn.get());

        addAndMakeVisible(button.get());
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoPanel)
};

}

#endif 
