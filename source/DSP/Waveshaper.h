#ifndef Waveshaper_h
#define Waveshaper_h

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include "filter.h"
#include "utils.h"

namespace viator
{

class Waveshaper
{
public:
    Waveshaper() = default;

    void prepare (const juce::dsp::ProcessSpec& spec);
    void reset();

    // =====================================================================
    // MAIN PROCESS METHOD
    // =====================================================================
    void process (juce::dsp::AudioBlock<float>& block);

    // =====================================================================
    // PARAMETER UPDATES
    // =====================================================================
    void set_drive(float newDrive);
    void set_mix (float newMix);
    void set_output (float newOutput);

private:
    double sampleRate = 44100.0;
    float ln = 0.5f;
    float lp = 23.0f;
    float ln_lp = 1.01f;
    float g = 10.0f;

    juce::SmoothedValue<float> drive_param;
    juce::SmoothedValue<float> drive_compensate_param;
    juce::SmoothedValue<float> raw_drive_param;
    juce::SmoothedValue<float> mix_param;
    juce::SmoothedValue<float> output_param;

    juce::dsp::LinkwitzRileyFilter<float> negative_dc_filter;
    juce::dsp::LinkwitzRileyFilter<float> positive_dc_filter;

    // =====================================================================
    // Poletti Waveshaper
    // =====================================================================
    void processBlock (const juce::dsp::AudioBlock<float>& block)
    {
        for (int channel = 0; channel < block.getNumChannels(); ++channel)
        {
            auto* data = block.getChannelPointer(channel);

            for (int sample = 0; sample < block.getNumSamples(); ++sample)
            {
                const auto poletti = processSample(data[sample], channel);
                data[sample] = viator::dsp::clippers::get_hard_clipped_data(poletti);
            }
        }
    }

    float processSample(const float input, const int channel)
    {
        // xn from the equations
        const auto xn = input * 0.01f * drive_param.getNextValue();

        // asymmetrical waveshaper
        auto yn_positive = processWaveshaper(xn, g, ln, lp);
        auto yn_negative = processWaveshaper(xn, g, lp, ln);

        // highpass for dc offset
        yn_positive = positive_dc_filter.processSample(channel, yn_positive);
        yn_negative = negative_dc_filter.processSample(channel, yn_negative);

        // symmetrical waveshaper
        yn_positive = processWaveshaper(yn_positive, g * 2.0f, ln_lp, ln_lp);
        yn_negative = processWaveshaper(yn_negative, g * 2.0f, ln_lp, ln_lp);

        const auto signal = (yn_positive + yn_negative) * 0.51f * drive_compensate_param.getNextValue();
        const auto drive_blend = (1.0f - raw_drive_param.getNextValue()) * input + signal * raw_drive_param.getNextValue();
        const auto blend = (1.0f - mix_param.getNextValue()) * input + drive_blend *
            output_param.getNextValue() * mix_param.getNextValue();

        return blend;
    }

    static float processWaveshaper (
        const float xn,
        const float k,
        const float ln,
        const float lp)
    {
        float yn = 0.0f;
        const float numerator = k * xn;

        if (xn <= 0.0)
          yn = numerator / (1.0f - (numerator / ln));
        else
          yn = numerator / (1.0f + (numerator / lp));

        return yn;
    }
};

} // namespace

#endif /* Waveshaper_h */
