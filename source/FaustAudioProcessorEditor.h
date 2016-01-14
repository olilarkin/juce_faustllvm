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
  void audioProcessorParameterChanged (AudioProcessor* p, int parameterIndex, float newValue) override;

  //Timer
  void timerCallback() override;
  
  // FAUST UI
  void openTabBox(const char* label) override;
  void openHorizontalBox(const char* label) override;
  void openVerticalBox(const char* label) override;
  void closeBox() override;
  void addButton(const char* label, FAUSTFLOAT* zone) override;
  void addCheckButton(const char* label, FAUSTFLOAT* zone) override;
  void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override;
  void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override;
  void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override;
  void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override;
  void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override;
  
private:
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustAudioProcessorEditor)
};

#endif //FAUSTAUDIOPROCESSOREDITOR_H_INCLUDED