#pragma once
#include <JuceHeader.h>
#include "CardComponent.h"

class ProgressionComponent : public CardComponent {
public:
    ProgressionComponent() {
        titleLabel.setText("Chord Progression", juce::dontSendNotification);
        titleLabel.setFont(juce::FontOptions(16.0f));
        addAndMakeVisible(titleLabel);
    }
    
    void paint(juce::Graphics& g) override {
        CardComponent::paint(g);
        
        auto b = getLocalBounds().reduced(10);
        b.removeFromTop(25);
        
        g.setColour(juce::Colour(0xff2b2b2b));
        g.fillRoundedRectangle(b.toFloat(), 5.0f);
        
        g.setColour(juce::Colour(0xff606060));
        g.drawText("Drag chords here to build a progression", b, juce::Justification::centred, false);
    }
    
    void resized() override {
        auto b = getLocalBounds().reduced(5);
        titleLabel.setBounds(b.removeFromTop(25));
    }
private:
    juce::Label titleLabel;
};
