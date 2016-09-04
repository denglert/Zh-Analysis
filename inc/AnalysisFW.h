#ifndef ANALYSISFW_H
#define ANALYSISFW_H

#include "classes/DelphesClasses.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include <TClonesArray.h>
#include "UtilFunctions.h"
#include "GraphTools.h"
#include <map>
#include <cmath>



struct PlotSettings
{
	double BottomMargin;
};

// - AnalysisFW class
class AnalysisFW
{

	public:

	AnalysisFW( const char confFilePath_[] );
	AnalysisFW( );

	void Analyzer( TChain *chain, Histograms<TH1D> *histo);
	void MakePlots( );
	void CreateOutput();
	void WriteOutput();

	void Init();

	bool CutJet      ( Jet *jet     );
	bool CutMuon     ( Muon *mu     );
	bool CutElectron ( Electron *el );

	int nEvents;

	// - input/output handling
	TFile *output;
	TChain *chain;
	ExRootTreeReader *reader;

	std::set<TObject*> fHistos;
//	std::map<TObject*, PlotSettings> fPlotMap;

	Binning bins;
	Cuts cuts;
	Components components;

	std::string tag;

	Histograms<TH1D> *histos;
//	Histograms *histos;

	std::string  binConfigFilePath;
	std::string compConfigFilePath;

	config conf;
};


#endif
