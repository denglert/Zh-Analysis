#ifndef ANALYSISFW_H
#define ANALYSISFW_H

#include "classes/DelphesClasses.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include <TClonesArray.h>
#include "UtilFunctions.h"
#include "GraphTools.h"
#include <map>
#include <cmath>

// - AnalysisFW class
class AnalysisFW
{

	public:

	AnalysisFW( const char confFilePath_[] );
	AnalysisFW( );

	void Analyzer           ( TChain *chain, ResultContainer<TH1D> *histo );
	void PartonLevelAnalyzer( TChain *chain, ResultContainer<TH1D> *histo );


	void MakePlots( );
	void CreateOutputFile();
	void WriteOutput();

	void Init();

	bool CutJet      ( Jet *jet     );
	bool CutMuon     ( Muon *mu     );
	bool CutElectron ( Electron *el );
	bool Cuthcandidate ( TLorentzVector const &el );
	bool CutZcandidate ( TLorentzVector const &el );

	int nEvents;

	// - input/output handling
	TFile *output;
	TChain *chain;
	ExRootTreeReader *reader;

//	std::map<TObject*, PlotSettings> fPlotMap;

	Binning bins;
	Cuts cuts;
	Components components;

	std::string tag;

	TH1DContainer *histos;

	THStackContainer hstacks;
//	Histograms *histos;

	std::string  binConfigFilePath;
	std::string compConfigFilePath;

	config conf;
};


#endif
