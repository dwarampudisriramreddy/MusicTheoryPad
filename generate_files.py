import os

base_dir = "/home/sri/MusicTheoryPad/Source"

files = {
    "Theory/MusicTheory.h": """#pragma once
#include <JuceHeader.h>
namespace MusicTheory {
    extern const juce::StringArray ChromaticNotes;
    enum ScaleType { Major, NaturalMinor, Dorian, Mixolydian };
    std::vector<int> getScaleIntervals(ScaleType type);
    juce::String getChordForDegree(int degree, ScaleType type);
    std::vector<int> getChordTones(const juce::String& symbol);
    bool isNoteInScale(int pitch, int rootPitch, ScaleType type);
    juce::String getTheoryBlurb(ScaleType type);
}
""",
    "Theory/MusicTheory.cpp": """#include "MusicTheory.h"
namespace MusicTheory {
    const juce::StringArray ChromaticNotes = {"C","C#","D","Eb","E","F","F#","G","Ab","A","Bb","B"};
    std::vector<int> getScaleIntervals(ScaleType type) {
        if (type == Major) return {0,2,4,5,7,9,11};
        if (type == NaturalMinor) return {0,2,3,5,7,8,10};
        if (type == Dorian) return {0,2,3,5,7,9,10};
        if (type == Mixolydian) return {0,2,4,5,7,9,10};
        return {0,2,4,5,7,9,11};
    }
    juce::String getChordForDegree(int degree, ScaleType type) {
        if (type == Major) {
            juce::StringArray chords = {"I","ii","iii","IV","V","vi","vii°"};
            if (degree >= 0 && degree < 7) return chords[degree];
        } else {
            juce::StringArray chords = {"i","ii°","III","iv","v","VI","VII"};
            if (degree >= 0 && degree < 7) return chords[degree];
        }
        return "";
    }
    std::vector<int> getChordTones(const juce::String& symbol) {
        if (symbol.contains("m") || symbol.contains("i")) return {0, 3, 7};
        if (symbol.contains("°")) return {0, 3, 6};
        return {0, 4, 7};
    }
    bool isNoteInScale(int pitch, int rootPitch, ScaleType type) {
        int interval = (pitch - rootPitch) % 12;
        if (interval < 0) interval += 12;
        auto intervals = getScaleIntervals(type);
        return std::find(intervals.begin(), intervals.end(), interval) != intervals.end();
    }
    juce::String getTheoryBlurb(ScaleType type) {
        if (type == Major) return "I-IV-V-I, I-V-vi-IV, ii-V-I...";
        return "i-iv-v-i, i-VI-VII-i...";
    }
}
""",
    "LookAndFeel/AppLookAndFeel.h": """#pragma once
#include <JuceHeader.h>
class AppLookAndFeel : public juce::LookAndFeel_V4 {
public:
    AppLookAndFeel();
    void setDarkMode(bool dark);
    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                              bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
                      int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) override;
private:
    struct ColourScheme {
        juce::Colour bgPrimary, bgSecondary, bgTertiary, bgCard, textPrimary, textSecondary, textMuted, borderColour;
    } currentScheme;
    void applyScheme();
};
""",
    "LookAndFeel/AppLookAndFeel.cpp": """#include "AppLookAndFeel.h"
AppLookAndFeel::AppLookAndFeel() { setDarkMode(true); }
void AppLookAndFeel::setDarkMode(bool dark) {
    if (dark) {
        currentScheme = {juce::Colour::fromString("#ff1a1a2e"), juce::Colour::fromString("#ff2b2d31"),
                         juce::Colour::fromString("#ff1e1f22"), juce::Colour::fromString("#ff2b2d31"),
                         juce::Colour::fromString("#ffffffff"), juce::Colour::fromString("#ffb0b0b0"),
                         juce::Colour::fromString("#ff888888"), juce::Colour::fromString("#ff3a3c40")};
    } else {
        currentScheme = {juce::Colour::fromString("#fff5f5f7"), juce::Colour::fromString("#ffffffff"),
                         juce::Colour::fromString("#fff8f9fa"), juce::Colour::fromString("#ffffffff"),
                         juce::Colour::fromString("#ff1d1d1f"), juce::Colour::fromString("#ff6e6e73"),
                         juce::Colour::fromString("#ff86868b"), juce::Colour::fromString("#ffd2d2d7")};
    }
    applyScheme();
}
void AppLookAndFeel::applyScheme() {
    setColour(juce::ResizableWindow::backgroundColourId, currentScheme.bgPrimary);
    setColour(juce::TextButton::buttonColourId, currentScheme.bgSecondary);
    setColour(juce::TextButton::textColourOffId, currentScheme.textPrimary);
}
void AppLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
    auto bounds = button.getLocalBounds().toFloat();
    if (button.getProperties().contains("primary")) {
        juce::ColourGradient grad(juce::Colour::fromString("#ff667eea"), bounds.getTopLeft(), juce::Colour::fromString("#ff764ba2"), bounds.getBottomRight(), false);
        g.setGradientFill(grad);
    } else {
        g.setColour(juce::Colour::fromString("#ff3a3c40"));
    }
    g.fillRoundedRectangle(bounds, 10.0f);
}
void AppLookAndFeel::drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) {
    auto bounds = box.getLocalBounds().toFloat();
    g.setColour(currentScheme.bgSecondary);
    g.fillRoundedRectangle(bounds, 10.0f);
    g.setColour(currentScheme.borderColour);
    g.drawRoundedRectangle(bounds, 10.0f, 1.0f);
}
""",
    "UI/CardComponent.h": """#pragma once
#include <JuceHeader.h>
class CardComponent : public juce::Component {
public:
    CardComponent() {}
    void paint(juce::Graphics& g) override {
        g.setColour(findColour(juce::ResizableWindow::backgroundColourId).brighter(0.1f));
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 8.0f);
    }
};
""",
    "UI/CardComponent.cpp": """#include "CardComponent.h"
""",
    "UI/HeaderBar.h": """#pragma once
#include <JuceHeader.h>
class HeaderBar : public juce::Component {
public:
    HeaderBar() {
        titleLabel.setText("Music Theory Pad", juce::dontSendNotification);
        subtitleLabel.setText("Chord & Melody Composer", juce::dontSendNotification);
        addAndMakeVisible(titleLabel);
        addAndMakeVisible(subtitleLabel);
    }
    void resized() override {
        titleLabel.setBounds(10, 10, 200, 30);
        subtitleLabel.setBounds(10, 40, 200, 20);
    }
private:
    juce::Label titleLabel, subtitleLabel;
};
""",
    "UI/HeaderBar.cpp": """#include "HeaderBar.h"
""",
    "UI/ControlsPanel.h": """#pragma once
#include <JuceHeader.h>
#include "CardComponent.h"
class ControlsPanel : public CardComponent {
public:
    ControlsPanel() {}
};
""",
    "UI/ControlsPanel.cpp": """#include "ControlsPanel.h"
""",
    "UI/ChordPaletteComponent.h": """#pragma once
#include <JuceHeader.h>
#include "CardComponent.h"
class ChordPaletteComponent : public CardComponent {
public:
    ChordPaletteComponent() {}
};
""",
    "UI/ChordPaletteComponent.cpp": """#include "ChordPaletteComponent.h"
""",
    "UI/ProgressionComponent.h": """#pragma once
#include <JuceHeader.h>
#include "CardComponent.h"
class ProgressionComponent : public CardComponent {
public:
    ProgressionComponent() {}
};
""",
    "UI/ProgressionComponent.cpp": """#include "ProgressionComponent.h"
""",
    "UI/TheoryInfoComponent.h": """#pragma once
#include <JuceHeader.h>
#include "CardComponent.h"
class TheoryInfoComponent : public CardComponent {
public:
    TheoryInfoComponent() {}
};
""",
    "UI/TheoryInfoComponent.cpp": """#include "TheoryInfoComponent.h"
""",
    "UI/PianoRollGrid.h": """#pragma once
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
""",
    "UI/PianoRollGrid.cpp": """#include "PianoRollGrid.h"
""",
    "UI/PianoRollSection.h": """#pragma once
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
""",
    "UI/PianoRollSection.cpp": """#include "PianoRollSection.h"
""",
    "UI/BottomPlayerBar.h": """#pragma once
#include <JuceHeader.h>
class BottomPlayerBar : public juce::Component {
public:
    BottomPlayerBar() {}
};
""",
    "UI/BottomPlayerBar.cpp": """#include "BottomPlayerBar.h"
""",
    "UI/SavedMidiSidebar.h": """#pragma once
#include <JuceHeader.h>
class SavedMidiSidebar : public juce::Component {
public:
    SavedMidiSidebar() {}
};
""",
    "UI/SavedMidiSidebar.cpp": """#include "SavedMidiSidebar.h"
""",
    "Audio/SynthVoice.h": """#pragma once
#include <JuceHeader.h>
class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound*) override { return true; }
    void startNote(int, float, juce::SynthesiserSound*, int) override {}
    void stopNote(float, bool) override {}
    void pitchWheelMoved(int) override {}
    void controllerMoved(int, int) override {}
    void renderNextBlock(juce::AudioBuffer<float>&, int, int) override {}
};
""",
    "Audio/SynthVoice.cpp": """#include "SynthVoice.h"
""",
    "Audio/DrumSynth.h": """#pragma once
#include <JuceHeader.h>
class DrumSynth {
public:
    void renderNextBlock(juce::AudioBuffer<float>& buffer, int startSample, int numSamples) {}
};
""",
    "Audio/DrumSynth.cpp": """#include "DrumSynth.h"
""",
    "Audio/AudioEngine.h": """#pragma once
#include <JuceHeader.h>
class AudioEngine {
public:
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) { bufferToFill.clearActiveBufferRegion(); }
    void releaseResources() {}
};
""",
    "Audio/AudioEngine.cpp": """#include "AudioEngine.h"
""",
    "Midi/MidiIO.h": """#pragma once
#include <JuceHeader.h>
class MidiIO {
public:
    static void exportMidi(const juce::File& file) {}
    static void importMidi(const juce::File& file) {}
};
""",
    "Midi/MidiIO.cpp": """#include "MidiIO.h"
""",
    "State/CompositionState.h": """#pragma once
#include <JuceHeader.h>
class CompositionState {
public:
    juce::ValueTree state{"Composition"};
};
""",
    "State/CompositionState.cpp": """#include "CompositionState.h"
""",
    "MainComponent.cpp": """#include "MainComponent.h"
MainComponent::MainComponent() : melodyRoll(RollType::Melody, "Melody"), chordRoll(RollType::Chords, "Chords"), drumRoll(RollType::Drums, "Drums") {
    addAndMakeVisible(headerBar);
    addAndMakeVisible(contentViewport);
    contentViewport.setViewedComponent(&contentPanel, false);
    contentPanel.addAndMakeVisible(controlsPanel);
    contentPanel.addAndMakeVisible(chordPalette);
    contentPanel.addAndMakeVisible(progressionComponent);
    contentPanel.addAndMakeVisible(theoryInfo);
    contentPanel.addAndMakeVisible(melodyRoll);
    contentPanel.addAndMakeVisible(chordRoll);
    contentPanel.addAndMakeVisible(drumRoll);
    addAndMakeVisible(bottomBar);
    addAndMakeVisible(sidebar);
    
    setSize(1024, 768);
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { if (granted) setAudioChannels (2, 2); });
    } else {
        setAudioChannels (2, 2);
    }
}
MainComponent::~MainComponent() { shutdownAudio(); }
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) { audioEngine.prepareToPlay(samplesPerBlockExpected, sampleRate); }
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) { audioEngine.getNextAudioBlock(bufferToFill); }
void MainComponent::releaseResources() { audioEngine.releaseResources(); }
void MainComponent::paint(juce::Graphics& g) { g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); }
void MainComponent::resized() {
    auto b = getLocalBounds();
    headerBar.setBounds(b.removeFromTop(60));
    bottomBar.setBounds(b.removeFromBottom(60));
    sidebar.setBounds(b.removeFromLeft(sidebarVisible ? 200 : 0));
    contentViewport.setBounds(b);
    
    int contentHeight = 800;
    contentPanel.setBounds(0, 0, b.getWidth(), contentHeight);
    
    auto p = contentPanel.getLocalBounds().reduced(10);
    controlsPanel.setBounds(p.removeFromTop(60));
    p.removeFromTop(10);
    chordPalette.setBounds(p.removeFromTop(80));
    p.removeFromTop(10);
    progressionComponent.setBounds(p.removeFromTop(80));
    p.removeFromTop(10);
    theoryInfo.setBounds(p.removeFromTop(60));
    p.removeFromTop(10);
    chordRoll.setBounds(p.removeFromTop(120));
    p.removeFromTop(10);
    melodyRoll.setBounds(p.removeFromTop(160));
    p.removeFromTop(10);
    drumRoll.setBounds(p.removeFromTop(160));
}
void MainComponent::timerCallback() {}
"""
}

for rel_path, content in files.items():
    full_path = os.path.join(base_dir, rel_path)
    os.makedirs(os.path.dirname(full_path), exist_ok=True)
    with open(full_path, "w") as f:
        f.write(content)

print("Created all files.")
