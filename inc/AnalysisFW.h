#include "classes/DelphesClasses.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include <TClonesArray.h>
#include <TH1D.h>
#include "config.h"
#include "UtilFunctions.h"
#include "GraphTools.h"

#define loopx(x, nx)               for( int x = 0; x < nx; x++)
#define loopxy(x, y, nx, ny)        for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)
#define loopxyz(x, y, z, nx, ny, nz) for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)for( int z = 0; z < nz; z++)

struct Histograms
{

	TH1D ****PtDistr;
	TH1D ****EtaDistr;
	TH1D  ***MinvDistr;
	TH1D   **mZhDistr;
	TH1D   **nObj;
};

struct Cuts
{
	double cutMuonPtMin;
	double cutMuonEtaMax;

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


// - AnalysisFW class
class AnalysisFW
{

	public:

	AnalysisFW( const char confFilePath_[] );

	void Analyzer( ExRootTreeReader* reader);
	void CreatePlots( );

	void Init();

	bool CutJet      ( Jet *jet     );
	bool CutMuon     ( Muon *mu     );
	bool CutElectron ( Electron *el );

	int nEvents;

	Binning bins;
	Cuts cuts;

	Histograms histo;
	std::string confFilePath;

};


// --- Allocation functions
template<class TYPE>
void AllocateArrayX(TYPE **&a, int n1);

template<class TYPE>
void AllocateArrayXY(TYPE ***&a, int n1, int n2);

template<class TYPE>
void AllocateArrayXYZ(TYPE ****&a, int n1, int n2, int n3);
