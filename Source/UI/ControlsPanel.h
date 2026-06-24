#pragma once
#include <JuceHeader.h>
#include "CardComponent.h"

class ControlsPanel : public CardComponent {
public:
    ControlsPanel() {
        bpmLabel.setText("BPM:", juce::dontSendNotification);
        bpmLabel.setJustificationType(juce::Justification::centredRight);
        addAndMakeVisible(bpmLabel);
        
        bpmSlider.setSliderStyle(juce::Slider::IncDecButtons);
        bpmSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
        bpmSlider.setRange(40.0, 300.0, 1.0);
        bpmSlider.setValue(120.0);
        addAndMakeVisible(bpmSlider);
        
        keyLabel.setText("Key:", juce::dontSendNotification);
        keyLabel.setJustificationType(juce::Justification::centredRight);
        addAndMakeVisible(keyLabel);
        
        keyCombo.addItem("C Major", 1);
        keyCombo.addItem("G Major", 2);
        keyCombo.addItem("A Minor", 3);
        keyCombo.setSelectedId(1);
        addAndMakeVisible(keyCombo);
    }
    
    void resized() override {
        auto b = getLocalBounds().reduced(10);
        bpmLabel.setBounds(b.removeFromLeft(50));
        b.removeFromLeft(5);
        bpmSlider.setBounds(b.removeFromLeft(100));
        b.removeFromLeft(20);
        
        keyLabel.setBounds(b.removeFromLeft(40));
        b.removeFromLeft(5);
        keyCombo.setBounds(b.removeFromLeft(120));
    }

private:
    juce::Label bpmLabel, keyLabel;
    juce::Slider bpmSlider;
    juce::ComboBox keyCombo;
};
