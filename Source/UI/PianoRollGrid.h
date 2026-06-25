#pragma once
#include <JuceHeader.h>

enum class RollType { Melody, Chords, Drums };

class PianoRollGrid : public juce::Component {
public:
    PianoRollGrid(RollType type) : rollType(type) {}
    
    struct Note {
        int keyIndex;
        int startBeat;
        int lengthBeats;
    };
    
    std::vector<Note> notes;
    
    void paint(juce::Graphics& g) override {
        auto bounds = getLocalBounds();
        
        int keyWidth = 60;
        int numKeys = 24;
        float keyHeight = bounds.getHeight() / (float)numKeys;
        int beatWidth = 40;
        
        // Draw background and keys
        for (int i = 0; i < numKeys; ++i) {
            float y = i * keyHeight;
            bool isBlack = false; 
            int noteIndex = i % 12;
            if (noteIndex == 1 || noteIndex == 3 || noteIndex == 6 || noteIndex == 8 || noteIndex == 10) isBlack = true;
            
            g.setColour(isBlack ? juce::Colour(0xff2a2a2a) : juce::Colour(0xff3a3a3a));
            g.fillRect((float)keyWidth, y, (float)(bounds.getWidth() - keyWidth), keyHeight);
            
            g.setColour(isBlack ? juce::Colours::black : juce::Colours::white);
            g.fillRect(0.0f, y, (float)keyWidth, keyHeight);
            g.setColour(juce::Colours::grey);
            g.drawRect(0.0f, y, (float)keyWidth, keyHeight);
            
            g.setColour(juce::Colours::black.withAlpha(0.3f));
            g.drawLine(keyWidth, y, bounds.getWidth(), y);
        }
        
        // Draw vertical beat markers
        int numBeats = (bounds.getWidth() - keyWidth) / beatWidth;
        for (int i = 0; i < numBeats; ++i) {
            float x = keyWidth + i * beatWidth;
            g.setColour((i % 4 == 0) ? juce::Colours::grey.withAlpha(0.6f) : juce::Colours::grey.withAlpha(0.2f));
            g.drawLine(x, 0, x, bounds.getHeight());
        }
        
        // Draw notes
        g.setColour(juce::Colours::cyan);
        for (const auto& note : notes) {
            float x = keyWidth + note.startBeat * beatWidth;
            float y = note.keyIndex * keyHeight;
            float w = note.lengthBeats * beatWidth;
            g.fillRoundedRectangle(x + 1, y + 1, w - 2, keyHeight - 2, 4.0f);
        }
    }
    
    void mouseDown(const juce::MouseEvent& e) override {
        int keyWidth = 60;
        int beatWidth = 40;
        if (e.x < keyWidth) return; // Clicked on piano keys
        
        int numKeys = 24;
        float keyHeight = getHeight() / (float)numKeys;
        
        int clickedBeat = (e.x - keyWidth) / beatWidth;
        int clickedKey = e.y / keyHeight;
        
        // Check if we clicked an existing note to delete it
        for (auto it = notes.begin(); it != notes.end(); ++it) {
            if (it->keyIndex == clickedKey && clickedBeat >= it->startBeat && clickedBeat < it->startBeat + it->lengthBeats) {
                notes.erase(it);
                repaint();
                return;
            }
        }
        
        // Otherwise, add a new note
        notes.push_back({clickedKey, clickedBeat, 1});
        repaint();
    }
    
private:
    RollType rollType;
};
