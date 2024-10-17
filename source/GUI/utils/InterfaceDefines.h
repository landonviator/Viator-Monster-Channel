#pragma once

#include <juce_graphics/juce_graphics.h>
//#include "../../JuceLibraryCode/JucePluginDefines.h"

#define USE_LIVE_CONSTANT false

#if USE_LIVE_CONSTANT
#define colorHelper(c) JUCE_LIVE_CONSTANT(c);
#else
#define colorHelper(c) c;
#endif

#define VERSION             JucePlugin_VersionString
#define CTRLMODE            "Control Mode"

#define GITHUB_LINK         "https://mywebsite.com"
#define GITHUB_TAG_LINK     "https://mywebsite.com"
#define PRESET_EXETENSION   ".xml"

// Define Font
#define KNOB_FONT           "Futura"
#define KNOB_FONT_SIZE      15.0f
#define POPUP_FONT          "Futura"
#define POPUP_FONT_SIZE     18.0f
#define POPUP_FONT_SOZE     14.0f
#define KNOB_FONT_COLOUR    COLOUR1
#define KNOB_SUBFONT_COLOUR COLOUR7.withBrightness(0.8f)
#define KNOB_INNER_COLOUR   COLOUR7.withBrightness(slider.isEnabled() ? 0.8f : 0.5f)
#define KNOB_TICK_COLOUR    COLOUR7

// Define Components size
#define TEXTBOX_WIDTH       60
#define TEXTBOX_HEIGHT      30
#define KNOBSIZE            100
#define SCALED_KNOBSIZE     static_cast<int>(knobSize * scale)

// Define Position
#define INIT_WIDTH          1024.0f
#define INIT_HEIGHT         600.0f
#define MAIN_PANEL_WIDTH    1024.0f
#define MAIN_PANEL_HEIGHT   600.0f

#define KNOB_PANEL_1_X      SWITCH_X + SWITCH_WIDTH
#define KNOB_PANEL_2_X      SWITCH_X + SWITCH_WIDTH + KNOB_PANEL_1_WIDTH
#define KNOB_PANEL_3_X      SWITCH_X + SWITCH_WIDTH + KNOB_PANEL_1_WIDTH + OSC_HEIGHT * 2 + BUTTON_WIDTH

#define KNOB_PANEL_1_WIDTH  getWidth() / 4.0f
#define KNOB_PANEL_2_WIDTH  OSC_HEIGHT * 2

#define OSC_X               getWidth() / 10.0f - OSC_WIDTH / 2.0f
#define OSC_Y               PART1 + PART2 + getHeight() / 5.0f
#define OSC_WIDTH           getWidth() / 8.0f
#define OSC_HEIGHT          (getHeight() - PART1 - PART2) / 4.0f

#define METER_X             getWidth() / 10.0f * 2.0f
#define METER_Y             PART1 + PART2 + getHeight() / 5.0f
#define METER_WIDTH         getWidth() / 8.0f
#define METER_HEIGHT        (getHeight() - PART1 - PART2) / 4.0f

#define D_GRAPH_X           getWidth() / 10.0f - D_GRAPH_WIDTH / 2.0f
#define D_GRAPH_Y           PART1 + PART2 + getHeight() / 10.0f + (getHeight() - PART1 - PART2) / 2.0f
#define D_GRAPH_WIDTH       getWidth() / 8.0f
#define D_GRAPH_HEIGHT      (getHeight() - PART1 - PART2) / 4.0f

#define WIDTH_GRAPH_X       getWidth() / 20.0f + getWidth() / 8.0f
#define WIDTH_GRAPH_Y       PART1 + PART2 + getHeight() / 10.0f + (getHeight() - PART1 - PART2) / 2.0f
#define WIDTH_GRAPH_WIDTH   getWidth() / 8.0f
#define WIDTH_GRAPH_HEIGHT  (getHeight() - PART1 - PART2) / 4.0f

#define SPEC_HEIGHT         getHeight() / 10.0f * 3.0f

//FFT
#define SPEC_HEIGHT_FFT     getHeight() / 10.0f * 5.0f
#define SPEC_HEIGHT_FILTER  getHeight() / 10.0f * 2.5f

#define SPEC_HEITER_FILTER  getHeight() / 25.0f * 25.0f

#define DRIVE_X             KNOB_PANEL_2_X + OSC_HEIGHT - SCALED_KNOBSIZE / 2.0f
#define DRIVE_Y             OSC_Y + OSC_HEIGHT / 2.0f
#define DRIVE_SIZE          SCALED_KNOBSIZE * 2.0f

#define REC_X               KNOB_PANEL_1_X + SCALED_KNOBSIZE / 4.0f
#define BIAS_X              KNOB_PANEL_1_X + SCALED_KNOBSIZE + SCALED_KNOBSIZE / 4.0f
#define WIDTH_X             KNOB_PANEL_1_X + OSC_WIDTH - SCALED_KNOBSIZE / 2.0f

#define COMP_THRESH_X       KNOB_PANEL_1_X + SCALED_KNOBSIZE / 4.0f
#define COMP_RATIO_X        KNOB_PANEL_1_X + SCALED_KNOBSIZE + SCALED_KNOBSIZE / 4.0f
#define OUTPUT_X            KNOB_PANEL_3_X + SCALED_KNOBSIZE / 4.0f
#define MIX_X               KNOB_PANEL_3_X + SCALED_KNOBSIZE + SCALED_KNOBSIZE / 4.0f

#define CUTOFF_X            startX * 4.5f - SCALED_KNOBSIZE / 2.0f
#define RES_X               startX * 6.0f - SCALED_KNOBSIZE / 2.0f
#define DOWNSAMPLE_X        startX * 7.5f - SCALED_KNOBSIZE / 2.0f

#define FILTER_STATE_X      startX * 4.5f - SCALED_KNOBSIZE / 4.0f
#define FILTER_TYPE_X       startX * 6.0f - SCALED_KNOBSIZE / 4.0f
#define OUTPUT_X_G          startX * 9.0f - SCALED_KNOBSIZE / 2.0f
#define MIX_X_G             startX * 9.0f - SCALED_KNOBSIZE / 2.0f

#define VU_METER_WIDTH      getWidth() / 10.0f
#define VU_METER_HEIGHT     getHeight() / 10.0f * 9.0f
#define VU_METER_Y          getHeight() / 10.0f
#define VU_METER_X_1        getWidth() / 3.0f - VU_METER_WIDTH / 2.0f
#define VU_METER_X_2        getWidth() / 3.0f * 2.0f - VU_METER_WIDTH / 2.0f


// Switches
#define SWITCH_WIDTH        OSC_WIDTH / 10.0f
#define SWITCH_HEIGHT       OSC_HEIGHT / 2.0f
#define SWITCH_X            OSC_X + OSC_WIDTH * 2.0f

#define SWITCH_OSC_Y        OSC8
#define SWITCH_SHAPE_Y      OSC_Y + OSC_HEIGHT / 2.0f
#define SWITCH_COMP_Y       OSC_Y + OSC_HEIGHT
#define SWITCH_WIDTH_Y      OSC_Y + OSC_HEIGHT / 2.0f * 3.0f

// Buttons
#define BUTTON_X            SWITCH_X + SWITCH_WIDTH + KNOB_PANEL_1_WIDTH + OSC_HEIGHT * 2
#define BUTTON_WIDTH        OSC_WIDTH / 4.0f

// Define Color
#define COLOUR0             juce::Colour(244, 244, 210) // white
#define COLOUR1             juce::Colour(204, 204, 204)//Panel Fonts
#define COLOUR2             juce::Colour(243, 156, 18)//Orange
#define COLOUR3             juce::Colour(230, 126, 34)
#define COLOUR4             juce::Colour(0, 51, 102)
#define COLOUR5             juce::Colour(51, 102, 153)//Panel of Panel
#define COLOUR6             juce::Colour(40, 40, 40)
#define COLOUR7             juce::Colour(15, 15, 15)
#define COLOUR8             juce::Colour(10, 10, 10)
#define COLOUR9             juce::Colours::red
#define COLOUR10            juce::Colours::black
#define COLOUR11            juce::Colours::yellow
#define COLOUR12            juce::Colours::darkgrey
#define COLOUR13            juce::Colours::violet
#define COLOUR14            juce::Colours::green
#define COLOUR15            juce::Colour(211, 211, 211)//Light grey
#define COLOUR16            juce::Colour(127, 127, 127) //Mid grey
#define COLOUR17            juce::Colour(63, 63, 63) //Dark grey
#define COLOUR18            juce::Colours::orangered
#define DSKNOB              juce::Colours::skyblue
#define COLOUR_FONT         juce::Colour(100, 100, 100)
#define COLOUR_MASK_RED     juce::Colours::red.withAlpha(0.05f)
#define COLOUR_MASK_BLACK   juce::Colours::black.withAlpha(0.5f)
#define COLOUR_MASK_WHITE   juce::Colours::white.withAlpha(0.05f)
#define COLOUR_GROUP        juce::Colour(50, 50, 50)
#define DRIVE_COLOUR        juce::Colours::darkred
#define SHAPE_COLOUR        juce::Colours::yellow
#define WIDTH_COLOUR        juce::Colours::skyblue
#define COMP_COLOUR         juce::Colours::yellowgreen
#define FILTER_COLOUR       juce::Colours::hotpink
#define DOWNSAMPLE_COLOUR   juce::Colours::violet
#define LIMITER_COLOUR      juce::Colours::mediumpurple

// VU meters
#define SMOOTH_COEFF        0.2
