/*
  ==============================================================================

    FaustPluginFormat.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#pragma once

#include "FaustAudioPluginInstance.h"

class FaustPluginFormat : public AudioPluginFormat
{
private:
  File faustLibraryPath;
  File svgPath;

public:
  FaustPluginFormat(const File& faustLibraryPath, const File& svgPath = File::nonexistent)
  : faustLibraryPath(faustLibraryPath)
  , svgPath(svgPath)
  {
  }
  
  ~FaustPluginFormat()
  {
  }

  void getAllTypes (OwnedArray <PluginDescription>& results)
  {
    PluginDescription* desc = new PluginDescription();
    FaustAudioPluginInstance::fillInitialInPluginDescription(*desc);
    
    results.add(desc);    
  }

  String getName() const override
  {
    return "FAUST";
  }
  
  bool fileMightContainThisPluginType (const String& fileOrIdentifier) override
  {
    if(fileOrIdentifier == String::empty)
      return true;
    
    const File f (File::createFileWithoutCheckingPath (fileOrIdentifier));
    return f.existsAsFile() && f.hasFileExtension (".dsp");
  }
  
  FileSearchPath getDefaultLocationsToSearch() override
  {
    return FileSearchPath(DEFAULT_FAUST_DSP_SEARCHPATH);
  }
  
  bool canScanForPlugins() const override
  {
    return true;
  }
  
  void findAllTypesForFile (OwnedArray <PluginDescription>& results, const String& fileOrIdentifier) override
  {
    if (! fileMightContainThisPluginType (fileOrIdentifier))
      return;
    
    PluginDescription desc;
    desc.fileOrIdentifier = fileOrIdentifier;
    desc.uid = 0;
    
    ScopedPointer<FaustAudioPluginInstance> instance (dynamic_cast<FaustAudioPluginInstance*> (createInstanceFromDescription (desc, 44100., -1 /* so we don't compile*/)));
    
    if (instance == nullptr)
      return;
    
    if (instance->getHighlight())
      return;
    
    instance->fillInPluginDescription (desc);
    
    results.add (new PluginDescription (desc));
  }
  
  bool doesPluginStillExist (const PluginDescription& desc) override
  {
    return File::createFileWithoutCheckingPath (desc.fileOrIdentifier).exists();
  }
  
  String getNameOfPluginFromIdentifier (const String& fileOrIdentifier) override
  {
    return fileOrIdentifier;
  }
  
  bool pluginNeedsRescanning (const PluginDescription& desc) override
  {
    return File (desc.fileOrIdentifier).getLastModificationTime() != desc.lastFileModTime;
  }
  
  StringArray searchPathsForPlugins (const FileSearchPath& directoriesToSearch, const bool recursive, bool allowPluginsWhichRequireAsynchronousInstantiation = false) override
  {
    StringArray results;

    for (int j = 0; j < directoriesToSearch.getNumPaths(); ++j)
      recursiveFileSearch (results, directoriesToSearch[j], recursive);

    return results;
  }
  
  void recursiveFileSearch (StringArray& results, const File& dir, const bool recursive)
  {
    DirectoryIterator iter (dir, false, "*", File::findFilesAndDirectories);
    
    while (iter.next())
    {
      const File f (iter.getFile());
      bool isPlugin = false;
      
      if (fileMightContainThisPluginType (f.getFullPathName()))
      {
        isPlugin = true;
        results.add (f.getFullPathName());
      }
      
      if (recursive && (! isPlugin) && f.isDirectory())
        recursiveFileSearch (results, f, true);
    }
  }
  
private:
  void createPluginInstance (const PluginDescription& desc, double initialSampleRate, int initialBufferSize, void* userData, void (*callback) (void*, AudioPluginInstance*, const String&)) override
  {
    FaustAudioPluginInstance* result = nullptr;
    
    //This means we are in the scanning phase... we don't want to compile all the .dsps on load
    if (initialBufferSize == -1)
    {
      if (fileMightContainThisPluginType (desc.fileOrIdentifier))
      {
        result = new FaustAudioPluginInstance();
      }
    }
    else
    {
      result = new FaustAudioPluginInstance();
      
      result->initialize(faustLibraryPath, svgPath);
      
      if(desc.fileOrIdentifier != String::empty && fileMightContainThisPluginType (desc.fileOrIdentifier))
      {
        File dspFile = File(desc.fileOrIdentifier);
        
        result->getFactory()->addLibraryPath(dspFile.getParentDirectory());
        result->getFactory()->updateSourceCode(dspFile.loadFileAsString(), result);
      }
      
      result->prepareToPlay(initialSampleRate, initialBufferSize);
    }
    
    callback (userData, result, result == nullptr ? NEEDS_TRANS ("Problem creating FAUST Plugin Instance") : String());
  }
  
  bool requiresUnblockedMessageThreadDuringCreation (const PluginDescription&) const noexcept override
  {
    return false;
  }
  
};



