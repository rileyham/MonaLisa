/*
  ==============================================================================

    Parameters.cpp
    Created: 30 Jul 2024 4:15:52pm
    Author:  Riley Ham

  ==============================================================================
*/

#include "Parameters.h"

template<typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);
}

static juce::String stringFromDecibels(float value, int)
{
    return juce::String(value, 1) + " db";
}

static juce::String stringFromPercent(float value, int)
{
    return juce::String(int(value))+ " %";
}

static juce::String stringFromHz(float value, int)
{
    if (value < 1000.0f) {
        return juce::String(int(value)) + " Hz";
    } else if (value < 10000.0f) {
        return juce::String(value / 1000.0f, 2) + " kHz";
    } else {
        return juce::String(value / 1000.0f, 1) + " kHz";
    }
}

static float hzFromString(const juce::String& str)
{
    float value = str.getFloatValue();
    if (value < 20.0f) {
        return value * 1000.0f;
    }
    return value;
}

Parameters::Parameters(juce::AudioProcessorValueTreeState &apvts)
{
    castParameter(apvts, gainParamID, gainParam);
    castParameter(apvts, mixParamID, mixParam);
    castParameter(apvts, driveParamID, driveParam);
    castParameter(apvts, lowCutParamID, lowCutParam);
    castParameter(apvts, highCutParamID, highCutParam);
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>(gainParamID,
                                                           "Output Gain",
                                                           juce::NormalisableRange<float>{-12.0f, 12.0f},
                                                           0.0f,
                                                           juce::AudioParameterFloatAttributes()
                                                                    .withStringFromValueFunction(stringFromDecibels)));
    layout.add(std::make_unique<juce::AudioParameterFloat>(mixParamID,
                                                           "Mix",
                                                           juce::NormalisableRange<float>{0.0f, 100.0f},
                                                           100.0f,
                                                           juce::AudioParameterFloatAttributes()
                                                                    .withStringFromValueFunction(stringFromPercent)));
    layout.add(std::make_unique<juce::AudioParameterFloat>(driveParamID,
                                                           "Drive",
                                                           juce::NormalisableRange<float>{0.0f, 40.0f},
                                                           5.0f,
                                                           juce::AudioParameterFloatAttributes()
                                                                    .withStringFromValueFunction(stringFromDecibels)));
    layout.add(std::make_unique<juce::AudioParameterFloat>(lowCutParamID,
                                                           "Low Cut",
                                                           juce::NormalisableRange<float>{20.0f, 20000.0f, 1.0f, 0.3f},
                                                           20.0f,
                                                           juce::AudioParameterFloatAttributes()
                                                                    .withStringFromValueFunction(stringFromHz)
                                                                    .withValueFromStringFunction(hzFromString)
                                                           ));
    layout.add(std::make_unique<juce::AudioParameterFloat>(highCutParamID,
                                                           "High Cut",
                                                           juce::NormalisableRange<float>{20.0f, 20000.0f, 1.0f, 0.3f},
                                                           20000.0f,
                                                           juce::AudioParameterFloatAttributes()
                                                                    .withStringFromValueFunction(stringFromHz)
                                                                    .withValueFromStringFunction(hzFromString)
                                                           ));
    
    
    return layout;
}

void Parameters::update() noexcept
{
    // update smoothers
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    mixSmoother.setTargetValue(mixParam->get() * 0.01f);
    driveSmoother.setTargetValue(driveParam->get());
    lowCutSmoother.setTargetValue(lowCutParam->get());
    highCutSmoother.setTargetValue(highCutParam->get());
}

void Parameters::prepareToPlay(double sampleRate) noexcept
{
    double duration = 0.02f;
        
    // reset smoothers
    gainSmoother.reset(sampleRate, duration);
    mixSmoother.reset(sampleRate, duration);
    driveSmoother.reset(sampleRate, duration);
    lowCutSmoother.reset(sampleRate, duration);
    highCutSmoother.reset(sampleRate, duration);
    
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    mix = 1.0f;
    drive = 0.0f;
    
    // reset smoothers
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    mixSmoother.setCurrentAndTargetValue(mixParam->get() * 0.01f);
    driveSmoother.setCurrentAndTargetValue(driveParam->get());
    lowCutSmoother.setTargetValue(lowCutParam->get());
    highCutSmoother.setTargetValue(highCutParam->get());
    
}

void Parameters::smoothen() noexcept
{
    gain = gainSmoother.getNextValue();
    mix = mixSmoother.getNextValue();
    drive = driveSmoother.getNextValue();
    lowCut = lowCutSmoother.getNextValue();
    highCut = highCutSmoother.getNextValue();
}
