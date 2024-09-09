/*
  ==============================================================================

    LookAndFeel.h
    Created: 6 Sep 2024 12:56:41am
    Author:  Riley Ham

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace Colors
{
    const juce::Colour background {0xFF293132};
    const juce::Colour header {0xFFF4D7E8};
    
    namespace Knob
    {
    const juce::Colour trackBackground {0xFF5B575D};
        const juce::Colour trackActive {0xFFF2CFE4};
        const juce::Colour outline { 255, 250, 245 };
        const juce::Colour gradientTop {0xFFF4D7E8};
        const juce::Colour gradientBottom {0xFFF2CFE4};
        const juce::Colour dial { 100, 100, 100 };
        const juce::Colour dropShadow {0xFF000000};
        const juce::Colour label {0xFFF4D7E8};
        const juce::Colour textBoxBackground { 80, 80, 80 };
        const juce::Colour value { 240, 240, 240 };
        const juce::Colour caret { 255, 255, 255 };
    }

    namespace Group
    {
        const juce::Colour label {0xFFBFA6B6};
        const juce::Colour outline {0xFF8C7D88};
    }
}

class Fonts
{
    Fonts() = delete;
    
public:
    static juce::Font getFont(float height = 16.0f);
    static juce::Font getHeaderFont(float height = 46.0f);

private:
    static const juce::Typeface::Ptr typeface;
    static const juce::Typeface::Ptr headerTypeface;
};

class RotaryKnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    RotaryKnobLookAndFeel();
    
    static RotaryKnobLookAndFeel* get()
    {
        static RotaryKnobLookAndFeel instance;
        return &instance;
    }
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                        float sliderPos, float rotaryStartAngle,
                        float rotaryEndAngle, juce::Slider& slider)
    override;
    
    void drawTextEditorOutline(juce::Graphics&, int, int, juce::TextEditor&) override { }
    void fillTextEditorBackground(juce::Graphics&, int width, int height, juce::TextEditor&) override;
    
    float MARGIN = 2.0f;
    juce::Font getLabelFont(juce::Label&) override;
    juce::Label* createSliderTextBox(juce::Slider&) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryKnobLookAndFeel)
    
    juce::DropShadow dropShadow {Colors::Knob::dropShadow, 6, {0, 3} }; // {color, radius, xy offset}
};

class MainLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MainLookAndFeel();
    
    juce::Font getLabelFont(juce::Label&) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLookAndFeel)
};
