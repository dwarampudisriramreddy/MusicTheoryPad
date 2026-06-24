#pragma once
#include <JuceHeader.h>
#include "CardComponent.h"

class ChordPaletteComponent : public CardComponent {
public:
    ChordPaletteComponent() {
        titleLabel.setText("Chord Palette", juce::dontSendNotification);
        titleLabel.setFont(juce::FontOptions(16.0f));
        addAndMakeVisible(titleLabel);
    }
    
    void paint(juce::Graphics& g) override {
        CardComponent::paint(g);
        
        auto b = getLocalBounds().reduced(10);
        b.removeFromTop(25);
        
        g.setColour(juce::Colour(0xff404040));
        for (int i = 0; i < 7; ++i) {
            juce::Rectangle<int> chordRect(b.getX() + i * 80, b.getY(), 70, 40);
            g.fillRoundedRectangle(chordRect.toFloat(), 5.0f);
            g.setColour(juce::Colours::white);
            g.drawText("I", chordRect, juce::Justification::centred, false);
            g.setColour(juce::Colour(0xff404040));
        }
    }
    
    void resized() override {
        auto b = getLocalBounds().reduced(5);
        titleLabel.setBounds(b.removeFromTop(25));
    }
private:
    juce::Label titleLabel;
};
