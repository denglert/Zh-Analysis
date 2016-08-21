#ifndef GRAPHTOOLS_H
#define GRAPHTOOLS_H

#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>

TStyle* TStyle_Scheme ();

void CreatePlot ( TH1D *histo, const char outfig[]) ;

#endif
