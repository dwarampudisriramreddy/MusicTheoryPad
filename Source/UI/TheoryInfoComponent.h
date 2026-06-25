#pragma once
#include <JuceHeader.h>
#include "CardComponent.h"
class TheoryInfoComponent : public CardComponent {
public:
    TheoryInfoComponent() {
        infoLabel.setText("Theory Info: I - IV - V (C Major)", juce::dontSendNotification);
        infoLabel.setFont(juce::FontOptions(16.0f));
        addAndMakeVisible(infoLabel);
    }
    
    void resized() override {
        infoLabel.setBounds(getLocalBounds().reduced(10));
    }
private:
    juce::Label infoLabel;
};
