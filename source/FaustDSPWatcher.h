/*
  ==============================================================================

    FaustDSPWatcher.h
    Author:  Oliver Larkin

  ==============================================================================
*/

#pragma once

#include <juce_core/juce_core.h>

class FaustDSPWatcher : public Timer
{
public:
  FaustDSPWatcher(File _file)
  : file(_file)
  , prevModificationTime(0)
  {
    startTimer(1000);
  }
  
  ~FaustDSPWatcher()
  {
  }
  
  void timerCallback() override
  {
    Time lastModified = file.getLastModificationTime();
    
    if(lastModified > prevModificationTime)
    {
      prevModificationTime = lastModified;
    }
  }
  
private:
  File file;
  Time prevModificationTime;
};


