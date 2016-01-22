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

#pragma mark AudioProcessorListener
void FaustAudioProcessorEditor::audioProcessorChanged (AudioProcessor*)
{
}

void FaustAudioProcessorEditor::audioProcessorParameterChanged (AudioProcessor* p, int parameterIndex, float newValue)
{
}

#pragma mark Timer
void FaustAudioProcessorEditor::timerCallback()
{
}

#pragma mark Faust UI
void FaustAudioProcessorEditor::openTabBox(const char* label)
{
  //TODO:
}

void FaustAudioProcessorEditor::openHorizontalBox(const char* label)
{
  //TODO:
}

void FaustAudioProcessorEditor::openVerticalBox(const char* label)
{
  //TODO:
}

void FaustAudioProcessorEditor::closeBox()
{
  //TODO:
}

void FaustAudioProcessorEditor::addButton(const char* label, FAUSTFLOAT* zone)
{
  //TODO:
}

void FaustAudioProcessorEditor::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
  //TODO:
}

void FaustAudioProcessorEditor::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  //TODO:
}

void FaustAudioProcessorEditor::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  //TODO:
}

void FaustAudioProcessorEditor::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  //TODO:
}

void FaustAudioProcessorEditor::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
  //TODO:
}

void FaustAudioProcessorEditor::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
  //TODO:
}

void FaustAudioProcessorEditor::declare(FAUSTFLOAT* zone, const char* key, const char* val)
{
//  if (zone == 0) {
//    // special zone 0 means group metadata
//    if (strcmp(key,"tooltip")==0) {
//      // only group tooltip are currently implemented
//      gGroupTooltip = formatTooltip(30, value);
//    }
//  } else {
//    if (strcmp(key,"size")==0) {
//      fGuiSize[zone]=atof(value);
//    }
//    else if (strcmp(key,"tooltip")==0) {
//      fTooltip[zone] = formatTooltip(30, value) ;
//    }
//    else if (strcmp(key,"unit")==0) {
//      fUnit[zone] = value ;
//    }
//    else if (strcmp(key,"scale")==0) {
//      if (strcmp(value,"log") == 0) {
//        fLogSet.insert(zone);
//      } else if (strcmp(value,"exp") == 0) {
//        fExpSet.insert(zone);
//      }
//    }
//    else if (strcmp(key,"style")==0) {
//      // else if ((strcmp(key,"style")==0) || (strcmp(key,"type")==0)) {
//      if (strcmp(value,"knob") == 0) {
//        fKnobSet.insert(zone);
//      } else if (strcmp(value,"led") == 0) {
//        fLedSet.insert(zone);
//      } else if (strcmp(value,"numerical") == 0) {
//        fNumSet.insert(zone);
//      } else {
//        const char* p = value;
//        if (parseWord(p,"radio")) {
//          fRadioDescription[zone] = string(p);
//        } else if (parseWord(p,"menu")) {
//          fMenuDescription[zone] = string(p);
//        }
//      }
//    }
//  }
}

#pragma mark FAUST metadata declarations
void FaustAudioProcessorEditor::declare(const char* key, const char* value)
{
  
}