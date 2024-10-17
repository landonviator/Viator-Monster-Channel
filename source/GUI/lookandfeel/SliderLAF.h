#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../look.h"

namespace viator
{
    class CustomDial final : public juce::LookAndFeel_V4
    {
        public:
        CustomDial();
        
        void drawRotarySlider
        (
         juce::Graphics &g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float rotaryStartAngle,
            float rotaryEndAngle,
         juce::Slider &slider
         ) override;
        
        void drawLabel (juce::Graphics& g, juce::Label& label) override;
        
        enum class ValueType
        {
            kInt,
            kFloat
        };
        
        [[nodiscard]] ValueType getDialValueType() const
        {
            return _dialValueType;
        }
        
        void setDialValueType(const ValueType newValueType)
        {
            _dialValueType = newValueType;
        }
        
    private:

        int _sliderWidth = 0;
        juce::String _sliderName = "";
        
        ValueType _dialValueType = ValueType::kFloat;

        juce::Colour muted_white = juce::Colour(120, 130, 140);
        const juce::Colour gold = juce::Colour(161, 121, 83);

        static float getRoundedValue(float input);
    };

    class ChickenHeadDial final : public juce::LookAndFeel_V4
    {
    public:
        ChickenHeadDial();

        void drawRotarySlider
        (
         juce::Graphics &g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float rotaryStartAngle,
            float rotaryEndAngle,
         juce::Slider &slider
         ) override;

        void drawLabel (juce::Graphics& g, juce::Label& label) override;

        enum class ValueType
        {
            kInt,
            kFloat
        };

        [[nodiscard]] ValueType getDialValueType() const
        {
            return _dialValueType;
        }

        void setDialValueType(const ValueType newValueType)
        {
            _dialValueType = newValueType;
        }

    private:

        int _sliderWidth = 0;
        juce::String _sliderName = "";

        ValueType _dialValueType = ValueType::kFloat;

        juce::Colour muted_white = juce::Colour(120, 130, 140);
        const juce::Colour gold = juce::Colour(161, 121, 83);

        static float getRoundedValue(float input);
    };

    class WaveyDial final : public juce::LookAndFeel_V4
    {
    public:
        WaveyDial();

        void drawRotarySlider
        (
         juce::Graphics &g,
            int x,
            int y,
            int width,
            int height,
            float sliderPos,
            float rotaryStartAngle,
            float rotaryEndAngle,
         juce::Slider &slider
         ) override;

        void drawLabel (juce::Graphics& g, juce::Label& label) override;

        enum class ValueType
        {
            kInt,
            kFloat
        };

        [[nodiscard]] ValueType getDialValueType() const
        {
            return _dialValueType;
        }

        void setDialValueType(const ValueType newValueType)
        {
            _dialValueType = newValueType;
        }

    private:

        int _sliderWidth = 0;
        juce::String _sliderName = "";

        ValueType _dialValueType = ValueType::kFloat;

        juce::Colour muted_white = juce::Colour(120, 130, 140);
        const juce::Colour gold = juce::Colour(161, 121, 83);

        static float getRoundedValue(float input);
    };

    class Fader final : public juce::LookAndFeel_V4
    {
    public:
        Fader();

        void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                               float sliderPos,
                                               float minSliderPos,
                                               float maxSliderPos,
                                               juce::Slider::SliderStyle style, juce::Slider& slider) override;

        void drawLabel (juce::Graphics& g, juce::Label& label) override;

        enum class ValueType
        {
            kInt,
            kFloat
        };

        [[nodiscard]] ValueType getDialValueType() const
        {
            return _dialValueType;
        }

        void setDialValueType(const ValueType newValueType)
        {
            _dialValueType = newValueType;
        }

    private:

        int _sliderWidth = 0;
        juce::String _sliderName = "";

        ValueType _dialValueType = ValueType::kFloat;

        juce::Colour muted_white = juce::Colour(120, 130, 140);
        const juce::Colour gold = juce::Colour(161, 121, 83);

        static float getRoundedValue(float input);
    };
}
