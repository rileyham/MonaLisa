/*
  ==============================================================================

    Parameters.h
    Created: 30 Jul 2024 4:15:52pm
    Author:  Riley Ham

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

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
    
private:
    juce::AudioParameterFloat* gainParam;
    juce::LinearSmoothedValue<float> gainSmoother;
};
