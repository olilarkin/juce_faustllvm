/*
  ==============================================================================

    FaustAudioProcessorEditor.cpp
    Author:  Oliver Larkin

  ==============================================================================
*/

#include "FaustAudioProcessorEditor.h"

std::list<GUI*> GUI::fGuiList;

FaustAudioProcessorEditor::FaustAudioProcessorEditor(AudioProcessor& processor, dsp& dsp)
: AudioProcessorEditor(processor)
, fDSP(dsp)
{
  addAndMakeVisible(juceGUI);

  fDSP.buildUserInterface(&juceGUI);
  
  setSize(300, 300);
  
  startTimerHz(25);
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
  juceGUI.setBounds(getLocalBounds());
}
