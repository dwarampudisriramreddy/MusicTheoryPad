#pragma once
#include <JuceHeader.h>
#include "PianoRollGrid.h"
class PianoRollSection : public juce::Component {
public:
    PianoRollSection(RollType type, const juce::String& name) : grid(type) {
        addAndMakeVisible(viewport);
        viewport.setViewedComponent(&grid, false);
    }
    void resized() override { viewport.setBounds(getLocalBounds()); grid.setBounds(0,0,800,200); }
private:
    juce::Viewport viewport;
    PianoRollGrid grid;
};
