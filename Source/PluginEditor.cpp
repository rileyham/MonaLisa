/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"
#include "RotaryKnob.h"

//==============================================================================
MonaLisaAudioProcessorEditor::MonaLisaAudioProcessorEditor (MonaLisaAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Distortion group
    distortionGroup.setText("Distortion");
    distortionGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    distortionGroup.addAndMakeVisible(driveKnob);
    addAndMakeVisible(distortionGroup);
    
    // Output group
    outputGroup.setText("Output");
    outputGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    outputGroup.addAndMakeVisible(gainKnob);
    outputGroup.addAndMakeVisible(mixKnob);
    addAndMakeVisible(outputGroup);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (290, 330);
}

MonaLisaAudioProcessorEditor::~MonaLisaAudioProcessorEditor()
{
}

//==============================================================================
void MonaLisaAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Plugin Header
    
    g.fillAll (juce::Colours::lightpink);

    /*
    g.setColour (juce::Colours::firebrick);
    juce::Font bodoni ("Bodoni 72", "Book Italic", 50.0f);
    g.setFont(bodoni);
    g.drawFittedText ("MONA LISA", getLocalBounds(), juce::Justification::centred, 1);
     */
    
    // Distortion group
}

void MonaLisaAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    
    int y = 10;
    int height = bounds.getHeight() - 20;
    
    // position the groups
    distortionGroup.setBounds(10, y, 110, height);
    outputGroup.setBounds(bounds.getWidth() - 160, y, 150, height);
    
    // position the knobs inside the groups
    driveKnob.setTopLeftPosition(20, 20);
    mixKnob.setTopLeftPosition(20, 20);
    gainKnob.setTopLeftPosition(mixKnob.getX(), mixKnob.getBottom() + 10);
}
