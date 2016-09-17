#ifndef GRAPHTOOLS_H
#define GRAPHTOOLS_H

#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <THStack.h>

const int Colors[5] = {2, 4, 1, 3, 9};

TStyle* TStyle_Scheme ();

template<class T>
void CreatePlot ( T *histo, const char outfig[]) ;

void CreateStackPlot (THStack *hstack, const char basename[]);


#endif
