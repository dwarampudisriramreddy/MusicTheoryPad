#pragma once
#include <JuceHeader.h>

enum class RollType { Melody, Chords, Drums };

class PianoRollGrid : public juce::Component {
public:
    PianoRollGrid(RollType type) : rollType(type) {}
    
    void paint(juce::Graphics& g) override {
        auto bounds = getLocalBounds();
        
        // Draw piano keys on the left
        int keyWidth = 60;
        int numKeys = 24;
        float keyHeight = bounds.getHeight() / (float)numKeys;
        
        for (int i = 0; i < numKeys; ++i) {
            float y = i * keyHeight;
            bool isBlack = false; // Simplified
            int noteIndex = i % 12;
            if (noteIndex == 1 || noteIndex == 3 || noteIndex == 6 || noteIndex == 8 || noteIndex == 10) isBlack = true;
            
            // Note: piano roll usually has low notes at the bottom, so we should invert i.
            // For simplicity, we just draw alternating colors.
            g.setColour(isBlack ? juce::Colours::black : juce::Colours::white);
            g.fillRect(0.0f, y, (float)keyWidth, keyHeight);
            g.setColour(juce::Colours::grey);
            g.drawRect(0.0f, y, (float)keyWidth, keyHeight);
            
            // Draw grid lanes
            g.setColour(isBlack ? juce::Colour(0xff2a2a2a) : juce::Colour(0xff3a3a3a));
            g.fillRect((float)keyWidth, y, bounds.getWidth() - keyWidth, keyHeight);
            g.setColour(juce::Colours::black.withAlpha(0.3f));
            g.drawLine(keyWidth, y, bounds.getWidth(), y);
        }
        
        // Draw vertical beat markers
        int beatWidth = 40;
        int numBeats = (bounds.getWidth() - keyWidth) / beatWidth;
        for (int i = 0; i < numBeats; ++i) {
            float x = keyWidth + i * beatWidth;
            g.setColour((i % 4 == 0) ? juce::Colours::grey.withAlpha(0.6f) : juce::Colours::grey.withAlpha(0.2f));
            g.drawLine(x, 0, x, bounds.getHeight());
        }
    }
private:
    RollType rollType;
};
