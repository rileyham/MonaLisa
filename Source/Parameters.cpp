/*
  ==============================================================================

    Parameters.cpp
    Created: 30 Jul 2024 4:15:52pm
    Author:  Riley Ham

  ==============================================================================
*/

#include "Parameters.h"

// parameter id constants
const juce::ParameterID gainParamID {"gain", 1};

Parameters::Parameters(juce::AudioProcessorValueTreeState &apvts) {
    auto* param = apvts.getParameter(gainParamID.getParamID());
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(param);
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>(gainParamID,
                                                           "Output Gain",
                                                           juce::NormalisableRange<float>{-12.0f, 12.0f},
                                                           0.0f));
    
    return layout;
}

void Parameters::update() noexcept
{
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
}

void Parameters::prepareToPlay(double sampleRate) noexcept
{
    double duration = 0.02f;
    gainSmoother.reset(sampleRate, duration);
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
}

void Parameters::smoothen() noexcept
{
    gain = gainSmoother.getNextValue()
    ;}
