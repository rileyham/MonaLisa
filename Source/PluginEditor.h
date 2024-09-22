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
#include "LookAndFeel.h"
#include "LevelMeter.h"

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
    
    RotaryKnob gainKnob {"Gain", audioProcessor.apvts, gainParamID, true};
    RotaryKnob mixKnob {"Mix", audioProcessor.apvts, mixParamID};
    RotaryKnob driveKnob {"Drive", audioProcessor.apvts, driveParamID};
    RotaryKnob lowCutKnob {"Low Cut", audioProcessor.apvts, lowCutParamID};
    RotaryKnob highCutKnob {"High Cut", audioProcessor.apvts, highCutParamID};
    
    juce::GroupComponent distortionGroup, filterGroup, outputGroup;

    MainLookAndFeel mainLF;
    LevelMeter meter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonaLisaAudioProcessorEditor)
};
