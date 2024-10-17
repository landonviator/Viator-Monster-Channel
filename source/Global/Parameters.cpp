#include "Parameters.h"

    namespace viator::ParameterData
    {

        Params::Params()
        {
            initSliderParams();
            initButtonParams();
        }

        void Params::initSliderParams()
        {
            using skew = SliderParameterData::SkewType;
            using type = SliderParameterData::NumericType;

            _sliderParams.push_back(
            {
                ViatorParameters::preamp_driveID,
                ViatorParameters::preamp_driveName,
                0.0f, 30.0f, 0.0f,
                skew::kNoSkew, 15.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::preamp_mixID,
                ViatorParameters::preamp_mixName,
                0.0f, 100.0f, 100.0f,
                skew::kNoSkew, 15.0, type::kInt
            });

            _sliderParams.push_back(
            {
                ViatorParameters::preamp_outputID,
                ViatorParameters::preamp_outputName,
                -20.0f, 20.0f, 0.0f,
                skew::kNoSkew, 0.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::preamp_toneID,
                ViatorParameters::preamp_toneID,
                -10.0f, 10.0f, 0.0f,
                skew::kNoSkew, 0.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::preamp_low_cutID,
                ViatorParameters::preamp_low_cutName,
                20.0f, 10000.0f, 20.0f,
                skew::kSkew, 1000.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::preamp_high_cutID,
                ViatorParameters::preamp_high_cutName,
                40.0f, 20000.0f, 20000.0f,
                skew::kSkew, 1000.0, type::kFloat
            });

            _sliderParams.push_back(
                {
                    ViatorParameters::inputID,
                    ViatorParameters::inputName,
                    -30.0f, 30.0f, 0.0f,
                    skew::kNoSkew, 0.0, type::kFloat
                });

            _sliderParams.push_back(
                {
                    ViatorParameters::outputID,
                    ViatorParameters::outputName,
                    -30.0f, 30.0f, 0.0f,
                    skew::kNoSkew, 0.0, type::kFloat
                });

#if !IS_LITE
            // COMPRESSORS
            _sliderParams.push_back(
            {
                ViatorParameters::compOneInputID,
                ViatorParameters::compOneInputName,
                -20.0f, 20.0f, 0.0f,
                skew::kNoSkew, 0.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compOneAttackID,
                ViatorParameters::compOneAttackName,
                5.0f, 1000.0f, 60.0f,
                skew::kSkew, 60.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compOneHPFID,
                ViatorParameters::compOneHPFName,
                20.0f, 1000.0f, 20.0f,
                skew::kSkew, 100.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compOneReleaseID,
                ViatorParameters::compOneReleaseName,
                10.0f, 2000.0f, 120.0f,
                skew::kSkew, 120.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compOneThreshID,
                ViatorParameters::compOneThreshName,
                -60.0f, 0.0f, 0.0f,
                skew::kNoSkew, -30.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compOneRatioID,
                ViatorParameters::compOneRatioName,
                1.0f, 20.0f, 2.0f,
                skew::kNoSkew, 10.0, type::kInt
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compOneMixID,
                ViatorParameters::compOneMixName,
                0.0f, 100.0f, 100.0f,
                skew::kNoSkew, 50.0, type::kInt
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compOneOutputID,
                ViatorParameters::compOneOutputName,
                -20.0f, 20.0f, 0.0f,
                skew::kNoSkew, 0.0, type::kFloat
            });

            _compOneSliderParams.push_back(
                {
                    ViatorParameters::compOneInputID,
                    ViatorParameters::compOneInputName,
                    -20.0f, 20.0f, 0.0f,
                    skew::kNoSkew, 0.0, type::kFloat
                });

            _compOneSliderParams.push_back(
                {
                    ViatorParameters::compOneAttackID,
                    ViatorParameters::compOneAttackName,
                    5.0f, 1000.0f, 60.0f,
                    skew::kSkew, 60.0, type::kFloat
                });

            _compOneSliderParams.push_back(
                {
                    ViatorParameters::compOneHPFID,
                    ViatorParameters::compOneHPFName,
                    20.0f, 1000.0f, 20.0f,
                    skew::kSkew, 100.0, type::kFloat
                });

            _compOneSliderParams.push_back(
                {
                    ViatorParameters::compOneReleaseID,
                    ViatorParameters::compOneReleaseName,
                    10.0f, 2000.0f, 120.0f,
                    skew::kSkew, 120.0, type::kFloat
                });

            _compOneSliderParams.push_back(
                {
                    ViatorParameters::compOneThreshID,
                    ViatorParameters::compOneThreshName,
                    -60.0f, 0.0f, 0.0f,
                    skew::kNoSkew, -30.0, type::kFloat
                });

            _compOneSliderParams.push_back(
                {
                    ViatorParameters::compOneRatioID,
                    ViatorParameters::compOneRatioName,
                    1.0f, 20.0f, 2.0f,
                    skew::kNoSkew, 10.0, type::kInt
                });

            _compOneSliderParams.push_back(
                {
                    ViatorParameters::compOneMixID,
                    ViatorParameters::compOneMixName,
                    0.0f, 100.0f, 100.0f,
                    skew::kNoSkew, 50.0, type::kInt
                });

            _compOneSliderParams.push_back(
                {
                    ViatorParameters::compOneOutputID,
                    ViatorParameters::compOneOutputName,
                    -20.0f, 20.0f, 0.0f,
                    skew::kNoSkew, 0.0, type::kFloat
                });

            _sliderParams.push_back(
            {
                ViatorParameters::compTwoInputID,
                ViatorParameters::compTwoInputName,
                -20.0f, 20.0f, 0.0f,
                skew::kNoSkew, 0.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compTwoAttackID,
                ViatorParameters::compTwoAttackName,
                5.0f, 1000.0f, 60.0f,
                skew::kSkew, 60.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compTwoHPFID,
                ViatorParameters::compTwoHPFName,
                20.0f, 1000.0f, 20.0f,
                skew::kSkew, 100.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compTwoReleaseID,
                ViatorParameters::compTwoReleaseName,
                10.0f, 2000.0f, 120.0f,
                skew::kSkew, 120.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compTwoThreshID,
                ViatorParameters::compTwoThreshName,
                -60.0f, 0.0f, 0.0f,
                skew::kNoSkew, -30.0, type::kFloat
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compTwoRatioID,
                ViatorParameters::compTwoRatioName,
                1.0f, 20.0f, 2.0f,
                skew::kNoSkew, 10.0, type::kInt
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compTwoMixID,
                ViatorParameters::compTwoMixName,
                0.0f, 100.0f, 100.0f,
                skew::kNoSkew, 50.0, type::kInt
            });

            _sliderParams.push_back(
            {
                ViatorParameters::compTwoOutputID,
                ViatorParameters::compTwoOutputName,
                -20.0f, 20.0f, 0.0f,
                skew::kNoSkew, 0.0, type::kFloat
            });

            _compTwoSliderParams.push_back(
                {
                    ViatorParameters::compTwoInputID,
                    ViatorParameters::compTwoInputName,
                    -20.0f, 20.0f, 0.0f,
                    skew::kNoSkew, 0.0, type::kFloat
                });

            _compTwoSliderParams.push_back(
                {
                    ViatorParameters::compTwoAttackID,
                    ViatorParameters::compTwoAttackName,
                    5.0f, 1000.0f, 60.0f,
                    skew::kSkew, 60.0, type::kFloat
                });

            _compTwoSliderParams.push_back(
                {
                    ViatorParameters::compTwoHPFID,
                    ViatorParameters::compTwoHPFName,
                    20.0f, 1000.0f, 20.0f,
                    skew::kSkew, 100.0, type::kFloat
                });

            _compTwoSliderParams.push_back(
                {
                    ViatorParameters::compTwoReleaseID,
                    ViatorParameters::compTwoReleaseName,
                    10.0f, 2000.0f, 120.0f,
                    skew::kSkew, 120.0, type::kFloat
                });

            _compTwoSliderParams.push_back(
                {
                    ViatorParameters::compTwoThreshID,
                    ViatorParameters::compTwoThreshName,
                    -60.0f, 0.0f, 0.0f,
                    skew::kNoSkew, -30.0, type::kFloat
                });

            _compTwoSliderParams.push_back(
                {
                    ViatorParameters::compTwoRatioID,
                    ViatorParameters::compTwoRatioName,
                    1.0f, 20.0f, 2.0f,
                    skew::kNoSkew, 10.0, type::kInt
                });

            _compTwoSliderParams.push_back(
                {
                    ViatorParameters::compTwoMixID,
                    ViatorParameters::compTwoMixName,
                    0.0f, 100.0f, 100.0f,
                    skew::kNoSkew, 50.0, type::kInt
                });

            _compTwoSliderParams.push_back(
                {
                    ViatorParameters::compTwoOutputID,
                    ViatorParameters::compTwoOutputName,
                    -20.0f, 20.0f, 0.0f,
                    skew::kNoSkew, 0.0, type::kFloat
                });

            // GRAPHIC EQ
            for (int i = 0; i < 10; ++i) {
                _sliderParams.push_back (
                {
                    ViatorParameters::graphicEQGainID + juce::String(i),
                    ViatorParameters::graphicEQGainName + " " + juce::String(i),
                    -15.0f, 15.0f, 0.0f,
                    skew::kNoSkew, 0.0f, type::kFloat
                });
            }

#endif
        }

        void Params::initButtonParams()
        {
            _buttonParams.push_back(
            {
                ViatorParameters::pluginPowerID,
                ViatorParameters::pluginPowerName,
                true
            });

#if !IS_LITE

            _buttonParams.push_back(
            {
                ViatorParameters::compOneTypeID,
                ViatorParameters::compOneTypeName,
                false
            });

            _buttonParams.push_back(
            {
                ViatorParameters::compOnePowerID,
                ViatorParameters::compOnePowerName,
                false
            });

            _buttonParams.push_back(
            {
                ViatorParameters::compTwoTypeID,
                ViatorParameters::compTwoTypeName,
                false
            });

            _buttonParams.push_back(
            {
                ViatorParameters::compTwoPowerID,
                ViatorParameters::compTwoPowerName,
                false
            });

            _buttonParams.push_back(
            {
                ViatorParameters::graphicEQPowerID,
                ViatorParameters::graphicEQPowerName,
                true
            });

#endif
        }
    }

