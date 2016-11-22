#ifndef RESULTCONTAINER_H
#define RESULTCONTAINER_H

#include <map>
#include <set>
#include "UtilFunctions.h"

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

	void Allocate        ( Binning *bins         );
	void WriteToROOTFile ( TFile *f              );
	void SetTag          ( const char tag_[]     );
	void SetPrePath      ( const char prepath_[] );
	void SetLegendLabel  ( const char label_[]   ); // -- Set legend labels for all histograms
};

// --
class THStackContainer: public ResultContainer<THStack>
{
	public:
};

// -- 
class TH1DContainer: public ResultContainer<TH1D>
{
	public:
	void SetupBins  ( Binning *bins  );
};

#endif
