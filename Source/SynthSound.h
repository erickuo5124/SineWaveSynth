/*
  ==============================================================================

    SynthSound.h
    Created: 3 Oct 2021 1:49:07am
    Author:  郭又宗

  ==============================================================================
*/

#pragma once

class SynthSound : public juce::SynthesiserSound
{

public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiNoteNumber) override
    {
        return true;
    }
};
