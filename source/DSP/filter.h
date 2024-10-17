#ifndef filter_h
#define filter_h

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

namespace viator
{
template <typename SampleType>
class SVFilter
{
public:
    
    SVFilter();
    
    void prepare(float sample_rate, int num_channels);

    void process_buffer(std::vector<float*>& buffer, int num_channels, int samples_per_channel)
    {
        for (int channel = 0; channel < num_channels; channel++)
        {
            for (int sample = 0; sample < samples_per_channel; sample++)
            {
                float input = buffer[channel][sample];
                buffer[channel][sample] = process_sample(input, channel);
            }
        }
    }

    void processBuffer(juce::AudioBuffer<float>& buffer)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            auto* data = buffer.getWritePointer(channel);

            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                data[sample] = process_sample(data[sample], channel);
            }
        }
    }

    void process (juce::dsp::AudioBlock<float>& block)
    {
        for (int channel = 0; channel < block.getNumChannels(); ++channel)
        {
            auto* data = block.getChannelPointer(channel);

            for (int sample = 0; sample < block.getNumSamples(); ++sample)
            {
                data[sample] = process_sample(data[sample], channel);
            }
        }
    }
    
    SampleType process_sample(SampleType input, int ch) noexcept
    {
        const auto z1 = mZ1[ch];
        const auto z2 = mZ2[ch];
        
        const float x = input;

        const double HP = (x - mRCoeff2 * z1 - mGCoeff * z1 - z2) * mInversion;
        const double BP = HP * mGCoeff + z1;
        const double LP = BP * mGCoeff + z2;
        const double UBP = mRCoeff2 * BP;
        const double BShelf = x + UBP * mGain.getNextValue();
        const double LS = x + mGain.getNextValue() * LP;
        const double HS = x + mGain.getNextValue() * HP;
            
        // unit delay (state variable)
        mZ1[ch] = mGCoeff * HP + BP;
        mZ2[ch] = mGCoeff * BP + LP;

        switch (mType)
        {
            case kHighPass: return HP; break;
            case kLowPass: return LP; break;
            case kBandShelf: return BShelf; break;
            case kLowShelf: return LS; break;
            case kHighShelf: return HS; break;
        }
    }

    enum class ParameterId
    {
        kType,
        kQType,
        kSampleRate,
        kBypass
    };
        
    enum FilterType
    {
        kLowShelf,
        kHighPass,
        kBandShelf,
        kLowPass,
        kHighShelf
    };
    
    enum QType
    {
        kParametric,
        kProportional,
    };
    
    void setParameter(ParameterId parameter, SampleType parameterValue);
    void set_parameters(float cutoff, float band_width, float gain)
    {
        // cutoff
        mCutoff = juce::jlimit(20.0f, 20000.0f, cutoff);
        preWarp();

        // band_width
        mQ = juce::jlimit(0.01f, 0.98f, band_width);

        switch (mQType)
        {
            case kParametric: mRCoeff = 1.0 - mQ; break;
            case kProportional:

                if (mType == kBandShelf)
                {
                    mRCoeff = 1.0 - getPeakQ(mRawGain); break;
                }

                else
                {
                    mRCoeff = 1.0 - getShelfQ(mRawGain); break;
                }
        }

        mRCoeff2 = mRCoeff * 2.0;
        mInversion = 1.0 / (1.0 + mRCoeff2 * mGCoeff + mGCoeff * mGCoeff);

        // gain
        setGain(juce::jlimit(-20.0f, 20.0f, gain));
    }

private:
    
    float mCurrentSampleRate, mQ, mCutoff, mRawGain, twoPi { 3.14159265358979323f };
    bool mGlobalBypass;
    
    juce::SmoothedValue<float> mGain { 0.0f };

     /** Variables for the Z filter equations */
    double mGCoeff, mRCoeff, mRCoeff2, mK, mInversion;
    
    FilterType mType;
    
    QType mQType;
    
     /** state variables (z^-1) */
    std::vector<double> mZ1{}, mZ2{};
    
    void setGain(SampleType value);
    
    SampleType getShelfQ(SampleType value) const;
    SampleType getPeakQ(SampleType value) const;
    
    double sampleRate2X {0.0};
    double halfSampleDuration {0.0};
    
    double wd {0.0};
    double wa {0.0};
    
    void preWarp();
    void setSampleRates();
};
}

#endif /* filter_h */
