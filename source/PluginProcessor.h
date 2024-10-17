#pragma once

#include "Global/Parameters.h"
#include "GUI/panels/PluginUnlocker.h"
#include "DSP/Waveshaper.h"
#include "DSP/Compressor.h"
#include "DSP/GraphicEQ.h"
#include "GUI/Components/PresetBrowser.h"
#include "DSP_Module.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class PluginProcessor : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener

{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState &get_tree_state() { return _treeState; }
    juce::ValueTree &getVariableTree() { return variableTree; }
    viator::ParameterData::Params &getParameterMap() { return _parameterMap; }

    viator::PluginUnlocker& getUnlockerPanel() { return unlocker_panel; }
    viator_core::dsp::Compressor<float>& getComp1() {return compressorOne;}
    viator_core::dsp::Compressor<float>& getComp2() {return compressorTwo;}

    bool getIsPlaying() { return isPlaying.load(); }

    const juce::String& getProjectName(){return projectName;};

    PresetBrowser& get_preset_browser() { return preset_browser; }

    enum class StereoMode
    {
        kStereo,
        kMono,
        kMid,
        kSides
    };

    enum class HQMode
    {
        kOff,
        kTwo,
        kFour,
        kEight,
        kSixteen
    };

    void set_stereo_mode(const StereoMode newMode) { _stereoMode.store(newMode); }
    void set_hq_mode(const HQMode newMode) { _hqMode.store(newMode); }

    float GetInputLevel();
    float GetOutputLevel();

    std::map<juce::String, float>& getPresetA() { return preset_a; }
    std::map<juce::String, float>& getPresetB() { return preset_b; }

private:
    // tree state and parameter stuff
    viator::ParameterData::Params _parameterMap;
    juce::AudioProcessorValueTreeState _treeState;
    juce::ValueTree variableTree{"Variables", {}, {{"Group", {{"name", "Vars"}},
        {{"Parameter", {{"id", "width"}, {"value", 1000.0}}},
            {"Parameter", {{"id", "height"}, {"value", 500.0}}},
            {"Parameter", {{"id", "presetFolder"}, {"value", ""}}},
            {"Parameter", {{"id", "stereoMenu"}, {"value", 0}}},
            {"Parameter", {{"id", "hqMenu"}, {"value", 1}}}
        }}}};

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String &parameterID, float newValue) override;
    using Parameter = juce::AudioProcessorValueTreeState::Parameter;
    static juce::String valueToTextFunction(const float x) { return juce::String(static_cast<int>(x)); }
    static float textToValueFunction(const juce::String &str) { return str.getFloatValue(); }
    void updateParameters();

    juce::dsp::ProcessSpec process_spec;

    viator::PluginUnlocker unlocker_panel;

    std::unique_ptr<ViatorParameters::parameters> parameters;

    viator::Waveshaper waveshaper;
    viator_core::dsp::Compressor<float> compressorOne, compressorTwo;
    viator::GraphicEQ graphicEQ;

    std::atomic<bool> isPlaying {false};

    juce::String projectName {"viator-monster-channel"};

    PresetBrowser preset_browser;

    DSP_Module dspModuleOff, dspModuleTwo, dspModuleFour, dspModuleEight, dspModuleSixteen;

    void encodeBuffer(juce::AudioBuffer<float>& buffer);
    void decodeBuffer(juce::AudioBuffer<float>& buffer);

    std::atomic<StereoMode> _stereoMode = StereoMode::kStereo;
    std::atomic<HQMode> _hqMode = HQMode::kOff;
    juce::AudioBuffer<float> _midBuffer;
    juce::AudioBuffer<float> _sideBuffer;

    std::map<juce::String, float> preset_a, preset_b;

    void calculateInputPeakLevel(juce::AudioBuffer<float>& buffer);
    juce::SmoothedValue<float> inputPeakLevel = -60.0;
    float inputPeakValue = -60.0;

    void calculateOutputPeakLevel(juce::AudioBuffer<float>& buffer);
    juce::SmoothedValue<float> outputPeakLevel = -60.0;
    float outputPeakValue = -60.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
