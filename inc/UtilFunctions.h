#ifndef UTILFUNCTIONS_H
#define UTILFUNCTIONS_H

#include <string>
#include <iostream>
#include <set>
#include <TH1D.h>
#include "config.h"

#define loopx(x, nx)               for( int x = 0; x < nx; x++)
#define loopxy(x, y, nx, ny)        for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)
#define loopxyz(x, y, z, nx, ny, nz) for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)for( int z = 0; z < nz; z++)


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

template <typename T>
struct Histograms
{

	T ****PtDistr;
	T ****EtaDistr;
	T  ***MinvDistr;
	T  ***mZhDistr;
	T   **nObj;

	T *nJetConstituents;
	T *ZThetaDistr;
	void Setup( Histograms *histo, Binning *bins, std::string tag, std::set<TObject*> *fHistos);
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

struct Components
{
	int nComp;
	double      component_xsec[10];
	std::string component_name[10];
	std::string component_path[10];
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



void LoadBinningConfig( config *conf, Binning *bins);
void LoadCutsConfig(    config *conf, Cuts *cuts);

// --- Allocation functions
template<class TYPE>
void AllocateArrayX(TYPE **&a, int n1);

template<class TYPE>
void AllocateArrayXY(TYPE ***&a, int n1, int n2);

template<class TYPE>
void AllocateArrayXYZ(TYPE ****&a, int n1, int n2, int n3);

#endif
