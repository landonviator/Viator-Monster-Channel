#pragma once
#include <juce_audio_utils/juce_audio_utils.h>

namespace ViatorParameters
{
    extern const juce::String outputID;
    extern const juce::String outputName;
    extern const juce::String inputID;
    extern const juce::String inputName;

    // PREAMP
    extern const juce::String preamp_driveID;
    extern const juce::String preamp_driveName;
    extern const juce::String preamp_mixID;
    extern const juce::String preamp_mixName;
    extern const juce::String preamp_outputID;
    extern const juce::String preamp_outputName;
    extern const juce::String preamp_toneID;
    extern const juce::String preamp_toneName;
    extern const juce::String preamp_low_cutID;
    extern const juce::String preamp_low_cutName;
    extern const juce::String preamp_high_cutID;
    extern const juce::String preamp_high_cutName;

    // COMPRESSORS
    extern const juce::String compOneInputID;
    extern const juce::String compOneInputName;
    extern const juce::String compOneAttackID;
    extern const juce::String compOneAttackName;
    extern const juce::String compOneHPFID;
    extern const juce::String compOneHPFName;
    extern const juce::String compOneReleaseID;
    extern const juce::String compOneReleaseName;
    extern const juce::String compOneThreshID;
    extern const juce::String compOneThreshName;
    extern const juce::String compOneRatioID;
    extern const juce::String compOneRatioName;
    extern const juce::String compOneMixID;
    extern const juce::String compOneMixName;
    extern const juce::String compOneOutputID;
    extern const juce::String compOneOutputName;
    extern const juce::String compOneTypeID;
    extern const juce::String compOneTypeName;
    extern const juce::String compOnePowerID;
    extern const juce::String compOnePowerName;

    extern const juce::String compTwoInputID;
    extern const juce::String compTwoInputName;
    extern const juce::String compTwoAttackID;
    extern const juce::String compTwoAttackName;
    extern const juce::String compTwoHPFID;
    extern const juce::String compTwoHPFName;
    extern const juce::String compTwoReleaseID;
    extern const juce::String compTwoReleaseName;
    extern const juce::String compTwoThreshID;
    extern const juce::String compTwoThreshName;
    extern const juce::String compTwoRatioID;
    extern const juce::String compTwoRatioName;
    extern const juce::String compTwoMixID;
    extern const juce::String compTwoMixName;
    extern const juce::String compTwoOutputID;
    extern const juce::String compTwoOutputName;
    extern const juce::String compTwoTypeID;
    extern const juce::String compTwoTypeName;
    extern const juce::String compTwoPowerID;
    extern const juce::String compTwoPowerName;

    // GRAPHIC EQ
    extern const juce::String graphicEQGainID;
    extern const juce::String graphicEQGainName;
    extern const juce::String graphicEQPowerID;
    extern const juce::String graphicEQPowerName;
    extern const std::vector<float> graphicEQCutoffs;

    extern const juce::String pluginPowerID;
    extern const juce::String pluginPowerName;

    struct parameters
    {
        explicit parameters(const juce::AudioProcessorValueTreeState& tree)
        {
            // PREAMP
            preampDriveParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::preamp_driveID));
            preampMixParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::preamp_mixID));
            preampOutputParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::preamp_outputID));
            preampLPParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::preamp_high_cutID));
            preampHPParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::preamp_low_cutID));
            preampToneParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::preamp_toneID));

            // COMPRESSORS
            compOneInputParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compOneInputID));

            compOneAttackParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compOneAttackID));

            compOneHPFParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compOneHPFID));

            compOneReleaseParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compOneReleaseID));

            compOneThreshParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compOneThreshID));

            compOneRatioParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compOneRatioID));

            compOneMixParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compOneMixID));

            compOneOutputParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compOneOutputID));

            compOneTypeParam = dynamic_cast<juce::AudioParameterBool*>(
                tree.getParameter(ViatorParameters::compOneTypeID));

            compOnePowerParam = dynamic_cast<juce::AudioParameterBool*>(
                tree.getParameter(ViatorParameters::compOnePowerID));

            compTwoInputParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compTwoInputID));

            compTwoAttackParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compTwoAttackID));

            compTwoHPFParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compTwoHPFID));

            compTwoReleaseParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compTwoReleaseID));

            compTwoThreshParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compTwoThreshID));

            compTwoRatioParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compTwoRatioID));

            compTwoMixParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compTwoMixID));

            compTwoOutputParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::compTwoOutputID));

            compTwoTypeParam = dynamic_cast<juce::AudioParameterBool*>(
                tree.getParameter(ViatorParameters::compTwoTypeID));

            compTwoPowerParam = dynamic_cast<juce::AudioParameterBool*>(
                tree.getParameter(ViatorParameters::compTwoPowerID));

            graphicGain0Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "0"));
            graphicGain1Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "1"));
            graphicGain2Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "2"));
            graphicGain3Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "3"));
            graphicGain4Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "4"));
            graphicGain5Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "5"));
            graphicGain6Param = dynamic_cast<juce::AudioParameterFloat*>(
             tree.getParameter(ViatorParameters::graphicEQGainID + "6"));
            graphicGain7Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "7"));
            graphicGain8Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "8"));
            graphicGain9Param = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::graphicEQGainID + "9"));
            graphicEQPowerParam = dynamic_cast<juce::AudioParameterBool*>(
                tree.getParameter(ViatorParameters::graphicEQPowerID));

            pluginPowerParam = dynamic_cast<juce::AudioParameterBool*>(
                tree.getParameter(ViatorParameters::pluginPowerID));

            inputParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::inputID));
            outputParam = dynamic_cast<juce::AudioParameterFloat*>(
                tree.getParameter(ViatorParameters::outputID));
        }

        juce::AudioParameterFloat* preampDriveParam { nullptr };
        juce::AudioParameterFloat* preampMixParam { nullptr };
        juce::AudioParameterFloat* preampOutputParam { nullptr };
        juce::AudioParameterFloat* preampLPParam { nullptr };
        juce::AudioParameterFloat* preampHPParam { nullptr };
        juce::AudioParameterFloat* preampToneParam { nullptr };

        juce::AudioParameterFloat* compOneInputParam { nullptr };
        juce::AudioParameterFloat* compOneAttackParam { nullptr };
        juce::AudioParameterFloat* compOneHPFParam { nullptr };
        juce::AudioParameterFloat* compOneReleaseParam { nullptr };
        juce::AudioParameterFloat* compOneThreshParam { nullptr };
        juce::AudioParameterFloat* compOneRatioParam { nullptr };
        juce::AudioParameterFloat* compOneMixParam { nullptr };
        juce::AudioParameterFloat* compOneOutputParam { nullptr };
        juce::AudioParameterBool* compOneTypeParam { nullptr };
        juce::AudioParameterBool* compOnePowerParam { nullptr };

        juce::AudioParameterFloat* compTwoInputParam { nullptr };
        juce::AudioParameterFloat* compTwoAttackParam { nullptr };
        juce::AudioParameterFloat* compTwoHPFParam { nullptr };
        juce::AudioParameterFloat* compTwoReleaseParam { nullptr };
        juce::AudioParameterFloat* compTwoThreshParam { nullptr };
        juce::AudioParameterFloat* compTwoRatioParam { nullptr };
        juce::AudioParameterFloat* compTwoMixParam { nullptr };
        juce::AudioParameterFloat* compTwoOutputParam { nullptr };
        juce::AudioParameterBool* compTwoTypeParam { nullptr };
        juce::AudioParameterBool* compTwoPowerParam { nullptr };

        juce::AudioParameterFloat* graphicGain0Param { nullptr };
        juce::AudioParameterFloat* graphicGain1Param { nullptr };
        juce::AudioParameterFloat* graphicGain2Param { nullptr };
        juce::AudioParameterFloat* graphicGain3Param { nullptr };
        juce::AudioParameterFloat* graphicGain4Param { nullptr };
        juce::AudioParameterFloat* graphicGain5Param { nullptr };
        juce::AudioParameterFloat* graphicGain6Param { nullptr };
        juce::AudioParameterFloat* graphicGain7Param { nullptr };
        juce::AudioParameterFloat* graphicGain8Param { nullptr };
        juce::AudioParameterFloat* graphicGain9Param { nullptr };
        juce::AudioParameterBool* graphicEQPowerParam { nullptr };

        juce::AudioParameterBool* pluginPowerParam { nullptr };

        juce::AudioParameterFloat* inputParam { nullptr };
        juce::AudioParameterFloat* outputParam { nullptr };
    };
}
