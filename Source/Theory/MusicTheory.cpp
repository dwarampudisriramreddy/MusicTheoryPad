#include "MusicTheory.h"
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
