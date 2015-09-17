/*
  ==============================================================================

    FaustAudioProcessorEditor.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#ifndef FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED
#define FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED

//#include "modules/juce_audio_processors/processors/juce_AudioProcessorEditor.h"

class FaustAudioProcessorEditor : public AudioProcessorEditor
{
public:
  FaustAudioProcessorEditor (AudioProcessor& processor);
  ~FaustAudioProcessorEditor();
  
  void paint (Graphics& g) override;
  void resized() override;

private:
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustAudioProcessorEditor)
};

#endif //FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED