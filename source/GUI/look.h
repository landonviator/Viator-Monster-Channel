#pragma once
#ifndef look_h
#define look_h
#include "BinaryData.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

namespace viator
{
    namespace colors
    {
        static const juce::Colour monster_translucent_black = juce::Colours::black.withAlpha ( 0.9f );
        static const juce::Colour monster_meter_green = juce::Colour ( 61, 125, 101 );
        static const juce::Colour monster_meter_yellow = juce::Colour ( 182, 160, 39 );
        static const juce::Colour monster_meter_red = juce::Colour ( 177, 66, 97 );
        static const juce::Colour monster_viewer_bg = juce::Colour ( 120, 130, 140 ).withAlpha( 0.1f );
        static const juce::Colour monster_viewer_path = juce::Colour ( 255, 255, 90 );
        static const juce::Colour monster_outline = juce::Colour ( 161, 121, 83 );
        static const juce::Colour monster_comp_outline = juce::Colour ( 120, 130, 140 );
        static const juce::Colour monster_text_color = juce::Colour ( 230, 232, 234 );
        static const juce::Colour monster_shadow_color = juce::Colours::black.withAlpha(0.5f);
        static const juce::Colour monster_info_bg = juce::Colour ( 30, 32, 39 ).withAlpha ( 0.8f );
    }

class Fonts final
{
 public:

    static juce::Font bold(float height = 12.0f, float kerning = 0.15f)
    {
        return fonts().f_bold.withHeight(height).withExtraKerningFactor(kerning);
    }

    static juce::Font regular(float height = 12.0f, float kerning = 0.15f)
    {
        return fonts().f_regular.withHeight(height).withExtraKerningFactor(kerning);
    }

 private:

    Fonts() = default;

    static Fonts& fonts()
    {
        static Fonts instance;
        return instance;
    }

    juce::Font f_bold{ juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::JetBrainsMonoBold_ttf, BinaryData::JetBrainsMonoBold_ttfSize)) };
    juce::Font f_regular{ juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::JetBrainsMonoRegular_ttf, BinaryData::JetBrainsMonoRegular_ttfSize)) };

    JUCE_DECLARE_NON_COPYABLE(Fonts)
};
}

#endif
