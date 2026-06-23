#pragma once
#include <JuceHeader.h>
class AudioEngine {
public:
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) { bufferToFill.clearActiveBufferRegion(); }
    void releaseResources() {}
};
