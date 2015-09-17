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