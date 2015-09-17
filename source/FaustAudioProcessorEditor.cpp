/*
  ==============================================================================

    FaustAudioProcessorEditor.cpp
    Author:  Oliver Larkin

  ==============================================================================
*/

#include "FaustAudioProcessorEditor.h"

FaustAudioProcessorEditor::FaustAudioProcessorEditor(AudioProcessor& processor)
: AudioProcessorEditor(processor)
{
  setSize(300, 300);
}

FaustAudioProcessorEditor::~FaustAudioProcessorEditor()
{
}

void FaustAudioProcessorEditor::paint(Graphics& g)
{
  g.fillAll (Colours::red);
}

void FaustAudioProcessorEditor::resized()
{
}