#include "Zh-Analyzer.h"

int main(int argc, const char *argv[] ) 
{

	if (argc != 5)
	{
		std::cerr << "Usage: ./Zh-Analyzer <tag> <comp.conf> <bin.conf> <nEvents>" << std::endl;
		exit(1);
	}

	std::string tag                = argv[1];
	std::string compConfigFilePath = argv[2];
	std::string  binConfigFilePath = argv[3];
	int nEvents 				       = atoi(argv[4]);
	
	// - Plotting style
	TStyle *myStyle = TStyle_Scheme();
	gROOT->SetStyle("myStyle");

	AnalysisFW AnaFW;
	AnaFW.nEvents            = nEvents;
	AnaFW.tag                = tag;
	AnaFW.compConfigFilePath = compConfigFilePath.c_str();
	AnaFW.binConfigFilePath  =  binConfigFilePath.c_str();

	AnaFW.Init();

//	// - Create chain of root trees
//	TChain chain("Delphes");
   for(int i=0; i < AnaFW.components.nComp; i++)
	{
		AnaFW.chain->Add( AnaFW.components.component_path[i].c_str() );
		AnaFW.Analyzer( AnaFW.chain, &AnaFW.histos[i] );
		AnaFW.chain->Reset();
	}
//
//	// -  Create object of class ExRootTreeReader
//	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);

//	AnaFW.Analyzer ( );

	AnaFW.CreateOutput();
	AnaFW.WriteOutput();

	std::cout << std::endl;
	AnaFW.MakePlots();

	return 0;

}
