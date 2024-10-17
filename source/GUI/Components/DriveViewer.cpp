#include "DriveViewer.h"

namespace viator
{

DriveViewer::DriveViewer()
{
    const auto shadow_color = juce::Colours::black;
    auto shadow = juce::DropShadow(shadow_color, 25, {});

    drop_shadow = std::make_unique<juce::DropShadower>(shadow);
    drop_shadow->setOwner(this);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sample_rate;
    spec.maximumBlockSize = 1024;
    spec.numChannels = 2;
    lp_filter.prepare(spec);

    tone_filter.prepare(
        static_cast<float>(spec.sampleRate),
        static_cast<int>(spec.numChannels));

    tone_filter.setParameter(
        viator::SVFilter<float>::ParameterId::kType,
        viator::SVFilter<float>::FilterType::kHighShelf);
    tone_filter.setParameter(
        viator::SVFilter<float>::ParameterId::kQType,
        viator::SVFilter<float>::QType::kParametric);
}

void DriveViewer::paint (juce::Graphics& g)
{
    g.setColour(viator::colors::monster_viewer_bg);
    g.fillRoundedRectangle(
        0,
        0,
        static_cast<float>(getWidth()),
        static_cast<float>(getHeight()),
        6.0f);

    g.setColour(viator::colors::monster_viewer_path);
    draw_signal(g);
}

void DriveViewer::resized()
{
}

void DriveViewer::draw_signal(juce::Graphics& g)
{
    const float midHeight = static_cast<float>(getHeight()) / 2.0f;
    const float amplitude = static_cast<float>(getHeight()) / 2.1f;
    const auto width = static_cast<float>(getWidth());
    const float frequencyFactor =
        2.0f * juce::MathConstants<float>::pi * frequency * 0.13f / width;

    juce::Path sinePath;
    sinePath.startNewSubPath(-1, midHeight);

    hp_filter.setCoefficients(low_cutoff, sample_rate);
    lp_filter.setCutoffFrequency(high_cutoff);

    for (int x = 0; x < getWidth(); ++x)
    {
        const float normalizedX = static_cast<float>(x) * frequencyFactor;
        const float sineValue = std::sin(normalizedX + phase) * global_input;

        const float xn = sineValue * 0.01f * drive;
        float yn_positive = processWaveshaper(xn, gain, ln, lp);
        float yn_negative = processWaveshaper(xn, gain, lp, ln);

        yn_positive = hp_filter_positive.process(yn_positive);
        yn_negative = hp_filter_negative.process(yn_negative);

        yn_positive = processWaveshaper(
            yn_positive,
            gain,
            ln_lp, ln_lp);
        yn_negative = processWaveshaper(
            yn_negative,
            gain,
            ln_lp, ln_lp);

        float distortedValue = static_cast<float>(yn_positive + yn_negative) * 0.51f;
        float drive_blend = (1.0f - raw_drive) * sineValue + distortedValue * raw_drive;
        float signal = (1.0f - mix) * sineValue + drive_blend * mix * output;
        signal *= global_output;
        signal = hp_filter.process(static_cast<float>(signal));
        signal = tone_filter.process_sample(signal, 0);
        signal = lp_filter.processSample(0, static_cast<float>(signal));

        float y = midHeight - amplitude * signal * global_output;
        y = juce::jlimit(0.0f, static_cast<float>(getHeight()), y);
        x = static_cast<int>(juce::jlimit(0.0f, static_cast<float>(getWidth()), static_cast<float>(x)));

        // Check if x or y is out of bounds
        if (y < 0.0f ||
            y > static_cast<float>(getHeight()) ||
            x > getWidth())
        {
            signalInBounds = false;
        }

        sinePath.lineTo(static_cast<float>(x - 1), y);
    }

    g.strokePath(
        sinePath,
        juce::PathStrokeType(2.0f));
}

float DriveViewer::processWaveshaper(const float xn,
                                    const float k,
                                    const float ln,
                                    const float lp)
{
    float yn = 0.0f;
    const float numerator = k * xn;

    if (xn <= 0)
        yn = numerator / (1.0f - (numerator / ln));
    else
        yn = numerator / (1.0f + (numerator / lp));

    return yn;
}

}
