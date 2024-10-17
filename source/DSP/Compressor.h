#ifndef Compressor_h
#define Compressor_h

#include "ModuleBase.h"

namespace viator_core
{
namespace dsp
{

template <typename SampleType>
class Compressor : public ModuleBase<SampleType>
{
public:
    Compressor(){};
    ~Compressor(){};

    void reset();
    
    SampleType processSample(SampleType input, SampleType channel) override
    {
        hpFilter.setCutoffFrequency(hpCutoff);
        
        auto xUni = abs(input);

        auto hpSignal = hpFilter.processSample(channel, xUni);
        auto filteredXDB = juce::Decibels::gainToDecibels(std::abs(hpSignal));
        
        if (filteredXDB > threshold)
        {
            gainChangeDB = (threshold - filteredXDB) + ((filteredXDB - threshold) / ratio);
        }

        if (gainChangeDB < gainSmoothPrevious)
        {
            gainSmooth = alphaAttack * (gainSmoothPrevious - gainChangeDB) + gainChangeDB;
            currentSignal = gainSmooth;
        }
        
        else
        {
            gainSmooth = alphaRelease * (gainSmoothPrevious - gainChangeDB) + gainChangeDB;
            currentSignal = gainSmooth;
        }

        gainSmoothPrevious = gainSmooth;

        return input * juce::Decibels::decibelsToGain(gainSmooth);
    }

    
    enum class CompressorType
    {
        kVca,
        kOpto
    };
    
    void setParameters(SampleType newThresh, SampleType newRatio, SampleType newAttack, SampleType newRelease, SampleType newKnee, SampleType hpf);
    void setCompressorType(CompressorType newCompressorType);
    
    SampleType getGainReduction(){return currentSignal;};
    
private:
    float samplerate = 44100.0f;
    float threshold = 0.0f;
    float ratio = 2.0f;
    float attack = 5.0f;
    float release = 5.0f;
    float knee = 0.0f;
    float kneeScaled = 0.0f;
    float thresholdWithKnee = 0.0f;
    
    float alphaAttack = 0.0f;
    float alphaRelease = 0.0f;
    
    float gainSmoothPrevious = 0.0f;
    float gainChangeDB = 0.0f;
    
    float gainChange, gainSmooth, currentSignal;
    
    juce::dsp::LinkwitzRileyFilter<SampleType> hpFilter;
    float hpCutoff = 20.0f;
    
    CompressorType compressorType = CompressorType::kVca;
};

}} // namespace 

#endif /* Compressor_h */
