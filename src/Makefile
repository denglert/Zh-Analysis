include Makefile.local

### --- Objects --- ###
OBJ_$(ANALYSIS) = ../lib/Analysis-$(ANALYSIS).cpp.o $(OBJ_core)
OBJ_core =  ../lib/ResultContainer.cpp.o ../lib/AllocationUtils.cpp.o ../lib/UtilFunctions.cpp.o ../lib/GraphTools.cpp.o  ../lib/config.cpp.o ../lib/GlobalConfig.cpp.o  $(OBJ_AnaFW)
OBJ_AnaFW = ../lib/AnalysisFW.cpp.o ../lib/AnalysisFW-ObjSelection.cpp.o ../lib/RunAnalysis.cpp.o

### --- Binary --- ###
../bin/RunAnalysis-$(ANALYSIS): $(OBJ_$(ANALYSIS))
	LD_LIBRARY_PATH=$(VAR_LD_LIBRARY_PATH) $(CC) $^ $(CLFLAGS) -o $@

all : ../bin/RunAnalysis-$(ANALYSIS)

#################
### -- C++ -- ###
#################

CC     = g++
#CC     = icc

C++11   = -std=c++11
#C++11   =
WALL    = -Wall

CCFLAGS = -I../inc/ -I$(INCDIRLINK) $(ROOTCFLAGS) $(C++11) -MMD -MF .depend_cpp
CLFLAGS = $(DELPHES_LFLAGS) $(ROOTLFLAGS) 

# Delphes flags
DELPHES_LFLAGS = -L$(LIBDIRLINK) -lDelphes

# ROOT flags
ROOTCFLAGS = `root-config --cflags`

### General compilation rule for .cpp sources
../lib/%.cpp.o : %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

include .depend_cpp

clean : 
	rm ../lib/*
	rm    .depend_cpp
	touch .depend_cpp
