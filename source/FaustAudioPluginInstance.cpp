/*
  ==============================================================================

    FaustAudioPluginInstance.cpp
    Based on Faustgen~ by GRAME
    Author:  Oliver Larkin

 
    Faustgen~ license:
    ***********************************************************************
    FAUST Architecture File
    Copyright (C) 2010-2015 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


    ************************************************************************
    ***********************************************************************

  ==============================================================================
*/

#include "FaustAudioPluginInstance.h"
#include "FaustAudioProcessorParameter.h"
#include "FaustAudioProcessorEditor.h"

FaustAudioPluginInstance::FaustAudioPluginInstance()
: fDSPfactory(nullptr)
, fDSP(nullptr)
, highlight(false)
, needsToBeCompiled(false)
, tempSourceCode(String::empty)
, lastCompilerMessage(String::empty)
{
}

FaustAudioPluginInstance::~FaustAudioPluginInstance()
{
  freeDSP();
  
  if (fDSPfactory != nullptr)
    fDSPfactory->removeInstance(this);
}

void FaustAudioPluginInstance::fillInPluginDescription (PluginDescription& description) const
{
  if (description.fileOrIdentifier.length())
    description.name = File(description.fileOrIdentifier).getFileName();
  else
    description.name = "Faust Node";

  description.descriptiveName = getDescription();
  description.pluginFormatName = "FAUST";
  description.category = "";
  description.manufacturerName = getAuthor();
  description.version = "";
  //description.fileOrIdentifier = String::empty; //TODO:? Keep link to file?
  //description.lastFileModTime = Time(0);
  description.isInstrument = false;
  description.hasSharedContainer = false;

  if(fDSP != nullptr) {
    description.numInputChannels = fDSP->getNumInputs();
    description.numOutputChannels = fDSP->getNumOutputs();
  }
  else {
    description.numInputChannels = 0;
    description.numOutputChannels = 0;
  }
}

//static
void FaustAudioPluginInstance::fillInitialInPluginDescription (PluginDescription& description)
{
  description.name = "Faust Node";
  description.descriptiveName = "";
  description.pluginFormatName = "FAUST";
  description.category = "";
  description.manufacturerName = "";
  description.version = "";
  description.fileOrIdentifier = String::empty;
  description.lastFileModTime = Time(0);
  description.isInstrument = false;
  description.hasSharedContainer = false;
  description.numInputChannels = 1;
  description.numOutputChannels = 1;
}

void FaustAudioPluginInstance::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  if (!fDSP)
    createDSP();
  
  fDSP->init(sampleRate);
  setPlayConfigDetails(fDSP->getNumInputs(), fDSP->getNumOutputs(), sampleRate, samplesPerBlock);
}

void FaustAudioPluginInstance::releaseResources()
{
}

void FaustAudioPluginInstance::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
  jassert (! isUsingDoublePrecision());
  jassert (sizeof(FAUSTFLOAT) == 4); //TODO: if FAUSTFLOAT == 8 allways need to process the faust dsp with double precision
  process (buffer, midiMessages);
}

void FaustAudioPluginInstance::processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiMessages)
{
  jassert (isUsingDoublePrecision());
  jassert (sizeof(FAUSTFLOAT) == 8); //TODO: if FAUSTFLOAT == 4 allways need to process the faust dsp with single precision
  process (buffer, midiMessages);
}

template <typename FloatType>
void FaustAudioPluginInstance::process (AudioBuffer<FloatType>& buffer,MidiBuffer& midiMessages)
{
  const ScopedLock lock(fDSPfactory->fDSPMutex);
  
  if (fDSP != nullptr)
    fDSP->compute(buffer.getNumSamples(), (FAUSTFLOAT**)buffer.getArrayOfReadPointers(), (FAUSTFLOAT**)buffer.getArrayOfWritePointers());
}


void FaustAudioPluginInstance::reset()
{
}

bool FaustAudioPluginInstance::hasEditor() const
{
  return true;
}

AudioProcessorEditor* FaustAudioPluginInstance::createEditor()
{
  FaustAudioProcessorEditor* editor = new FaustAudioProcessorEditor(*this, *fDSP);
  
  return editor;
}

const String FaustAudioPluginInstance::getName() const
{
  if(fJSONInterface["name"].toString().length())
  {
    return fJSONInterface["name"].toString();
  }
  else
    return "Faust Node";
}

const String FaustAudioPluginInstance::getInputChannelName (int channelIndex) const
{
  return "unknown";
}

const String FaustAudioPluginInstance::getOutputChannelName (int channelIndex) const
{
  return "unknown";
}

bool FaustAudioPluginInstance::isInputChannelStereoPair (int index) const
{
  return false;
}

bool FaustAudioPluginInstance::isOutputChannelStereoPair (int index) const
{
  return false;
}

bool FaustAudioPluginInstance::supportsDoublePrecisionProcessing() const
{
  return sizeof(FAUSTFLOAT) == 8;
}

bool FaustAudioPluginInstance::acceptsMidi() const
{
  return false;
}

bool FaustAudioPluginInstance::producesMidi() const
{
  return false;
}

bool FaustAudioPluginInstance::silenceInProducesSilenceOut() const
{
  return true;
}

double FaustAudioPluginInstance::getTailLengthSeconds() const
{
  return 0.;
}

int FaustAudioPluginInstance::getNumPrograms()
{
  return 1;
}

int FaustAudioPluginInstance::getCurrentProgram()
{
  return 0;
}

void FaustAudioPluginInstance::setCurrentProgram (int index)
{
}

const String FaustAudioPluginInstance::getProgramName (int index)
{
  return "Default";
}

void FaustAudioPluginInstance::changeProgramName (int index, const String& newName)
{
}

//TODO: also need to store the state of the parameters
void FaustAudioPluginInstance::getStateInformation (MemoryBlock& destData)
{
  XmlElement xml ("FAUSTGEN");
  fDSPfactory->getStateInformation(xml);
  copyXmlToBinary (xml, destData);
}

void FaustAudioPluginInstance::setStateInformation (const void* data, int sizeInBytes)
{
  ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
  
  if (xmlState != nullptr)
  {
    if (xmlState->hasTagName ("FAUSTGEN"))
    {
      fDSPfactory->freeDSPFactory();
      fDSPfactory->setStateInformation(*xmlState);
    }
  }
  
  createDSP();
}

void FaustAudioPluginInstance::createDSP()
{
  const ScopedLock lock(fDSPfactory->fDSPMutex);

  fDSP = fDSPfactory->createDSPAux(this);
  jassert(fDSP);
  
  // Initialize User Interface
  fDSP->buildUserInterface(this);

  JSON::parse(fDSPfactory->getJSON(), fJSONInterface);
  
  // Initialize at the system's sampling rate
  if (getSampleRate() == 0)
    fDSP->init(44100.);
  else
    fDSP->init(getSampleRate());
  
  updateHostDisplay();
}

void FaustAudioPluginInstance::freeDSP()
{
  delete fDSP;
  fDSP = nullptr;
}

bool FaustAudioPluginInstance::allocateFactory(const String& effectName, const File& libraryPath, const File& svgPath)
{
  bool res = false;
  
  if (FaustgenFactory::gFactoryMap.find(effectName.toStdString()) != FaustgenFactory::gFactoryMap.end())
  {
    fDSPfactory = FaustgenFactory::gFactoryMap[effectName];
  }
  else
  {
    fDSPfactory = new FaustgenFactory(effectName, libraryPath, svgPath);
    FaustgenFactory::gFactoryMap[effectName] = fDSPfactory;
    res = true;
  }
  
  fDSPfactory->addInstance(this);
  return res;
}

void FaustAudioPluginInstance::setSourceCode(String sourceCode, bool compile)
{
  if (compile)
  {
    fDSPfactory->updateSourceCode(sourceCode, this);
    needsToBeCompiled = false;
    tempSourceCode = "";
  }
  else
  {
    needsToBeCompiled = true;
    tempSourceCode = sourceCode;
  }
}

String FaustAudioPluginInstance::getSourceCode()
{
  if (tempSourceCode.length())
    return tempSourceCode;
  else
    return fDSPfactory->getSourcecode();
}

void FaustAudioPluginInstance::highlightON(const String& error)
{
  lastCompilerMessage = error;
  highlight = true;
}

void FaustAudioPluginInstance::highlightOFF()
{
  highlight = false;
}

void FaustAudioPluginInstance::openTabBox(const char* label)
{
  //TODO:
}

void FaustAudioPluginInstance::openHorizontalBox(const char* label)
{
  //TODO:
}

void FaustAudioPluginInstance::openVerticalBox(const char* label)
{
  //TODO:
}

void FaustAudioPluginInstance::closeBox()
{
  //TODO:
}

void FaustAudioPluginInstance::addButton(const char* label, FAUSTFLOAT* zone)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeBool, 0, 0, 1, 1, "", zone));
}

void FaustAudioPluginInstance::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeBool, 0, 0, 1, 1, "", zone));
}

void FaustAudioPluginInstance::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeFloat, init, min, max, step, "", zone));
}

void FaustAudioPluginInstance::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeFloat, init, min, max, step, "", zone));
}

void FaustAudioPluginInstance::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
  addParameter(new FaustAudioProcessorParameter(String(label), FaustAudioProcessorParameter::kTypeFloat, init, min, max, step, "", zone));
}

void FaustAudioPluginInstance::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
  //TODO:
}

void FaustAudioPluginInstance::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
  //TODO:
}

void FaustAudioPluginInstance::addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
{
    //TODO:
}

void FaustAudioPluginInstance::initialize(const File &libraryPath, const File &svgPath)
{
  // Empty (= no name) FaustAudioPluginInstance will be internally separated as groups with different names
  if (fDSPfactory == nullptr)
  {
    String effectName;
    effectName << "FaustgenFactory-" << FaustgenFactory::gFaustCounter;
    allocateFactory(effectName.toStdString(), libraryPath, svgPath);
  }
  
  fDSPfactory->addLibraryPath(libraryPath);
}

const String FaustAudioPluginInstance::getAuthor() const
{
  if(fJSONInterface["author"].toString().length())
  {
    return fJSONInterface["author"].toString();
  }
  else
    return "Author Not Defined";
}

const String FaustAudioPluginInstance::getDescription() const
{
  if(fJSONInterface["description"].toString().length())
  {
    return fJSONInterface["description"].toString();
  }
  else
    return "Description Not Defined";
}
