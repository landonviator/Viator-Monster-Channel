#include "Waveshaper.h"

namespace viator
{

void Waveshaper::prepare (const juce::dsp::ProcessSpec& spec)
{
    jassert (spec.sampleRate > 0);
    jassert (spec.numChannels > 0);
    
    sampleRate = spec.sampleRate;

    drive_param.reset(sampleRate, 0.01);
    drive_compensate_param.reset(sampleRate, 0.01);
    raw_drive_param.reset(sampleRate, 0.01);
    mix_param.reset(sampleRate, 0.01);
    output_param.reset(sampleRate, 0.01);

    negative_dc_filter.prepare(spec);
    negative_dc_filter.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    negative_dc_filter.setCutoffFrequency(20.0);
    positive_dc_filter.prepare(spec);
    positive_dc_filter.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
    positive_dc_filter.setCutoffFrequency(20.0);
}

void Waveshaper::reset()
{
    negative_dc_filter.reset();
    positive_dc_filter.reset();
}

void Waveshaper::process (juce::dsp::AudioBlock<float>& block)
{
    processBlock(block);
}

void Waveshaper::set_drive(const float newDrive)
{
    drive_param.setTargetValue(juce::Decibels::decibelsToGain(newDrive));
    drive_compensate_param.setTargetValue(juce::Decibels::decibelsToGain(-newDrive * 0.5f));

    auto drive_scaled = juce::jlimit(0.0f, 5.0f, newDrive);
    raw_drive_param.setTargetValue(juce::jmap(drive_scaled, 0.0f, 5.0f, 0.0f, 1.0f));
}

void Waveshaper::set_mix (const float newMix)
{
    mix_param.setTargetValue(newMix * 0.01f);
}

void Waveshaper::set_output (const float newOutput)
{
    output_param.setTargetValue(juce::Decibels::decibelsToGain(newOutput));
}

} // namespace viator_dsp
