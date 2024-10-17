#pragma once
#ifndef DriveViewer_h
#define DriveViewer_h

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_dsp/juce_dsp.h>
#include "../../DSP/filter.h"
#include "../look.h"

namespace viator
{

    class HighPassFilter
    {
    public:
        HighPassFilter() : alpha(0.0f), previousX(0.0f), previousY(0.0f)
        {
            setCoefficients(cutoffFrequency, sampleRate);
        }

        void setCoefficients(float cutoffFrequency, float sampleRate)
        {
            float RC = 1.0f / (2.0f * juce::MathConstants<float>::pi * cutoffFrequency);
            alpha = RC / (RC + 1.0f / sampleRate);
            previousX = 0.0f;
            previousY = 0.0f;
        }

        float process(float input)
        {
            float output = alpha * (previousY + input - previousX);
            previousX = input;
            previousY = output;
            return output;
        }

    private:
        float alpha;
        float previousX;
        float previousY;
        float cutoffFrequency {10.0f};
        float sampleRate {44100.0f};
    };

class DriveViewer : public juce::Component
{
public:
    DriveViewer();

    void paint (juce::Graphics&) override;
    void resized() override;

    void set_drive(float new_drive)
    {
        drive = juce::Decibels::decibelsToGain(new_drive);

        const auto drive_scaled = juce::jlimit(0.0f, 5.0f, new_drive);
        raw_drive = juce::jmap(drive_scaled, 0.0f, 5.0f, 0.0f, 1.0f);
        repaint();
    }

    void set_mix (float newMix)
    {

        mix = juce::jlimit(0.0f, 100.0f, newMix) * 0.01f;
        repaint();
    }

    void set_output(float new_output)
    {
        output = juce::Decibels::decibelsToGain(new_output);
        repaint();
    }

    void set_low_cutoff(float newCutoff)
    {
        low_cutoff = newCutoff;
        repaint();
    }

    void set_high_cutoff(float newCutoff)
    {
        high_cutoff = newCutoff;
        repaint();
    }

    void update_tone_filter(float gain)
    {
        tone_filter.set_parameters(40.0f, 0.1f, gain);
        repaint();
    }

    bool getIsSignalInBounds()
    {
        return signalInBounds;
    }

    void draw_signal(juce::Graphics& g);

    void set_global_output(float new_output)
    {
        global_output = juce::Decibels::decibelsToGain(new_output);
        repaint();
    }

    void set_global_input(float new_output)
    {
        global_input = juce::Decibels::decibelsToGain(new_output);
        repaint();
    }
    
private:

    std::unique_ptr<juce::DropShadower> drop_shadow;

    static float processWaveshaper(float xn, float k, float ln, float lp);
    float drive = 1.0f;
    float raw_drive = 0.0f;
    float mix = 1.0f;
    float output = 1.0f;
    float global_output = 1.0f;
    float global_input = 1.0f;
    float ln = 0.5f;
    float lp = 23.0f;
    float ln_lp = 1.01f;
    float gain = 10.0f;
    float frequency = 20.0f;
    float phase = 0.0f;
    float low_cutoff = 5.0f;
    float high_cutoff = 1800.0f;
    float sample_rate = 44100.0f;
    viator::HighPassFilter hp_filter_negative, hp_filter_positive, hp_filter;
    juce::dsp::LinkwitzRileyFilter<float> lp_filter;
    viator::SVFilter<float> tone_filter;

    bool signalInBounds = true;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DriveViewer)
};

}

#endif 
