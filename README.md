# FAUST LLVM JIT Module for JUCE

This is a JUCE Module for embedding the Faust LLVM JIT compiler as a JUCE AudioProcessor/AudioPluginInstance. It includes supporting classes such as a Faust syntax highlighter for the JUCE code editor.

Should work on OSX, Linux and eventually Windows.

See example CLI project https://github.com/olilarkin/juce_faustllvm_test

##Dependencies:

**Mac Ports**

https://www.macports.org/

Mac Ports is used to build many of the dependencies. Ports should be built with the +universal variant and macosx_deployment_target should be set in /opt/local/etc/macports/macports.conf to match the OSX Deployment Target in the .jucer project. e.g.

macosx_deployment_target 10.9

the .jucer project expects ports to be installed in certain locations. If you have customized macports configuration, you may have to adjust the .jucer project in order to build.

even on a fast machine the following will take a long time to build! Be prepared to leave your computer for over an hour!

To do everything in one go you can use the following command:

*sudo port install llvm-3.5 +universal ncurses +universal zlib +universal openssl +universal*

**LLVM 3.7**

Install via Macports e.g. *sudo port install llvm-3.5 +universal*

The .jucer projects expects the libraries to be in /opt/local/libexec/llvm-3.5/lib

**libncurses**

Install via macports e.g. *sudo port install ncurses +universal*

The .jucer projects expect to link against /opt/local/lib/libncurses.a

**zlib**

Install via macports  e.g. *sudo port install zlib +universal*

The .jucer projects expect to link against /opt/local/lib/libz.a

**libcrypto**

Part of openssl. Install via macports e.g. *sudo port install openssl +universal*

The .jucer projects expect to link against /opt/local/lib/libcrypto.a

**FAUST (faust2 branch)**

http://faust.grame.fr/download/

You need to have built and installed the faust2 branch from source and it should be built against LLVM 3.5. 

If you have multiple LLVM versions installed you should run *sudo port select llvm mp-llvm-3.5* prior to building faust2

You may need to add the MacPorts include folder before building faust

export CXXFLAGS="-I/opt/local/include"

and you may want to set the deployment target to match what you have in the .jucer e.g.

export MACOSX_DEPLOYMENT_TARGET=10.9

You may need libmicrohttpd, libsndfile installed as well.

The .jucer projects expect to link against /usr/local/lib/libfaust.a

##JUCER settings:

When using the juce_faustllvm module you will need to add some things to your main .jucer project:

**Extra Linker Flags:**
LLVM Libs: (run *llvm-config --libs* on command line to get list, there are a lot!)

in order to force static linking of the libraries, the full path to the the static libraries can be added in the .jucer "extra linker flags section", without a -l in front of the library name.

/usr/local/lib/libfaust.a  
/opt/local/lib/libncurses.a  
/opt/local/lib/libz.a  
/opt/local/lib/libcrypto.a  

**Header search paths:**

/usr/local/include

**Extra Library search paths:**

/opt/local/libexec/llvm-3.5/lib

**License:**
  
The core of this module is heavily based on the faustgen~ Max external by GRAME.

Written by Oliver Larkin    
License: GPL
www.olilarkin.co.uk