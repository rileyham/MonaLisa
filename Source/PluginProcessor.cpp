/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"


//==============================================================================
MonaLisaAudioProcessor::MonaLisaAudioProcessor():
    AudioProcessor(
        BusesProperties()
            .withInput("Input", juce::AudioChannelSet::stereo(), true)
            .withOutput("Input", juce::AudioChannelSet::stereo(), true)
    ),
    params(apvts) // initializes the parameters object
{
}

MonaLisaAudioProcessor::~MonaLisaAudioProcessor()
{
}

//==============================================================================
const juce::String MonaLisaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MonaLisaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MonaLisaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MonaLisaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MonaLisaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MonaLisaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MonaLisaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MonaLisaAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MonaLisaAudioProcessor::getProgramName (int index)
{
    return {};
}

void MonaLisaAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MonaLisaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    params.prepareToPlay(sampleRate);
    params.reset();
    
    // initialize the waveshaper using a lambda function from -0.1 to 0.1
    waveShaper.functionToUse = [] (float x)
    {
        return std::tanh(x);
    };
    /*
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = juce::uint32(samplesPerBlock);
    spec.numChannels = 2;
    
    processorChain.prepare(spec);
    
    processorChain.reset()
    */
}

void MonaLisaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MonaLisaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void MonaLisaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, [[maybe_unused]] juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    params.update();
    
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        params.smoothen();
      
        // read incoming audio into new variables
        float dryL = channelDataL[sample];
        float dryR = channelDataR[sample];
        
        // process the incoming audio into a wet channel
        float wetL = dryL * juce::Decibels::decibelsToGain(params.drive);
        float wetR = dryR * juce::Decibels::decibelsToGain(params.drive);
        
        wetL = waveShaper.processSample(wetL);
        wetR = waveShaper.processSample(wetR);
        
        wetL = wetL * juce::Decibels::decibelsToGain(-params.drive * 0.7);
        wetR = wetR * juce::Decibels::decibelsToGain(-params.drive * 0.7);
        
        // blend
        float mixL = (( dryL * (-params.mix + 1)) + (wetL * params.mix));
        float mixR = (( dryR * (-params.mix + 1)) + (wetR * params.mix));
        
        channelDataL[sample] = mixL * params.gain;
        channelDataR[sample] = mixR * params.gain;

    }
    
}

//==============================================================================
bool MonaLisaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MonaLisaAudioProcessor::createEditor()
{
    return new MonaLisaAudioProcessorEditor (*this);
}

//==============================================================================
void MonaLisaAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // saving parameters
    copyXmlToBinary(*apvts.copyState().createXml(), destData);
}

void MonaLisaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // restoring parameters
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    
    // if there is xml to get, restore it
    if(xml.get() != nullptr && xml->hasTagName(apvts.state.getType())) {
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonaLisaAudioProcessor();
}
