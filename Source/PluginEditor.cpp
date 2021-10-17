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
    setSize (800, 600);
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
    addAndMakeVisible(spectrumPanel);
    addAndMakeVisible(waveformPanel);
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
}

void SineWaveSynAudioProcessorEditor::resized()
{
    juce::Grid grid;
     
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.setGap(juce::Grid::Px(10));
    grid.templateRows    = { Track (Fr (10)), Track(Fr(1)), Track(Fr(1)) };
    grid.templateColumns = { Track (Fr (1)), Track (Fr (1)) };

    grid.items = {
        juce::GridItem (waveformPanel),
        juce::GridItem (spectrumPanel),
        juce::GridItem (waveSelector).withArea({}, juce::GridItem::Span(2)),
        juce::GridItem(levelSlider).withArea({}, juce::GridItem::Span(2))
    };

    grid.performLayout (getLocalBounds().reduced(20, 20));
}
