#include "Compressor.h"

namespace viator_core::dsp
{

template <typename SampleType>
void Compressor<SampleType>::reset()
{
    samplerate = viator_core::dsp::ModuleBase<SampleType>::getProcessSpec().sampleRate;
    
    hpFilter.prepare(viator_core::dsp::ModuleBase<SampleType>::getProcessSpec());
    hpFilter.setType(juce::dsp::LinkwitzRileyFilter<SampleType>::Type::highpass);
    hpFilter.setCutoffFrequency(hpCutoff);
}

template <typename SampleType>
void Compressor<SampleType>::setParameters(SampleType newThresh, SampleType newRatio, SampleType newAttack, SampleType newRelease, SampleType newKnee, SampleType hpf)
{
    threshold = newThresh;
    ratio = newRatio;
    
    if (compressorType == CompressorType::kVca)
    {
        attack = newAttack;
        release = newRelease;
    }

    else
    {
        attack = newAttack + 250.0;
        release = newRelease + 250.0;
    }
    
    knee = juce::jmap(static_cast<float>(newKnee), 0.0f, 6.0f, 6.0f, 0.0f);
    kneeScaled = juce::Decibels::gainToDecibels(knee);
    thresholdWithKnee = threshold - juce::Decibels::gainToDecibels(knee);
    hpCutoff = hpf;
    
    alphaAttack = std::exp(-std::log(9) / (samplerate * (attack / 1000.0f)));
    alphaRelease = std::exp(-std::log(9) / (samplerate * (release / 1000.0f)));
}

template <typename SampleType>
void Compressor<SampleType>::setCompressorType(CompressorType newCompressorType)
{
    compressorType = newCompressorType;
}

//==============================================================================
template class Compressor<float>;
template class Compressor<double>;

} // namespace
