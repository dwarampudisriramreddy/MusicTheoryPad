#pragma once
#include <JuceHeader.h>
enum class RollType { Melody, Chords, Drums };
class PianoRollGrid : public juce::Component {
public:
    PianoRollGrid(RollType type) : rollType(type) {}
    void paint(juce::Graphics& g) override {
        g.fillAll(juce::Colours::black);
    }
private:
    RollType rollType;
};
