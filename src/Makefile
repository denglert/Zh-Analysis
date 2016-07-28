
OBJ_Zh_Analyzer = ../lib/Zh-Analyzer.cpp.o

../bin/Zh-Analyzer: $(OBJ_Zh_Analyzer)
	$(CC) $^ $(CLFLAGS) -o $@

all : ../bin/Zh-Analyzer

####################
## -- Linking -- ###
####################

LIBDIRLINK = $(HOME)/lib/links/libs
INCDIRLINK = $(HOME)/lib/links/inc

#################
### -- C++ -- ###
#################

CC     = g++
#CC     = icc

CCFLAGS = -I../inc/ -I$(INCDIRLINK) $(ROOTCFLAGS) -MMD -MF .depend_cpp
CLFLAGS = $(ROOTLFLAGS)

# ROOT
ROOTCFLAGS = `root-config --cflags`
ROOTLFLAGS = -L/home/de3u14/lib/build/hep/root/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lm -ldl

### General compilation rule for .cpp sources
../lib/%.cpp.o : %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

include .depend_cpp
