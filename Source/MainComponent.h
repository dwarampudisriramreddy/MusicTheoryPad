#pragma once

#include <JuceHeader.h>
#include "UI/HeaderBar.h"
#include "UI/ControlsPanel.h"
#include "UI/ChordPaletteComponent.h"
#include "UI/ProgressionComponent.h"
#include "UI/TheoryInfoComponent.h"
#include "UI/PianoRollSection.h"
#include "UI/BottomPlayerBar.h"
#include "UI/SavedMidiSidebar.h"
#include "Audio/AudioEngine.h"
#include "State/CompositionState.h"

class MainComponent  : public juce::AudioAppComponent, public juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    
    void timerCallback() override;

private:
    CompositionState state;
    AudioEngine audioEngine;
    
    HeaderBar headerBar;
    
    juce::Viewport contentViewport;
    juce::Component contentPanel;
    
    ControlsPanel controlsPanel;
    ChordPaletteComponent chordPalette;
    ProgressionComponent progressionComponent;
    TheoryInfoComponent theoryInfo;
    
    PianoRollSection melodyRoll;
    PianoRollSection chordRoll;
    PianoRollSection drumRoll;
    
    BottomPlayerBar bottomBar;
    SavedMidiSidebar sidebar;
    
    bool sidebarVisible = false;
    juce::ComponentAnimator animator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
