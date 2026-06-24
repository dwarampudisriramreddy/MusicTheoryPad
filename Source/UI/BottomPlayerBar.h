#pragma once
#include <JuceHeader.h>

class BottomPlayerBar : public juce::Component {
public:
    BottomPlayerBar() {
        playButton.setButtonText("Play");
        stopButton.setButtonText("Stop");
        recordButton.setButtonText("Record");
        
        playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgreen);
        stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkred);
        recordButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkred.withAlpha(0.5f));
        
        addAndMakeVisible(playButton);
        addAndMakeVisible(stopButton);
        addAndMakeVisible(recordButton);
        
        transportSlider.setSliderStyle(juce::Slider::LinearHorizontal);
        transportSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible(transportSlider);
    }
    
    void paint(juce::Graphics& g) override {
        g.fillAll(juce::Colour(0xff1a1a1a)); // Dark background
        g.setColour(juce::Colours::grey);
        g.drawLine(0, 0, getWidth(), 0, 2.0f); // Top border
    }
    
    void resized() override {
        auto b = getLocalBounds().reduced(10);
        playButton.setBounds(b.removeFromLeft(80));
        b.removeFromLeft(10);
        stopButton.setBounds(b.removeFromLeft(80));
        b.removeFromLeft(10);
        recordButton.setBounds(b.removeFromLeft(80));
        b.removeFromLeft(20);
        transportSlider.setBounds(b);
    }

private:
    juce::TextButton playButton, stopButton, recordButton;
    juce::Slider transportSlider;
};
