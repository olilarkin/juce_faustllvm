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
  
  constrainer.setSizeLimits(200, 300, 1024, 768);
  setConstrainer(&constrainer);
  
  setResizable (true, true);
  setSize(300, 500);
  
  startTimerHz(25);
}

FaustAudioProcessorEditor::~FaustAudioProcessorEditor()
{
}

void FaustAudioProcessorEditor::paint(Graphics& g)
{
}

void FaustAudioProcessorEditor::resized()
{
  juceGUI.setBounds(getLocalBounds());
}
