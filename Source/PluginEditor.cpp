/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SineWaveSynAudioProcessorEditor::SineWaveSynAudioProcessorEditor (SineWaveSynAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    levelSlider.setValue(0.5);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,
                                true,
                                levelSlider.getTextBoxWidth(),
                                levelSlider.getTextBoxHeight());
    
    waveSelector.addItemList({ "Sine", "Square", "Triangle", "Saw" },  1);
    waveSelector.setSelectedId(1);
    
    levelSliderAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "GAIN", levelSlider);
    waveSelectorAttachment = std::make_unique< juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree, "TYPE", waveSelector);    
    
    addAndMakeVisible(levelSlider);
    addAndMakeVisible(waveSelector);
}

SineWaveSynAudioProcessorEditor::~SineWaveSynAudioProcessorEditor()
{
}

//==============================================================================
void SineWaveSynAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);
    int x = 50;
    int y = 100;
    int width = 50;
    int height = levelSlider.getHeight();
    
    g.drawFittedText("Level", x, y, width, height, juce::Justification::centred, 1);
}

void SineWaveSynAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    int sliderWidth = area.getWidth() / 2;
    int sliderHeight = area.getHeight() / 4;
    int x = 100;
    int y = 100;
    
    levelSlider.setBounds(x, y, sliderWidth, sliderHeight);
    
    waveSelector.setBounds(100, 50, sliderWidth, sliderHeight/2);
}
