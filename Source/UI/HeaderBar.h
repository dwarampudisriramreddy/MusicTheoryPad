#pragma once
#include <JuceHeader.h>
class HeaderBar : public juce::Component {
public:
    HeaderBar() {
        titleLabel.setText("Music Theory Pad", juce::dontSendNotification);
        subtitleLabel.setText("Chord & Melody Composer", juce::dontSendNotification);
        addAndMakeVisible(titleLabel);
        addAndMakeVisible(subtitleLabel);
    }
    void resized() override {
        titleLabel.setBounds(10, 10, 200, 30);
        subtitleLabel.setBounds(10, 40, 200, 20);
    }
private:
    juce::Label titleLabel, subtitleLabel;
};
