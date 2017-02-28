/*
  ==============================================================================

    FaustAudioProcessorEditor.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#ifndef FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED
#define FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED

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

#endif //FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED
