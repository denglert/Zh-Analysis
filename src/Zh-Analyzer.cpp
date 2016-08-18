#include "Zh-Analyzer.h"

int main(int argc, const char *argv[] ) 
{

	if (argc != 4)
	{
		std::cerr << "Usage: ./Zh-Analyzer <a_Delphes_sim_file.root> <config.conf> <nEvents>" << std::endl;
		exit(1);
	}

	std::string inpFilename  = argv[1];
	std::string confFilePath = argv[2];
	int nEvents 				 = atoi(argv[3]);
	
	// - Plotting style
	TStyle *myStyle = TStyle_Scheme();
	gROOT->SetStyle("myStyle");

	AnalysisFW AnaFW( confFilePath.c_str() );
	AnaFW.nEvents = nEvents;

	// - Create chain of root trees
	TChain chain("Delphes");
	chain.Add(inpFilename.c_str());

	// -  Create object of class ExRootTreeReader
	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);

	AnaFW.Analyzer (treeReader);

	AnaFW.CreatePlots();

	return 0;

}
