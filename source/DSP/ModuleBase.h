#ifndef ModuleBase_h
#define ModuleBase_h

#include <juce_dsp/juce_dsp.h>

namespace viator_core::dsp
{

template <typename SampleType>
class ModuleBase
{
public:
    ModuleBase() = default;
    virtual ~ModuleBase() = default;

    void prepareModule (const juce::dsp::ProcessSpec& spec);
    
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock      = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples  = outputBlock.getNumSamples();

        jassert (inputBlock.getNumChannels() == numChannels);
        jassert (inputBlock.getNumSamples()  == numSamples);

        if (context.isBypassed)
        {
            outputBlock.copyFrom (inputBlock);
            return;
        }
        
        for (size_t sample = 0; sample < numSamples; ++sample)
        {
            for (size_t channel = 0; channel < numChannels; ++channel)
            {
                auto* input = inputBlock.getChannelPointer (channel);
                auto* output = outputBlock.getChannelPointer (channel);
                
                auto inputSignal = input[sample] * inputGain.getNextValue();
                auto wetSignal = processSample(inputSignal, channel);
                auto blend = (1.0 - mix.getNextValue()) * inputSignal + mix.getNextValue() * wetSignal * outputGain.getNextValue();
                output[sample] = blend;
            }
        }
    }
    
    virtual SampleType processSample(SampleType input, SampleType channel) = 0;
    
    void setInputGain(SampleType newGain);
    void setOutputGain(SampleType newGain);
    void setMix(SampleType newMix);
    
    float getSampleRate(){return sampleRate;};
    juce::dsp::ProcessSpec& getProcessSpec(){return _spec;};
    
    float getInputGain(){return inputGain.getNextValue();};
    float getOutputGain(){return outputGain.getNextValue();};
    float getMix(){return mix.getNextValue();};

private:
    float sampleRate = 44100.0f;
    juce::SmoothedValue<SampleType> inputGain = 1.0;
    juce::SmoothedValue<SampleType> outputGain = 1.0;
    juce::SmoothedValue<SampleType> mix = 0.0;
    
    juce::dsp::ProcessSpec _spec;
};

} // namespace

#endif /* ModuleBase_h */
