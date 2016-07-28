#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include "Zh-Analyzer.h"

int main(int argc, const char *argv[] ) 
{

	if (argc != 2)
	{
		std::cerr << "Usage: ./Zh-Analyzer <a_Delphes_sim_file.root>" << std::endl;
		exit(1);
	}

	std::string inpFilename;
	inpFilename = argv[1];

	TFile *f = NULL;
	std::cout << "\nBefore open f: " << f << std::endl;
	f = TFile::Open( inpFilename.c_str() );
	std::cout << "\nAfter open f: " << f << std::endl;

	if ( f->IsZombie() || (f == NULL) ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}
	else {std::cout << Form("TFile %s seem to have loaded.\n", inpFilename.c_str()); }

	TTree *Delphes = (TTree*)f->Get("Delphes");

	Delphes->Print();

	return 0;

}
