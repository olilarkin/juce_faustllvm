/*
  ==============================================================================

    FaustAudioPluginInstance.h
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

#ifndef FaustAudioPluginInstance_H_INCLUDED
#define FaustAudioPluginInstance_H_INCLUDED

#include <juce_audio_processors/juce_audio_processors.h>

#include "FaustGenFactory.h"
#include "faust/gui/UI.h"

#include "FaustAudioProcessorEditor.h"

class FaustAudioPluginInstance  : public AudioPluginInstance
                                , public UI
{
public:
  FaustAudioPluginInstance();
  ~FaustAudioPluginInstance();
  
// AudioPluginInstance
  void fillInPluginDescription (PluginDescription& description) const override;
  static void fillInitialInPluginDescription (PluginDescription& description);

// AudioProcessor
  void prepareToPlay (double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;
  void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
  void reset() override;
  
  bool hasEditor() const override;
  AudioProcessorEditor* createEditor() override;
  
  const String getName() const override;
  
  const String getInputChannelName (int channelIndex) const override;
  const String getOutputChannelName (int channelIndex) const override;
  bool isInputChannelStereoPair (int index) const override;
  bool isOutputChannelStereoPair (int index) const override;
  
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool silenceInProducesSilenceOut() const override;
  double getTailLengthSeconds() const override;
  
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram (int index) override;
  const String getProgramName (int index) override;
  void changeProgramName (int index, const String& newName) override;
  
  void getStateInformation (MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;
  
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
  
// Unique
  void createDSP();
  void freeDSP();
  
  void setSourceCode(String sourceCode, bool compile);
  String getSourceCode();
  FaustgenFactory* getFactory() { return fDSPfactory; }
  llvm_dsp* getDSP() { return fDSP; }
  void highlightON(const String& error);
  void highlightOFF();
  
  const String getAuthor() const;
  const String getDescription() const;
  
  const bool getHighlight() { return highlight; }
  const String getCompilerMessage() { return lastCompilerMessage; }

  //MUST CALL AFTER CREATION
  void initialize(const File &libraryPath, const File& svgPath = File::nonexistent);
  
private:
  bool allocateFactory(const String& effectName, const File& libraryPath, const File& svgPath = File::nonexistent);

  var fJSONInterface;
  FaustgenFactory* fDSPfactory;
  llvm_dsp* fDSP;
  bool highlight;
  String tempSourceCode;
  String lastCompilerMessage;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustAudioPluginInstance)
};


#endif  // FaustAudioPluginInstance_H_INCLUDED
