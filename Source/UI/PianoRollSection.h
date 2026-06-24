#pragma once
#include <JuceHeader.h>
#include "PianoRollGrid.h"
#include "CardComponent.h"

class PianoRollSection : public CardComponent {
public:
    PianoRollSection(RollType type, const juce::String& name) : grid(type) {
        trackNameLabel.setText(name, juce::dontSendNotification);
        trackNameLabel.setFont(juce::Font(16.0f, juce::Font::bold));
        addAndMakeVisible(trackNameLabel);
        
        addAndMakeVisible(viewport);
        viewport.setViewedComponent(&grid, false);
    }
    void resized() override {
        auto b = getLocalBounds().reduced(5);
        trackNameLabel.setBounds(b.removeFromTop(25));
        viewport.setBounds(b);
        grid.setBounds(0, 0, 1600, 400); // Larger inner grid for scrolling
    }
private:
    juce::Label trackNameLabel;
    juce::Viewport viewport;
    PianoRollGrid grid;
};
