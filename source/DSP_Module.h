/*
  ==============================================================================

    DSP_Module.h
    Created: 7 Apr 2024 7:04:00pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <juce_dsp/juce_dsp.h>
#include "DSP/Waveshaper.h"
#include "Global/Parameters.h"

class DSP_Module
{
public:
    
    void prepare(const double samplerate, const juce::uint32 blockSize, const juce::uint32 numChannels, const int factor)
    {
        juce::dsp::ProcessSpec spec {};
        spec.numChannels = numChannels;
        spec.maximumBlockSize = blockSize;
        
        _oversampler = std::make_unique<juce::dsp::Oversampling<float>>(spec.numChannels, factor, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, true, false);
        _oversampler->initProcessing(spec.maximumBlockSize);
        
        spec.sampleRate = samplerate * static_cast<float>(_oversampler->getOversamplingFactor());
        spec.maximumBlockSize = blockSize * static_cast<int>(_oversampler->getOversamplingFactor());
        
        waveshaper.prepare(spec);

        spec.sampleRate = samplerate;
        spec.maximumBlockSize = blockSize;

        tone_filter.prepare(
            static_cast<float>(spec.sampleRate),
            static_cast<int>(spec.numChannels));
        lp_filter.prepare(spec);
        lp_filter.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);

        hp_filter.prepare(spec);
        hp_filter.setType(juce::dsp::LinkwitzRileyFilterType::highpass);

        tone_filter.setParameter(
            viator::SVFilter<float>::ParameterId::kType,
            viator::SVFilter<float>::FilterType::kHighShelf);
        tone_filter.setParameter(
            viator::SVFilter<float>::ParameterId::kQType,
            viator::SVFilter<float>::QType::kProportional);
    }
    
    void process(juce::AudioBuffer<float>& buffer)
    {
        juce::dsp::AudioBlock<float> block {buffer};
        juce::dsp::AudioBlock<float> upSampledBlock {buffer};

        lp_filter.process(juce::dsp::ProcessContextReplacing<float>(block));
        hp_filter.process(juce::dsp::ProcessContextReplacing<float>(block));

        upSampledBlock = _oversampler->processSamplesUp(block);
        waveshaper.process(upSampledBlock);
        _oversampler->processSamplesDown(block);

        tone_filter.process(block);
    }
    
    void set_parameters(const ViatorParameters::parameters& parameters)
    {
        // PREAMP
        const auto drive = parameters.preampDriveParam->get();
        const auto mix = parameters.preampMixParam->get();
        const auto output = parameters.preampOutputParam->get();
        waveshaper.set_drive(drive);
        waveshaper.set_mix(mix);
        waveshaper.set_output(output);

        const auto lp = parameters.preampLPParam->get();
        const auto hp = parameters.preampHPParam->get();
        lp_filter.setCutoffFrequency(lp);
        hp_filter.setCutoffFrequency(hp);

        const auto tone = parameters.preampToneParam->get();
        tone_filter.set_parameters(1000.0f, 0.9f, tone);
    }

private:
    std::unique_ptr<juce::dsp::Oversampling<float>> _oversampler;
    viator::Waveshaper waveshaper;
    juce::dsp::LinkwitzRileyFilter<float> lp_filter;
    juce::dsp::LinkwitzRileyFilter<float> hp_filter;
    viator::SVFilter<float> tone_filter;
};
