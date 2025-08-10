/*
  ==============================================================================

    Parameters.h
    Created: 30 Jul 2024 4:15:52pm
    Author:  Riley Ham

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// parameter id constants
const juce::ParameterID gainParamID {"gain", 1};
const juce::ParameterID mixParamID {"mix", 1};
const juce::ParameterID driveParamID {"drive", 1};
const juce::ParameterID lowCutParamID {"lowCut", 1};
const juce::ParameterID highCutParamID {"highCut", 1};
const juce::ParameterID bypassParamID {"bypass", 1};

class Parameters
{
    public:
    Parameters(juce::AudioProcessorValueTreeState &apvts);
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    void prepareToPlay(double sampleRate) noexcept;
    void update() noexcept;
    void reset() noexcept;
    void smoothen() noexcept;
    
    float gain = 0.0f;
    float mix = 1.0f;
    float drive = 0.0f;
    float lowCut = 20.0f;
    float highCut = 20000.0f;
    bool bypassed = false;
    
    juce::AudioParameterBool* bypassParam;
    
private:
    juce::AudioParameterFloat* gainParam;
    juce::LinearSmoothedValue<float> gainSmoother;
    
    juce::AudioParameterFloat* mixParam;
    juce::LinearSmoothedValue<float> mixSmoother;
    
    juce::AudioParameterFloat* driveParam;
    juce::LinearSmoothedValue<float> driveSmoother;
    
    juce::AudioParameterFloat* lowCutParam;
    juce::LinearSmoothedValue<float> lowCutSmoother;
    
    juce::AudioParameterFloat* highCutParam;
    juce::LinearSmoothedValue<float> highCutSmoother;
};
