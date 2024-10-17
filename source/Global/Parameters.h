#pragma once
#include "Globals.h"

namespace viator
{
    namespace ParameterData
    {

        // Param data
        struct SliderParameterData
        {
            enum SkewType
            {
                kSkew,
                kNoSkew
            };

            enum NumericType
            {
                kInt,
                kFloat
            };

        public:
            juce::String paramID;
            juce::String paramName;
            float min;
            float max;
            float initial;
            SkewType isSkew;
            float center;
            NumericType isInt;
        };

        struct ButtonParameterData
        {
        public:
            juce::String paramID;
            juce::String paramName;
            bool initial;
        };

        struct MenuParameterData
        {
         public:
            juce::String paramID;
            juce::String name;
            int min;
            int max;
            int defaultIndex;
            juce::StringArray choices;
        };

        class Params
        {
        public:
            Params();

            // Get a ref to the param data
            std::vector<viator::ParameterData::SliderParameterData> &getSliderParams() { return _sliderParams; };
            std::vector<viator::ParameterData::ButtonParameterData> &getButtonParams() { return _buttonParams; };
            std::vector<viator::ParameterData::MenuParameterData>& getMenuParams(){return _menuParams;};

            std::vector<viator::ParameterData::SliderParameterData> _compOneSliderParams;
            std::vector<viator::ParameterData::SliderParameterData> _compTwoSliderParams;

        private:
            // Adds params to the vector
            void initSliderParams();
            void initButtonParams();

        private:
            // Vector holding param data
            std::vector<viator::ParameterData::SliderParameterData> _sliderParams;
            std::vector<viator::ParameterData::ButtonParameterData> _buttonParams;
            std::vector<viator::ParameterData::MenuParameterData> _menuParams;

        };
    }
}
