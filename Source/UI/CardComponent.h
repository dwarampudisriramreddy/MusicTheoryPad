#pragma once
#include <JuceHeader.h>
class CardComponent : public juce::Component {
public:
    CardComponent() {}
    void paint(juce::Graphics& g) override {
        g.setColour(findColour(juce::ResizableWindow::backgroundColourId).brighter(0.1f));
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 8.0f);
    }
};
