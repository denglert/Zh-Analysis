#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include "Zh-Analyzer.h"
#include "ExRootAnalysis/ExRootTreeReader.h"



int main(int argc, const char *argv[] ) 
{

	if (argc != 2)
	{
		std::cerr << "Usage: ./Zh-Analyzer <a_Delphes_sim_file.root>" << std::endl;
		exit(1);
	}

	std::string inpFilename;
	inpFilename = argv[1];

//	TFile *f = NULL;
//	std::cout << "\nBefore open f: " << f << std::endl;
//	f = TFile::Open( inpFilename.c_str() );
//	std::cout << "\nAfter open f: " << f << std::endl;
//
//	if ( f->IsZombie() || (f == NULL) ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}
//	else {std::cout << Form("TFile %s seem to have loaded.\n", inpFilename.c_str()); }
//
//	TTree *Delphes = (TTree*)f->Get("Delphes");
//
//	Delphes->Print();

	// Create chain of root trees
	TChain chain("Delphes");
	chain.Add(inpFilename.c_str());
	
	// Create object of class ExRootTreeReader
	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
	Long64_t numberOfEntries = treeReader->GetEntries();
	
	// Get pointers to branches used in this analysis
	TClonesArray *branchJet = treeReader->UseBranch("Jet");
	TClonesArray *branchElectron = treeReader->UseBranch("Electron");
	
	// Book histograms
	TH1 *histJetPT = new TH1F("jet_pt", "jet P_{T}", 100, 0.0, 100.0);
	TH1 *histMass = new TH1F("mass", "M_{inv}(e_{1}, e_{2})", 100, 40.0, 140.0);
	
	// Loop over all events
	for(Int_t entry = 0; entry < numberOfEntries; ++entry)
	{
	  // Load selected branches with data from specified event
	  treeReader->ReadEntry(entry);
	
	  // If event contains at least 1 jet
	  if(branchJet->GetEntries() > 0)
	  {
	    // Take first jet
	    Jet *jet = (Jet*) branchJet->At(0);
	
	    // Plot jet transverse momentum
	    histJetPT->Fill(jet->PT);
	
	    // Print jet transverse momentum
		 std::cout << "Jet pt: "<<jet->PT << std::endl;
	  }
	
	  Electron *elec1, *elec2;
	
	  // If event contains at least 2 electrons
	  if(branchElectron->GetEntries() > 1)
	  {
	    // Take first two electrons
	    elec1 = (Electron *) branchElectron->At(0);
	    elec2 = (Electron *) branchElectron->At(1);


	    // Plot their invariant mass
	    histMass->Fill(((elec1->P4()) + (elec2->P4())).M());
	  }
	}
	
	// Show resulting histograms
	histJetPT->Draw();
	histMass->Draw();

	return 0;

}
