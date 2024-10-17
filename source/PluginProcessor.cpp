#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
),
      _treeState(*this, nullptr, "PARAMETERS", createParameterLayout()), preset_browser(*this)
{
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getSliderParams()[i].paramID, this);
    }

    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getButtonParams()[i].paramID, this);
    }

    parameters = std::make_unique<ViatorParameters::parameters>(_treeState);

    get_preset_browser().createPresetFolder();
    get_preset_browser().prepareFactoryMenu();

    for (const auto &param : _parameterMap.getSliderParams())
    {
        preset_a[param.paramID] = _treeState.getRawParameterValue(param.paramID)->load();
        preset_b[param.paramID] = _treeState.getRawParameterValue(param.paramID)->load();
    }
}

PluginProcessor::~PluginProcessor()
{
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getSliderParams()[i].paramID, this);
    }

    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getButtonParams()[i].paramID, this);
    }
}

//==============================================================================
const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String PluginProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void PluginProcessor::changeProgramName(int index, const juce::String &newName)
{
    juce::ignoreUnused(index, newName);
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        auto param = _parameterMap.getSliderParams()[i];

        if (param.isInt == viator::ParameterData::SliderParameterData::NumericType::kInt
            || param.isSkew == viator::ParameterData::SliderParameterData::SkewType::kSkew)
        {
            auto range = juce::NormalisableRange<float>(param.min, param.max);

            if (param.isSkew == viator::ParameterData::SliderParameterData::SkewType::kSkew)
            {
                range.setSkewForCentre(param.center);
            }

            params.push_back(std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(juce::ParameterID{
                                                                                                 param.paramID, 1},
                                                                                             param.paramName,
                                                                                             param.paramName,
                                                                                             range,
                                                                                             param.initial,
                                                                                             valueToTextFunction,
                                                                                             textToValueFunction));
        } else
        {
            params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{param.paramID, 1},
                                                                         param.paramName,
                                                                         param.min,
                                                                         param.max,
                                                                         param.initial));
        }
    }

    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        auto param = _parameterMap.getButtonParams()[i];
        params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{param.paramID, 1},
                                                                    param.paramName,
                                                                    _parameterMap.getButtonParams()[i].initial));
    }

    return {params.begin(), params.end()};
}

void PluginProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
}

void PluginProcessor::updateParameters()
{
    switch (_hqMode.load())
    {
        case HQMode::kOff:
        {
            dspModuleOff.set_parameters(*parameters);
            break;
        }

        case HQMode::kTwo:
        {
            dspModuleTwo.set_parameters(*parameters);
            break;
        }

        case HQMode::kFour:
        {
            dspModuleFour.set_parameters(*parameters);
            break;
        }

        case HQMode::kEight:
        {
            dspModuleEight.set_parameters(*parameters);
            break;
        }

        case HQMode::kSixteen:
        {
            dspModuleSixteen.set_parameters(*parameters);
            break;
        }

        default:
        {
            dspModuleOff.set_parameters(*parameters);
            break;
        }
    }

#if !IS_LITE

    // COMPRESSORS
    const auto compOneInput = parameters->compOneInputParam->get();
    const auto compOneAttack = parameters->compOneAttackParam->get();
    const auto compOneHPF = parameters->compOneHPFParam->get();
    const auto compOneRelease = parameters->compOneReleaseParam->get();
    const auto compOneThresh = parameters->compOneThreshParam->get();
    const auto compOneRatio = parameters->compOneRatioParam->get();
    const auto compOneMix = parameters->compOneMixParam->get();
    const auto compOneOut = parameters->compOneOutputParam->get();
    const auto compOneType = parameters->compTwoTypeParam->get();
    compressorOne.setCompressorType(static_cast<viator_core::dsp::Compressor<float>::CompressorType>(compOneType));
    compressorOne.setInputGain(compOneInput);
    compressorOne.setParameters(compOneThresh, compOneRatio, compOneAttack, compOneRelease, 0.0f, compOneHPF);
    compressorOne.setMix(compOneMix);
    compressorOne.setOutputGain(compOneOut);

    const auto compTwoInput = parameters->compTwoInputParam->get();
    const auto compTwoAttack = parameters->compTwoAttackParam->get();
    const auto compTwoHPF = parameters->compTwoHPFParam->get();
    const auto compTwoRelease = parameters->compTwoReleaseParam->get();
    const auto compTwoThresh = parameters->compTwoThreshParam->get();
    const auto compTwoRatio = parameters->compTwoRatioParam->get();
    const auto compTwoMix = parameters->compTwoMixParam->get();
    const auto compTwoOut = parameters->compTwoOutputParam->get();
    const auto compTwoType = parameters->compTwoTypeParam->get();
    compressorTwo.setCompressorType(static_cast<viator_core::dsp::Compressor<float>::CompressorType>(compTwoType));
    compressorTwo.setInputGain(compTwoInput);
    compressorTwo.setParameters(compTwoThresh, compTwoRatio, compTwoAttack, compTwoRelease, 0.0f, compTwoHPF);
    compressorTwo.setMix(compTwoMix);
    compressorTwo.setOutputGain(compTwoOut);

    const auto graphicCutoffs = ViatorParameters::graphicEQCutoffs;
    std::vector<float> gains;
    gains.push_back(parameters->graphicGain0Param->get());
    gains.push_back(parameters->graphicGain1Param->get());
    gains.push_back(parameters->graphicGain2Param->get());
    gains.push_back(parameters->graphicGain3Param->get());
    gains.push_back(parameters->graphicGain4Param->get());
    gains.push_back(parameters->graphicGain5Param->get());
    gains.push_back(parameters->graphicGain6Param->get());
    gains.push_back(parameters->graphicGain7Param->get());
    gains.push_back(parameters->graphicGain8Param->get());
    gains.push_back(parameters->graphicGain9Param->get());
    graphicEQ.updateFilterParameters(graphicCutoffs, 0.3f, gains);
#endif
}

//==============================================================================
void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate, samplesPerBlock);
    process_spec.sampleRate = sampleRate;
    process_spec.numChannels = static_cast<unsigned int>(getTotalNumOutputChannels());
    process_spec.maximumBlockSize = static_cast<unsigned int>(samplesPerBlock);

    dspModuleOff.prepare(process_spec.sampleRate,
                         process_spec.maximumBlockSize,
                         process_spec.numChannels, 0);
    dspModuleTwo.prepare(process_spec.sampleRate,
                         process_spec.maximumBlockSize,
                         process_spec.numChannels, 1);
    dspModuleFour.prepare(process_spec.sampleRate,
                          process_spec.maximumBlockSize,
                          process_spec.numChannels, 2);
    dspModuleEight.prepare(process_spec.sampleRate,
                           process_spec.maximumBlockSize,
                           process_spec.numChannels, 3);
    dspModuleSixteen.prepare(process_spec.sampleRate,
                             process_spec.maximumBlockSize,
                             process_spec.numChannels, 4);

    compressorOne.prepareModule(process_spec);
    compressorOne.reset();
    compressorTwo.prepareModule(process_spec);
    compressorTwo.reset();

    graphicEQ.prepare(process_spec);

    _midBuffer.setSize(1, samplesPerBlock);
    _sideBuffer.setSize(1, samplesPerBlock);

    inputPeakLevel.reset(sampleRate, 0.5);
    outputPeakLevel.reset(sampleRate, 0.5);
}

void PluginProcessor::releaseResources()
{
    waveshaper.reset();
}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                   juce::MidiBuffer &midiMessages)
{
    juce::ignoreUnused(midiMessages);

    if (!parameters->pluginPowerParam->get())
        return;

    updateParameters();

    const auto inputGain = juce::Decibels::decibelsToGain(parameters->inputParam->get());
    buffer.applyGain(inputGain);

    calculateInputPeakLevel(buffer);

    encodeBuffer(buffer);

    switch (_hqMode.load())
    {
        case HQMode::kOff:
        {
            dspModuleOff.process(buffer);
            break;
        }

        case HQMode::kTwo:
        {
            dspModuleTwo.process(buffer);
            break;
        }

        case HQMode::kFour:
        {
            dspModuleFour.process(buffer);
            break;
        }

        case HQMode::kEight:
        {
            dspModuleEight.process(buffer);
            break;
        }

        case HQMode::kSixteen:
        {
            dspModuleSixteen.process(buffer);
            break;
        }

        default:
        {
            dspModuleOff.process(buffer);
            break;
        }
    }

    decodeBuffer(buffer);


    calculateOutputPeakLevel(buffer);

    const auto outputGain = juce::Decibels::decibelsToGain(parameters->outputParam->get());
    buffer.applyGain(outputGain);
}

void PluginProcessor::encodeBuffer(juce::AudioBuffer<float> &buffer)
{
    if (buffer.getNumChannels() < 2) return;

    auto numSamples = buffer.getNumSamples();
    float *leftInputData = buffer.getWritePointer(0);
    float *rightInputData = buffer.getWritePointer(1);

    float *midData = _midBuffer.getWritePointer(0);
    float *sideData = _sideBuffer.getWritePointer(0);

    for (int sample = 0; sample < numSamples; ++sample)
    {
        float mid = 0.5f * (leftInputData[sample] + rightInputData[sample]);
        float side = 0.5f * (leftInputData[sample] - rightInputData[sample]);

        midData[sample] = mid;
        sideData[sample] = side;

        switch (_stereoMode.load())
        {
            case StereoMode::kStereo:
            {
                leftInputData[sample] = leftInputData[sample];
                rightInputData[sample] = rightInputData[sample];
                break;
            }

            case StereoMode::kMono:
            {
                float mono = 0.5f * (leftInputData[sample] + rightInputData[sample]);
                leftInputData[sample] = mono;
                rightInputData[sample] = mono;
                break;
            }

            case StereoMode::kMid:
            {
                leftInputData[sample] = mid;
                rightInputData[sample] = mid;
                break;
            }

            case StereoMode::kSides:
            {
                leftInputData[sample] = side;
                rightInputData[sample] = side;
                break;
            }
        }
    }
}

void PluginProcessor::decodeBuffer(juce::AudioBuffer<float> &buffer)
{
    if (buffer.getNumChannels() < 2) return;

    auto numSamples = buffer.getNumSamples();
    float *leftOutputData = buffer.getWritePointer(0);
    float *rightOutputData = buffer.getWritePointer(1);

    const float *midData = _midBuffer.getReadPointer(0);
    const float *sideData = _sideBuffer.getReadPointer(0);

    for (int sample = 0; sample < numSamples; ++sample)
    {
        switch (_stereoMode.load())
        {
            case StereoMode::kStereo:
            {
                leftOutputData[sample] = leftOutputData[sample];
                rightOutputData[sample] = rightOutputData[sample];
                break;
            }

            case StereoMode::kMono:
            {
                leftOutputData[sample] = leftOutputData[sample];
                rightOutputData[sample] = rightOutputData[sample];
                break;
            }

            case StereoMode::kMid:
            {
                leftOutputData[sample] = leftOutputData[sample] + sideData[sample];
                rightOutputData[sample] = rightOutputData[sample] - sideData[sample];
                break;
            }

            case StereoMode::kSides:
            {
                leftOutputData[sample] = midData[sample] + leftOutputData[sample];
                rightOutputData[sample] = midData[sample] - rightOutputData[sample];
                break;
            }
        }
    }
}

void PluginProcessor::calculateInputPeakLevel(juce::AudioBuffer<float> &buffer)
{
    inputPeakLevel.skip(buffer.getNumSamples());
    inputPeakValue = buffer.getMagnitude(0, 0, buffer.getNumSamples());

    if (inputPeakValue < inputPeakLevel.getCurrentValue())
    {
        inputPeakLevel.setTargetValue(inputPeakValue);
    } else
    {
        inputPeakLevel.setCurrentAndTargetValue(inputPeakValue);
    }
}

void PluginProcessor::calculateOutputPeakLevel(juce::AudioBuffer<float> &buffer)
{
    outputPeakLevel.skip(buffer.getNumSamples());
    outputPeakValue = buffer.getMagnitude(0, 0, buffer.getNumSamples());

    if (outputPeakValue < outputPeakLevel.getCurrentValue())
    {
        outputPeakLevel.setTargetValue(outputPeakValue);
    } else
    {
        outputPeakLevel.setCurrentAndTargetValue(outputPeakValue);
    }
}

float PluginProcessor::GetInputLevel()
{
    return inputPeakLevel.getNextValue();
}

float PluginProcessor::GetOutputLevel()
{
    return outputPeakLevel.getNextValue();
}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *PluginProcessor::createEditor()
{ // Use generic gui for editor for now
    return new PluginEditor(*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void PluginProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    _treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    _treeState.state.writeToStream(stream);
}

void PluginProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    const auto tree = juce::ValueTree::readFromData(data, static_cast<size_t>(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");

    if (tree.isValid())
    {
        _treeState.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
