#pragma once
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
