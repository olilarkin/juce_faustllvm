# FAUST LLVM JIT Module for JUCE

This is a JUCE Module for embedding the Faust LLVM JIT compiler as a JUCE AudioProcessor/AudioPluginInstance. It includes supporting classes such as a Faust syntax highlighter for the JUCE code editor.

Should work on OSX, Linux and eventually Windows. Only tested on OSX 10.9 thusfar.

THE FOLLOWING IS WORK IN PROGRESS - NEEDS TO BE CHECKED ON A FRESH SYSTEM!

See example CLI project https://github.com/CMRCYork/juce_faustllvm_test



##Building on Linux:

The following instructions are for Ubuntu 14.04LTS. Older versions and other distros will require slightly different proceedures. You need a compiler with C++11 support.

**JUCE on Linux**

Firstly, here's a shell command to install the packages required for JUCE on Linux:

sudo apt-get -y install g++ libfreetype6-dev libx11-dev libxinerama-dev libxcursor-dev mesa-common-dev libasound2-dev freeglut3-dev libxcomposite-dev

**LLVM 3.5**

Install via apt-get e.g. sudo apt-get install llvm-3.5 . NOTE: it will compile with other LLVM versions (3.1+) but you will need to adjust header/library includes accordingly and run llvm-config --libs all to get the list of all the LLVM libs for that particular version.

**FAUST (faust2 branch)**

You need to have built and installed the faust2 branch from source and it should be built against the same LLVM version as the project using the module.

sudo apt-get install libssl-dev libncurses5-dev 
git clone git://git.code.sf.net/p/faudiostream/code faust -b faust2
cd faust
make
sudo make install

##Installing Dependencies on OSX:

**LLVM 3.5**

Install via Macports e.g. sudo port install llvm-3.5 +universal . The .jucer project expects the libraries to be in /opt/local/libexec/llvm-3.5/lib . If they are elsewhere you'll have to modify the jucer project.

**FAUST (faust2 branch)**

You need to have built and installed the faust2 branch from source and it should be built against LLVM/CLANG 3.5. You will probably need libmicrohttpd, libsndfile installed as well. Consult the faust documentation/mailing list. NOTE: the macports faust2-devel is using LLVM/CLANG 3.4. 

The test project .jucer file expects to link against /usr/local/lib/libfaust.a

**libncurses**

Install via macports e.g. sudo port install ncurses +universal

The test project .jucer file expects to link against /opt/local/lib/libncurses.a

**zlib**

Install via macports  e.g. sudo port install zlib +universal

The test project .jucer file expects to link against /opt/local/lib/libz.a

**libcrypto**

Part of openssl. Install via macports e.g.  sudo port install openssl +universal

The test project .jucer file expects to link against /opt/local/lib/libcrypto.a

###JUCER settings:

**Extra Linker Flags:**
LLVM Libs: (run llvm-config --libs on command line to get list, there are a lot!)

in order to force static linking of the libraries, the full path to the the static libraries can be added in the Jucer "extra linker flags section", without a -l in front of the library name.

/usr/local/lib/libfaust.a  
/opt/local/lib/libncurses.a  
/opt/local/lib/libz.a  
/opt/local/lib/libcrypto.a  

**Header search paths:**

* /usr/local/include

**Extra Library search paths:**

* /opt/local/libexec/llvm-3.5/lib

**License:**
  
  The core of this module is heavily based on the faustgen~ Max external by GRAME.

  Written by Oliver Larkin 
  Contemporary Music Research Centre  
  Music Department  
  University of York  
  License: GPL
  
  www.cmrcyork.org | www.olilarkin.co.uk
