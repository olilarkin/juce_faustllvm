/*
  This file is part of the juce_faustllvm JUCE module
  Written by Oliver Larkin
  www.olilarkin.co.uk
  License: GPL

  based on Faustgen~ by GRAME

*/

/*******************************************************************************

 BEGIN_JUCE_MODULE_DECLARATION

  ID:               juce_faustllvm
  vendor:           olilarkin
  version:          0.4
  name:             LIBFAUST compiler for JUCE
  description:      FaustAudioPluginInstance and related classes for embedding the libfaust JIT compiler in JUCE Projects.
  website:          https://github.com/olilarkin/juce_faustllvm
  license:          GPL

  dependencies:     juce_core, juce_audio_processors, juce_gui_basics

  OSXLibs:          

  LinuxLibs:        faust crypto z curses LLVMLTO LLVMPasses LLVMObjCARCOpts LLVMSymbolize LLVMDebugInfoPDB LLVMDebugInfoDWARF LLVMMIRParser LLVMCoverage LLVMTableGen LLVMDlltoolDriver LLVMOrcJIT LLVMObjectYAML LLVMLibDriver LLVMOption LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen LLVMGlobalISel LLVMSelectionDAG LLVMAsmPrinter LLVMDebugInfoCodeView LLVMDebugInfoMSF LLVMX86Desc LLVMMCDisassembler LLVMX86Info LLVMX86AsmPrinter LLVMX86Utils LLVMMCJIT LLVMLineEditor LLVMInterpreter LLVMExecutionEngine LLVMRuntimeDyld LLVMCodeGen LLVMTarget LLVMCoroutines LLVMipo LLVMInstrumentation LLVMVectorize LLVMScalarOpts LLVMLinker LLVMIRReader LLVMAsmParser LLVMInstCombine LLVMTransformUtils LLVMBitWriter LLVMAnalysis LLVMProfileData LLVMObject LLVMMCParser LLVMMC LLVMBitReader LLVMCore LLVMBinaryFormat LLVMSupport LLVMDemangle
  
  WinLibs:          faust LLVMLTO.lib LLVMPasses.lib LLVMObjCARCOpts.lib LLVMSymbolize.lib LLVMDebugInfoPDB.lib LLVMDebugInfoDWARF.lib LLVMMIRParser.lib LLVMCoverage.lib LLVMTableGen.lib LLVMDlltoolDriver.lib LLVMOrcJIT.lib LLVMObjectYAML.lib LLVMLibDriver.lib LLVMOption.lib LLVMX86Disassembler.lib LLVMX86AsmParser.lib LLVMX86CodeGen.lib LLVMGlobalISel.lib LLVMSelectionDAG.lib LLVMAsmPrinter.lib LLVMDebugInfoCodeView.lib LLVMDebugInfoMSF.lib LLVMX86Desc.lib LLVMMCDisassembler.lib LLVMX86Info.lib LLVMX86AsmPrinter.lib LLVMX86Utils.lib LLVMMCJIT.lib LLVMLineEditor.lib LLVMInterpreter.lib LLVMExecutionEngine.lib LLVMRuntimeDyld.lib LLVMCodeGen.lib LLVMTarget.lib LLVMCoroutines.lib LLVMipo.lib LLVMInstrumentation.lib LLVMVectorize.lib LLVMScalarOpts.lib LLVMLinker.lib LLVMIRReader.lib LLVMAsmParser.lib LLVMInstCombine.lib LLVMTransformUtils.lib LLVMBitWriter.lib LLVMAnalysis.lib LLVMProfileData.lib LLVMObject.lib LLVMMCParser.lib LLVMMC.lib LLVMBitReader.lib LLVMCore.lib LLVMBinaryFormat.lib LLVMSupport.lib LLVMDemangle.lib 

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#define DEFAULT_FAUST_DSP_SEARCHPATH "~/Library/Application Support/pMix2/FaustNodes" // TODO:  don't do this here

#define FAUSTGEN_VERSION "0.99b" // TODO:  rename this

#if JUCE_MAC || JUCE_LINUX
  #define FAUST_DRAW_PATH "/var/tmp/"
  #define SEPARATOR '/'
#elif JUCE_WIN32
  #define FAUST_DRAW_PATH "\\faustgen-resources\\" // TODO:  rename this/don't do this here
  #define SEPARATOR '\\'
#endif

#define LLVM_OPTIMIZATION -1
#define DEFAULT_CODE "declare name \"Faust Effect\";\nimport(\"stdfaust.lib\");\nprocess = _;"

#define HTML_WRAPPER "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n\
<html>\n\
<head>\n\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n\
<title>SVG viewer</title>\n\
</head>\n\
<body style=\"background-color: white;\">\n\
<embed src=\"process.svg\" type=\"image/svg+xml\" style=\"background-color: white; width: 100%;\">\n\
</body>\n\
</html>"

#define LOG Logger::getCurrentLogger()->writeToLog

#include "source/FaustAudioPluginInstance.h"
#include "source/FaustAudioProcessorEditor.h"
#include "source/FaustAudioProcessorParameter.h"
#include "source/FaustCodeTokenizer.h"
#include "source/FaustPluginFormat.h"
// #include "source/FaustDSPWatcher.h"
// #include "source/FaustFileFilter.h"
// #include "source/FaustGenFactory.h"
