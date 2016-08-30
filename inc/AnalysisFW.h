#ifndef ANALYSISFW_H
#define ANALYSISFW_H

#include "classes/DelphesClasses.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include <TClonesArray.h>
#include <TH1D.h>
#include "config.h"
#include "UtilFunctions.h"
#include "GraphTools.h"
#include <set>
#include <map>
#include <cmath>

#define loopx(x, nx)               for( int x = 0; x < nx; x++)
#define loopxy(x, y, nx, ny)        for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)
#define loopxyz(x, y, z, nx, ny, nz) for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)for( int z = 0; z < nz; z++)

struct Histograms
{

	TH1D ****PtDistr;
	TH1D ****EtaDistr;
	TH1D  ***MinvDistr;
	TH1D  ***mZhDistr;
	TH1D   **nObj;

	TH1D *nJetConstituents;
	TH1D *ZThetaDistr;
};

struct Components
{
	nComp;
	double      component_xsec[10];
	std::string component_name[10];
	std::string component_path[10];
};

struct Cuts
{
	double cutMuonPtMin;
	double cutMuonEtaMax;

	double cutElectronPtMin;
	double cutElectronEtaMax;

	double cutJetPtMin;
	double cutJetEtaMax;

	double cutZMinvMin;
	double cutZMinvMax;

	double cutZPtMin;
	double cutZPtMax;

	double cuthMinvMin;
	double cuthMinvMax;

};

struct Binning
{
	int nCat;
	int nMult;
	int nLevel; 

	int nCatmZh;

	double nPtBins;
	double PtMin;
	double PtMax;

	double nMinvBins;
	double MinvMin;
	double MinvMax;

	double nmZhBins;
	double mZhMin;
	double mZhMax;

	double nEtaBins;
	double EtaMin;
	double EtaMax;

	double nObjBins;
	double ObjMin;
	double ObjMax;
	  	
};

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

	void Analyzer( ExRootTreeReader* reader);
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
	TChain chain;
	ExRootTreeReader *reader;

	std::set<TObject*> fHistos;
//	std::map<TObject*, PlotSettings> fPlotMap;

	Binning bins;
	Cuts cuts;
	Components components;

	std::string tag;

	Histograms histo;
	std::string  binConfFilePath;
	std::string compConfFilePath;

	config conf;
};


// --- Allocation functions
template<class TYPE>
void AllocateArrayX(TYPE **&a, int n1);

template<class TYPE>
void AllocateArrayXY(TYPE ***&a, int n1, int n2);

template<class TYPE>
void AllocateArrayXYZ(TYPE ****&a, int n1, int n2, int n3);

#endif
