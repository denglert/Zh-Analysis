include Makefile.local

OBJ_Zh_Analyzer = ../lib/Zh-Analyzer.cpp.o $(OBJ_core)
OBJ_Zh_Parton_Analyzer = ../lib/Zh-Parton-Analyzer.cpp.o $(OBJ_core)
OBJ_core =  ../lib/GraphTools.cpp.o  ../lib/config.cpp.o ../lib/AnalysisFW.cpp.o ../lib/AnalysisFW-Analyzer.cpp.o ../lib/GlobalConfig.cpp.o ../lib/ResultContainer.cpp.o ../lib/AllocationUtils.cpp.o ../lib/UtilFunctions.cpp.o

../bin/Zh-Analyzer: $(OBJ_Zh_Analyzer)
	LD_LIBRARY_PATH=$(VAR_LD_LIBRARY_PATH) $(CC) $^ $(CLFLAGS) -o $@

../bin/Zh-Parton-Analyzer: $(OBJ_Zh_Parton_Analyzer)
	LD_LIBRARY_PATH=$(VAR_LD_LIBRARY_PATH) $(CC) $^ $(CLFLAGS) -o $@

all : ../bin/Zh-Analyzer ../bin/Zh-Parton-Analyzer


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
	rm    ./src/.depend_cpp
	touch ./src/.depend_cpp
