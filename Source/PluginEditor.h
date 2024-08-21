/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"
#include "RotaryKnob.h"

//==============================================================================
/**
*/
class MonaLisaAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MonaLisaAudioProcessorEditor (MonaLisaAudioProcessor&);
    ~MonaLisaAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonaLisaAudioProcessor& audioProcessor;
    
    RotaryKnob gainKnob {"Gain", audioProcessor.apvts, gainParamID};
    RotaryKnob mixKnob {"Mix", audioProcessor.apvts, mixParamID};
    RotaryKnob driveKnob {"Drive", audioProcessor.apvts, driveParamID};
    
    juce::GroupComponent distortionGroup, outputGroup;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonaLisaAudioProcessorEditor)
};
