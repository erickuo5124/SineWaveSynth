/*
  ==============================================================================

    SynthVoice.cpp
    Created: 3 Oct 2021 1:49:21am
    Author:  郭又宗

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    noteMidiNumber = midiNoteNumber;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    currentAngle = 0.f;
    angleIncrement = frequency / getSampleRate() * juce::MathConstants<float>::twoPi;
    tailOff = 0.0;
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        level = 0;
        currentAngle = 0.f;
    }
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    // handle pitch wheel moved midi event
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    // handle midi control change
}

void SynthVoice::renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
    for (int i = startSample; i < (startSample + numSamples); i++) {
        float value;
        switch (waveType) {
            case 0: value = std::sin(currentAngle); break; // sine wave
            case 1: value = std::sin(currentAngle) > 0 ? 1 : 0; break; // square wave
            case 2: value = std::asin(sin(currentAngle)); break; // triangle wave
            case 3: value = std::atan(tan(currentAngle)); break; // sawtooth wave
            default: value = std::sin(currentAngle); break; // use sine wave as default
        }
        float out = value * level * (tailOff > 0.0 ? tailOff : 1.0);
        outputBuffer.addSample(0, i, out);
        outputBuffer.addSample(1, i, out);
        
        currentAngle += angleIncrement;
        if (tailOff > 0.0) {
            tailOff *= 0.99;
            if(tailOff <= 0.05){
                clearCurrentNote();
                angleIncrement = 0.0;
                level = 0.0;
                break;
            }
        }
    }
}

void SynthVoice::setLevel(float newLevel)
{
    level = newLevel;
}

void SynthVoice::setWaveType(int type)
{
    waveType = type;
}
