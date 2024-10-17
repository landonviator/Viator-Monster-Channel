#ifndef Graphic_EQ_h
#define Graphic_EQ_h

#include "filter.h"
#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace viator
{

class GraphicEQ
{
public:
    GraphicEQ()
    {
        for (int i = 0; i < numFilters; ++i) {
            filters.emplace_back(std::make_unique<viator::SVFilter<float>>());
        }
    }

    void prepare (const juce::dsp::ProcessSpec& spec) const
    {
        using parameter = viator::SVFilter<float>::ParameterId;
        using type = viator::SVFilter<float>::FilterType;
        using qType = viator::SVFilter<float>::QType;
        for (const auto& filter : filters) {
            if (filter != nullptr) {
                filter->prepare(static_cast<float>(spec.sampleRate), static_cast<int>(spec.numChannels));
                filter->setParameter(parameter::kType, type::kBandShelf);
                filter->setParameter(parameter::kQType, qType::kProportional);
            }
        }
    }

    // =====================================================================
    // MAIN PROCESS METHOD
    // =====================================================================
    void process (juce::AudioBuffer<float>& buffer) const
    {
        for (const auto& filter : filters) {
            if (filter != nullptr) {
                filter->processBuffer(buffer);
            }
        }
    }

    void updateFilterParameters(const std::vector<float>& cutoffs,
        const float bandWidth, const std::vector<float>& gains) const {
        using parameter = viator::SVFilter<float>::ParameterId;
        int index = 0;
        for (const auto& filter : filters) {
            if (filter != nullptr) {
                jassert(cutoffs.size() == filters.size() &&
                    gains.size() == filters.size());
                filter->set_parameters(cutoffs[index], bandWidth, gains[index]);
            }

            index++;
        }
    }

private:
    static constexpr int numFilters {10};

    std::vector<std::unique_ptr<viator::SVFilter<float>>> filters;
};

} // namespace

#endif /* Graphic_EQ_h */
