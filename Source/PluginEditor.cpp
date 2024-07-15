/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonaLisaAudioProcessorEditor::MonaLisaAudioProcessorEditor (MonaLisaAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

MonaLisaAudioProcessorEditor::~MonaLisaAudioProcessorEditor()
{
}

//==============================================================================
void MonaLisaAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::lightpink);

    g.setColour (juce::Colours::firebrick);
    juce::Font bodoni ("Bodoni 72", "Book Italic", 50.0f);
    g.setFont(bodoni);
    g.drawFittedText ("MONA LISA", getLocalBounds(), juce::Justification::centred, 1);
}

void MonaLisaAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
