/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SineWaveSynAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SineWaveSynAudioProcessorEditor (SineWaveSynAudioProcessor&);
    ~SineWaveSynAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SineWaveSynAudioProcessor& audioProcessor;
    
    juce::Slider levelSlider;
    juce::ComboBox waveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> levelSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectorAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineWaveSynAudioProcessorEditor)
};
