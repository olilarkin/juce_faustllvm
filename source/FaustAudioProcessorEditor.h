/*
  ==============================================================================

    FaustAudioProcessorEditor.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#ifndef FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED
#define FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED

#include "faust/gui/UI.h"

class FaustSlider : public Slider
{
public:
  FaustSlider(const juce::String& componentName)
  {
  }
protected:
  void mouseDown(const MouseEvent& e)
  {
  }
  
  void mouseUp(const MouseEvent& e)
  {
  }
  
};

class FaustAudioProcessorEditor : public AudioProcessorEditor
                                , private AudioProcessorListener
                                , private Timer
                                , public UI
{
public:
  FaustAudioProcessorEditor (AudioProcessor& processor);
  ~FaustAudioProcessorEditor();
  
  void paint (Graphics& g) override;
  void resized() override;

  //AudioProcessorListener
  void audioProcessorChanged (AudioProcessor*) override;
  void audioProcessorParameterChanged (AudioProcessor* p, int parameterIndex, float newValue);

  //Timer
  void timerCallback();
  
  // FAUST UI
  void openTabBox(const char* label);
  void openHorizontalBox(const char* label);
  void openVerticalBox(const char* label);
  void closeBox();
  void addButton(const char* label, FAUSTFLOAT* zone);
  void addCheckButton(const char* label, FAUSTFLOAT* zone);
  void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
  void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
  void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
  void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
  void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
  
private:
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustAudioProcessorEditor)
};

#endif //FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED