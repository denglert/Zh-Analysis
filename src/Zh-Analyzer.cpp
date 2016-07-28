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
	TStyle* myStyle = new TStyle("myStyle","My own Root Style");
	
//	myStyle->SetTitleSize(0.3); 
//	myStyle->SetTitleX(0.3); 
	myStyle->SetTitleSize(0.04,"xy"); 
//	myStyle->SetLabelSize(0.06,"xy"); 
	gROOT->SetStyle("myStyle");


	// Create chain of root trees
	TChain chain("Delphes");
	chain.Add(inpFilename.c_str());
	
	// Create object of class ExRootTreeReader
	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
	Long64_t numberOfEntries = treeReader->GetEntries();
	
	// Get pointers to branches used in this analysis
	TClonesArray *branchJet = treeReader->UseBranch("Jet");
	TClonesArray *branchMuon = treeReader->UseBranch("Muon");
	
	// Book histograms
	TH1 *histo_m_inv_jj     = new TH1F("m_inv_jj", "", 300, 0.0, 300.0);
	TH1 *histo_m_inv_mumu   = new TH1F("m_inv_mumu", "", 100, 40.0, 140.0);
	TH1 *histo_m_inv_mumujj = new TH1F("m_inv_mumujj", "", 100, 0.0, 1000.0);
	TH1 *histo_pt_mumu      = new TH1F("pt_mumu", "", 100, 0.0, 1000.0);
	
	Muon *mu_A;
	Muon *mu_B;
	Jet *jet_A;
	Jet *jet_B;
	TLorentzVector p_mumu; 
	TLorentzVector p_jj; 
	TLorentzVector p_mumujj; 

	// Loop over all events
	for(Int_t entry = 0; entry < numberOfEntries; ++entry)
	{

	  // Load selected branches with data from specified event
	  treeReader->ReadEntry(entry);
	
	  // If event contains at least 1 jet
	  if(branchJet->GetEntries() > 1)
	  {

	    // Take first jet
	    jet_A = (Jet*) branchJet->At(0);
	    jet_B = (Jet*) branchJet->At(1);

		 p_jj = jet_A->P4()+jet_B->P4();
	
	    // Plot jet transverse momentum
	    histo_m_inv_jj->Fill( p_jj.M() );
	  }
	
	
	  // If event contains at least 2 electrons
	  if(branchMuon->GetEntries() > 1)
	  {
	    // Take first two electrons
	    mu_A = (Muon *) branchMuon->At(0);
	    mu_B = (Muon *) branchMuon->At(1);

		 p_mumu = mu_A->P4()+mu_B->P4();

	    // Plot their invariant mass
	    histo_m_inv_mumu->Fill(p_mumu.M());
	    histo_pt_mumu->Fill(p_mumu.Pt());
	  }

	  p_mumujj = p_mumu + p_jj;


	   histo_m_inv_mumujj->Fill( p_mumujj.M() );

	}
	
	TCanvas canvas("canvas", "canvas", 600, 600);



	// Show resulting histograms
	// histo_m_inv_jj->Draw();
	gPad->SetLeftMargin(0.14);
	gPad->SetBottomMargin(0.15);
	
	histo_m_inv_mumu->GetXaxis()->SetTitle("m_{inv} (#mu^{-} #mu^{+}) [GeV/c^{2}]");
	histo_m_inv_mumu->GetYaxis()->SetTitle("Entries");
	histo_m_inv_mumu->GetYaxis()->SetTitleOffset(1.5);
	histo_m_inv_mumu->Draw();
	canvas.SaveAs("./figures/M_inv_mumu.pdf");

	canvas.Clear();

	histo_m_inv_jj->GetXaxis()->SetTitle("m_{inv} (jj) [GeV/c^{2}]");
	histo_m_inv_jj->GetYaxis()->SetTitle("Entries");
	histo_m_inv_jj->GetYaxis()->SetTitleOffset(1.5);
	histo_m_inv_jj->Draw(); canvas.SaveAs("./figures/M_inv_jj.pdf");

	canvas.Clear();

	histo_m_inv_mumujj->GetXaxis()->SetTitle("m_{inv} (#mu^{-} #mu^{+} jj) [GeV/c^{2}]");
	histo_m_inv_mumujj->GetYaxis()->SetTitle("Entries");
	histo_m_inv_mumujj->GetYaxis()->SetTitleOffset(1.5);
	histo_m_inv_mumujj->Draw();

	canvas.SaveAs("./figures/M_inv_mumujj.pdf");

	canvas.Clear();

	histo_pt_mumu->GetXaxis()->SetTitle("p_{T} (#mu^{-} #mu^{+}) [GeV]");
	histo_pt_mumu->GetYaxis()->SetTitle("Entries");
	histo_pt_mumu->GetYaxis()->SetTitleOffset(1.5);
	histo_pt_mumu->Draw();

	canvas.SaveAs("./figures/pt_mumu.pdf");



	return 0;

}
