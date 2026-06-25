#include "MainComponent.h"
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
    
    bottomBar.onPlayClicked = [this]() {
        audioEngine.setPlaying(true);
    };
    bottomBar.onStopClicked = [this]() {
        audioEngine.setPlaying(false);
    };
}
MainComponent::~MainComponent() { shutdownAudio(); }
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) { audioEngine.prepareToPlay(samplesPerBlockExpected, sampleRate); }
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) { audioEngine.getNextAudioBlock(bufferToFill); }
void MainComponent::releaseResources() { audioEngine.releaseResources(); }
void MainComponent::paint(juce::Graphics& g) { 
    g.fillAll(juce::Colour(0xff121212)); // Dark DAW background
}
void MainComponent::resized() {
    auto b = getLocalBounds();
    headerBar.setBounds(b.removeFromTop(60));
    bottomBar.setBounds(b.removeFromBottom(60));
    sidebar.setBounds(b.removeFromLeft(sidebarVisible ? 200 : 0));
    contentViewport.setBounds(b);
    
    int contentHeight = 1100; // Give enough space for piano rolls
    contentPanel.setBounds(0, 0, b.getWidth() > 0 ? b.getWidth() - 20 : 1000, contentHeight);
    
    auto p = contentPanel.getLocalBounds().reduced(10);
    controlsPanel.setBounds(p.removeFromTop(60));
    p.removeFromTop(10);
    chordPalette.setBounds(p.removeFromTop(100));
    p.removeFromTop(10);
    progressionComponent.setBounds(p.removeFromTop(100));
    p.removeFromTop(10);
    theoryInfo.setBounds(p.removeFromTop(60));
    p.removeFromTop(10);
    chordRoll.setBounds(p.removeFromTop(200));
    p.removeFromTop(10);
    melodyRoll.setBounds(p.removeFromTop(200));
    p.removeFromTop(10);
    drumRoll.setBounds(p.removeFromTop(200));
}
void MainComponent::timerCallback() {}
