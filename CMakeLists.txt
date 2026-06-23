cmake_minimum_required(VERSION 3.20)
project(MusicTheoryPad VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.9 # Use a stable JUCE 7 tag
)
FetchContent_MakeAvailable(juce)

juce_add_gui_app(MusicTheoryPad
    PRODUCT_NAME "Music Theory Pad"
    VERSION ${PROJECT_VERSION}
)

juce_generate_juce_header(MusicTheoryPad)

target_sources(MusicTheoryPad PRIVATE
    Source/Main.cpp
    Source/MainComponent.h
    Source/MainComponent.cpp
    Source/Theory/MusicTheory.h
    Source/Theory/MusicTheory.cpp
    Source/LookAndFeel/AppLookAndFeel.h
    Source/LookAndFeel/AppLookAndFeel.cpp
    Source/UI/CardComponent.h
    Source/UI/CardComponent.cpp
    Source/UI/HeaderBar.h
    Source/UI/HeaderBar.cpp
    Source/UI/ControlsPanel.h
    Source/UI/ControlsPanel.cpp
    Source/UI/ChordPaletteComponent.h
    Source/UI/ChordPaletteComponent.cpp
    Source/UI/ProgressionComponent.h
    Source/UI/ProgressionComponent.cpp
    Source/UI/TheoryInfoComponent.h
    Source/UI/TheoryInfoComponent.cpp
    Source/UI/PianoRollGrid.h
    Source/UI/PianoRollGrid.cpp
    Source/UI/PianoRollSection.h
    Source/UI/PianoRollSection.cpp
    Source/UI/BottomPlayerBar.h
    Source/UI/BottomPlayerBar.cpp
    Source/UI/SavedMidiSidebar.h
    Source/UI/SavedMidiSidebar.cpp
    Source/Audio/SynthVoice.h
    Source/Audio/SynthVoice.cpp
    Source/Audio/DrumSynth.h
    Source/Audio/DrumSynth.cpp
    Source/Audio/AudioEngine.h
    Source/Audio/AudioEngine.cpp
    Source/Midi/MidiIO.h
    Source/Midi/MidiIO.cpp
    Source/State/CompositionState.h
    Source/State/CompositionState.cpp
)

target_compile_definitions(MusicTheoryPad
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
)

target_link_libraries(MusicTheoryPad PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
)
