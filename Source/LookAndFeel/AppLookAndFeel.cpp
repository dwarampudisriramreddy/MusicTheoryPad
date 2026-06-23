#include "AppLookAndFeel.h"
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
