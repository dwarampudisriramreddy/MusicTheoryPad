#pragma once
#include <JuceHeader.h>
class CardComponent : public juce::Component {
public:
    CardComponent() {}
    void paint(juce::Graphics& g) override {
        g.setColour(juce::Colour(0xff1e1e1e)); // Dark card background
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 8.0f);
        
        // Add a subtle border
        g.setColour(juce::Colour(0xff333333));
        g.drawRoundedRectangle(getLocalBounds().toFloat(), 8.0f, 1.0f);
    }
};
