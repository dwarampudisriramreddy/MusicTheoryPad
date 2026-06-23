#pragma once
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
