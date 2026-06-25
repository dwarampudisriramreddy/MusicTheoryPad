#pragma once
#include <JuceHeader.h>

class AudioEngine {
public:
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
        this->sampleRate = sampleRate;
        phase = 0.0;
        phaseIncrement = (440.0 * juce::MathConstants<double>::twoPi) / sampleRate;
    }
    
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
        if (!isPlaying) {
            bufferToFill.clearActiveBufferRegion();
            return;
        }
        
        auto* left = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
        auto* right = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
        
        for (int i = 0; i < bufferToFill.numSamples; ++i) {
            float sample = (float) std::sin(phase) * 0.1f; // low volume
            left[i] = sample;
            if (right != nullptr) right[i] = sample;
            
            phase += phaseIncrement;
            if (phase >= juce::MathConstants<double>::twoPi)
                phase -= juce::MathConstants<double>::twoPi;
        }
    }
    
    void releaseResources() {}
    
    void setPlaying(bool play) {
        isPlaying = play;
    }

private:
    double sampleRate = 44100.0;
    double phase = 0.0;
    double phaseIncrement = 0.0;
    bool isPlaying = false;
};
