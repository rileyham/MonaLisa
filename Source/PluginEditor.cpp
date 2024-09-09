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
    // Set look and feel
    setLookAndFeel(&mainLF);
    
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
    setLookAndFeel(nullptr);
}

//==============================================================================
void MonaLisaAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(Colors::background);
    g.fillAll();
    
    /*
    // add a noise texture to the background
    auto noise = juce::ImageCache::getFromMemory(BinaryData::Noise_png, BinaryData::Noise_pngSize);
    noise.multiplyAllAlphas(0.3f);
    auto fillType = juce::FillType(noise, juce::AffineTransform::scale(0.5));
    g.setFillType(fillType);
    g.fillRect(getLocalBounds());
     */
    
    // draw header text
    g.setColour(Colors::header);
    g.setFont(Fonts::getHeaderFont());
    g.drawText("Mona Lisa", 0, 5, getLocalBounds().getWidth(), 40, juce::Justification::centred);

}

void MonaLisaAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    
    int y = 50;
    int height = bounds.getHeight() - 60;
    
    // position the groups
    distortionGroup.setBounds(10, y, 110, height);
    outputGroup.setBounds(bounds.getWidth() - 160, y, 150, height);
    
    // position the knobs inside the groups
    driveKnob.setTopLeftPosition(20, 20);
    mixKnob.setTopLeftPosition(20, 20);
    gainKnob.setTopLeftPosition(mixKnob.getX(), mixKnob.getBottom() + 10);
}
