/*
  ==============================================================================

    FaustAudioProcessorEditor.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#pragma once

#include "faust/gui/JuceGUI.h"

class FaustAudioProcessorEditor : public AudioProcessorEditor, private Timer
{
public:
  FaustAudioProcessorEditor (AudioProcessor& processor, dsp& dsp);
  ~FaustAudioProcessorEditor();
  
  void paint (Graphics& g) override;
  void resized() override;
  
  void timerCallback() override
  {
    GUI::updateAllGuis();
  }
  

private:
  JuceGUI juceGUI;
  dsp& fDSP;
  ComponentBoundsConstrainer constrainer;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustAudioProcessorEditor)
};

