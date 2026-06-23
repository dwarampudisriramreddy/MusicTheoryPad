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
