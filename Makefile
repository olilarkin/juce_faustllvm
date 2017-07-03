LLVM_CONFIG ?= $(lastword $(wildcard /usr/bin/llvm-config* /opt/local/bin/llvm-config* /usr/local/bin/llvm-config*) $(shell which llvm-config 2> /dev/null))
LLVM_LIBS=$(patsubst -l%,%,$(shell $(LLVM_CONFIG) --libs))

juce_faustllvm.h : juce_faustllvm.h.in
	sed "s/{{llvm_libs}}/$(LLVM_LIBS)/" $< > $@

all : juce_faustllvm.h
.PHONY : all
