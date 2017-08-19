/*
  ==============================================================================

    FaustFileFilter.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#pragma once

#include <juce_core/juce_core.h>

class FaustDSPFileFilter : public FileFilter
{
public:
  FaustDSPFileFilter()
  : FileFilter("Faust DSP file")
  {
  }
  
  ~FaustDSPFileFilter()
  {
  }
  
  bool isFileSuitable (const File &file) const override
  {
    //todo contains process
    if(file.getFileExtension() == ".dsp")
      return true;
    else
      return false;
  }
  
  bool isDirectorySuitable (const File &file) const override
  {
    return false;
  }
};

class FaustLIBFileFilter : public FileFilter
{
public:
  FaustLIBFileFilter()
  : FileFilter("Faust library file")
  {
  }
  
  ~FaustLIBFileFilter()
  {
  }
  
  bool isFileSuitable (const File &file) const override
  {
    if(file.getFileExtension() == ".lib")
      return true;
    else
      return false;
  }
  
  bool isDirectorySuitable (const File &file) const override
  {
    return false;
  }
};



