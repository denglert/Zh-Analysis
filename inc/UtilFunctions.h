#ifndef UTILFUNCTIONS_H
#define UTILFUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <TH1D.h>
#include <TFile.h>
#include <THStack.h>
#include "config.h"
#include "GraphTools.h"

#define loopx(x, nx)                 for( int x = 0; x < nx; x++)
#define loopxy(x, y, nx, ny)         for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)
#define loopxyz(x, y, z, nx, ny, nz) for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)for( int z = 0; z < nz; z++)

#define MAXNCOMPONENT 10

///
class Binning
{

	public:
	void LoadBinningConfig( config *conf );

	int nCat;
	int nMult;
	int nLevel; 

	int nCatmZh;

	std::vector< std::string > tagCatName;
	std::vector< std::string > tagLevelName;
	std::vector< std::string > tagMultName;

	std::vector< std::string > labelCatName;
	std::vector< std::string > labelLevelName;
	std::vector< std::string > labelMultName;


	std::string tag_Cat  (const int  id);
	std::string tag_Mult (const int  id);
	std::string tag_Level  (const int  id);

	std::string label_Cat  (const int  id);
	std::string label_Mult (const int  id);
	std::string label_Level  (const int  id);

//	std::string *strCatName  = NULL;
//	std::string *strLvlName  = NULL;
//	std::string *strMultName = NULL;

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

///
template <typename T>
class ResultContainer
{
	public:
	T ****PtDistr;
	T ****EtaDistr;
	T  ***MinvDistr;
	T  ***mZhDistr;
	T  ***backDistr;
	T   **nObj;

	T *nJetConstituents;
	T *ZThetaDistr;

	std::set<TObject*> fCollection;
	std::map<TObject*, PlotSettings> fPlotMap;

	std::string tag;
	std::string prepath;

	ResultContainer ( ){};
	ResultContainer ( const char tag_[], const char prepath_[] );

	void Allocate   ( Binning *bins );
	void WriteToROOTFile ( TFile *f );
	void SetTag     ( const char tag_[]     );
	void SetPrePath ( const char prepath_[] );
	void SetLegendLabel   ( const char label_[] ); // -- Set legend labels for all histograms
};

/////
class THStackContainer: public ResultContainer<THStack>
{
	public:
};

////
class TH1DContainer: public ResultContainer<TH1D>
{
	public:
	void SetupBins  ( Binning *bins  );
};

////
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

	double cutMissingETMax;
};

struct Components
{
	double lumi;
	int   nComp;

	double      component_xsec    [MAXNCOMPONENT];
	double      component_scale   [MAXNCOMPONENT];
	double      component_nEvents [MAXNCOMPONENT];
	std::string component_name    [MAXNCOMPONENT];
	std::string component_path    [MAXNCOMPONENT];
	int         component_color   [MAXNCOMPONENT];
};

enum Category { jet,     bjet,   mu          };
enum Level    { gene, genecut, reco, recocut };
enum Mult     { mono,      di                };

std::string label_Cat          ( const int id );
std::string label_Level        ( const int id );
std::string label_Multiplicity ( const int id );
std::string tag_Cat            ( const int id );
std::string tag_Multiplicity   ( const int id );
std::string tag_Level          ( const int id );

void progress_bar( double percent );

void LoadCutsConfig(    config *conf, Cuts *cuts);

// --- Allocation functions
template<class TYPE>
void AllocateArrayX(TYPE **&a, int n1);

template<class TYPE>
void AllocateArrayXY(TYPE ***&a, int n1, int n2);

template<class TYPE>
void AllocateArrayXYZ(TYPE ****&a, int n1, int n2, int n3);

#endif
