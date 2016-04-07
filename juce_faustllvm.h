/*
  This file is part of the juce_faustllvm JUCE module
  Written by Oliver Larkin
  Contemporary Music Research Centre
  Music Department, University of York
  License: GPL
  
  based on Faustgen~ by GRAME
  
*/

/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               juce_faustllvm
  vendor:           olilarkin
  version:          0.2
  name:             FAUST LLVM JIT compiler for JUCE
  description:      FaustAudioPluginInstance and related classes for embedding the Faust LLVM compiler in JUCE Projects.
  website:          https://github.com/olilarkin/juce_faustllvm
  license:          GPL

  dependencies:     juce_core, juce_audio_processors, juce_gui_basics
  
  OSXLibs:          faust crypto z curses LLVMLTO LLVMObjCARCOpts LLVMLinker LLVMBitWriter LLVMIRReader LLVMBPFCodeGen LLVMBPFDesc LLVMBPFInfo LLVMBPFAsmPrinter LLVMAMDGPUCodeGen LLVMAMDGPUAsmParser LLVMAMDGPUUtils LLVMAMDGPUDesc LLVMAMDGPUInfo LLVMAMDGPUAsmPrinter LLVMSystemZDisassembler LLVMSystemZCodeGen LLVMSystemZAsmParser LLVMSystemZDesc LLVMSystemZInfo LLVMSystemZAsmPrinter LLVMHexagonDisassembler LLVMHexagonCodeGen LLVMHexagonDesc LLVMHexagonInfo LLVMNVPTXCodeGen LLVMNVPTXDesc LLVMNVPTXInfo LLVMNVPTXAsmPrinter LLVMCppBackendCodeGen LLVMCppBackendInfo LLVMMSP430CodeGen LLVMMSP430Desc LLVMMSP430Info LLVMMSP430AsmPrinter LLVMXCoreDisassembler LLVMXCoreCodeGen LLVMXCoreDesc LLVMXCoreInfo LLVMXCoreAsmPrinter LLVMMipsDisassembler LLVMMipsCodeGen LLVMMipsAsmParser LLVMMipsDesc LLVMMipsInfo LLVMMipsAsmPrinter LLVMAArch64Disassembler LLVMAArch64CodeGen LLVMAArch64AsmParser LLVMAArch64Desc LLVMAArch64Info LLVMAArch64AsmPrinter LLVMAArch64Utils LLVMARMDisassembler LLVMARMCodeGen LLVMARMAsmParser LLVMARMDesc LLVMARMInfo LLVMARMAsmPrinter LLVMPowerPCDisassembler LLVMPowerPCCodeGen LLVMPowerPCAsmParser LLVMPowerPCDesc LLVMPowerPCInfo LLVMPowerPCAsmPrinter LLVMSparcDisassembler LLVMSparcCodeGen LLVMSparcAsmParser LLVMSparcDesc LLVMSparcInfo LLVMSparcAsmPrinter LLVMMIRParser LLVMAsmParser LLVMLibDriver LLVMOption LLVMDebugInfoPDB LLVMTableGen LLVMOrcJIT LLVMLineEditor LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen LLVMSelectionDAG LLVMAsmPrinter LLVMX86Desc LLVMMCDisassembler LLVMX86Info LLVMX86AsmPrinter LLVMX86Utils LLVMMCJIT LLVMDebugInfoDWARF LLVMPasses LLVMipo LLVMVectorize LLVMInterpreter LLVMExecutionEngine LLVMRuntimeDyld LLVMCodeGen LLVMTarget LLVMScalarOpts LLVMProfileData LLVMObject LLVMMCParser LLVMBitReader LLVMInstCombine LLVMInstrumentation LLVMTransformUtils LLVMipa LLVMMC LLVMAnalysis LLVMCore LLVMSupport
  LinuxLibs:        faust crypto z curses LLVMLTO LLVMObjCARCOpts LLVMLinker LLVMBitWriter LLVMIRReader LLVMBPFCodeGen LLVMBPFDesc LLVMBPFInfo LLVMBPFAsmPrinter LLVMAMDGPUCodeGen LLVMAMDGPUAsmParser LLVMAMDGPUUtils LLVMAMDGPUDesc LLVMAMDGPUInfo LLVMAMDGPUAsmPrinter LLVMSystemZDisassembler LLVMSystemZCodeGen LLVMSystemZAsmParser LLVMSystemZDesc LLVMSystemZInfo LLVMSystemZAsmPrinter LLVMHexagonDisassembler LLVMHexagonCodeGen LLVMHexagonDesc LLVMHexagonInfo LLVMNVPTXCodeGen LLVMNVPTXDesc LLVMNVPTXInfo LLVMNVPTXAsmPrinter LLVMCppBackendCodeGen LLVMCppBackendInfo LLVMMSP430CodeGen LLVMMSP430Desc LLVMMSP430Info LLVMMSP430AsmPrinter LLVMXCoreDisassembler LLVMXCoreCodeGen LLVMXCoreDesc LLVMXCoreInfo LLVMXCoreAsmPrinter LLVMMipsDisassembler LLVMMipsCodeGen LLVMMipsAsmParser LLVMMipsDesc LLVMMipsInfo LLVMMipsAsmPrinter LLVMAArch64Disassembler LLVMAArch64CodeGen LLVMAArch64AsmParser LLVMAArch64Desc LLVMAArch64Info LLVMAArch64AsmPrinter LLVMAArch64Utils LLVMARMDisassembler LLVMARMCodeGen LLVMARMAsmParser LLVMARMDesc LLVMARMInfo LLVMARMAsmPrinter LLVMPowerPCDisassembler LLVMPowerPCCodeGen LLVMPowerPCAsmParser LLVMPowerPCDesc LLVMPowerPCInfo LLVMPowerPCAsmPrinter LLVMSparcDisassembler LLVMSparcCodeGen LLVMSparcAsmParser LLVMSparcDesc LLVMSparcInfo LLVMSparcAsmPrinter LLVMMIRParser LLVMAsmParser LLVMLibDriver LLVMOption LLVMDebugInfoPDB LLVMTableGen LLVMOrcJIT LLVMLineEditor LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen LLVMSelectionDAG LLVMAsmPrinter LLVMX86Desc LLVMMCDisassembler LLVMX86Info LLVMX86AsmPrinter LLVMX86Utils LLVMMCJIT LLVMDebugInfoDWARF LLVMPasses LLVMipo LLVMVectorize LLVMInterpreter LLVMExecutionEngine LLVMRuntimeDyld LLVMCodeGen LLVMTarget LLVMScalarOpts LLVMProfileData LLVMObject LLVMMCParser LLVMBitReader LLVMInstCombine LLVMInstrumentation LLVMTransformUtils LLVMipa LLVMMC LLVMAnalysis LLVMCore LLVMSupport
  
 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#define FAUSTFLOAT float

#define DEFAULT_FAUST_DSP_SEARCHPATH "~/Library/Application Support/pMix2/FaustNodes"

#define FAUSTGEN_VERSION "0.99b"

#if JUCE_MAC || JUCE_LINUX
  #define FAUST_DRAW_PATH "/var/tmp/"
  #define SEPARATOR '/'
#elif JUCE_WIN32
  #define FAUST_DRAW_PATH "\\faustgen-resources\\"
  #define SEPARATOR '\\'
#endif

#define LLVM_OPTIMIZATION 3
//#define DEFAULT_CODE "declare name \"Faust Effect\";\n\ngain = hslider(\"gain\", 1., 0., 1., 0.);\nprocess = _*(gain);"
#define DEFAULT_CODE "//declare name \"Faust Node\";\n\nimport(\"math.lib\");\nimport(\"maxmsp.lib\");\nimport(\"music.lib\");\nimport(\"oscillator.lib\");\nimport(\"reduce.lib\");\nimport(\"filter.lib\");\nimport(\"effect.lib\");\n\nprocess=_,_;"

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
