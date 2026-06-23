#pragma once
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
