#include "AnalysisFW.h"

//////////////////////
// -- AnalysisFW -- //
//////////////////////

void AnalysisFW::Init()
{

	config conf;
	conf.append(confFilePath.c_str());

	bins.nCat     = getconfig(conf, "nCat");
	bins.nMult    = getconfig(conf, "nMult");
	bins.nLevel   = getconfig(conf, "nLevel");

	bins.nPtBins = getconfig(conf, "nPtBins");
	bins.PtMin   = getconfig(conf, "PtMin");
	bins.PtMax   = getconfig(conf, "PtMax");

	bins.nEtaBins = getconfig(conf, "nEtaBins");
	bins.EtaMin   = getconfig(conf, "EtaMin");
	bins.EtaMax   = getconfig(conf, "EtaMax");

	bins.nMinvBins = getconfig(conf, "nMinvBins");
	bins.MinvMin   = getconfig(conf, "MinvMin");
	bins.MinvMax   = getconfig(conf, "MinvMax");

	bins.nmZhBins = getconfig(conf, "nmZhBins");
	bins.mZhMin   = getconfig(conf, "mZhMin");
	bins.mZhMax   = getconfig(conf, "mZhMax");

	bins.nObjBins = getconfig(conf, "nObjBins");
	bins.ObjMin   = getconfig(conf, "ObjMin");
	bins.ObjMax   = getconfig(conf, "ObjMax");

	cuts.cutMuonPtMin  = getconfig(conf, "cutMuonPtMin");
	cuts.cutMuonEtaMax = getconfig(conf, "cutMuonEtaMax");

	cuts.cutZMinvMin   = getconfig(conf, "cutZMinvMin");
	cuts.cutZMinvMax   = getconfig(conf, "cutZMinvMax");

	cuts.cutZPtMin     = getconfig(conf, "cutZPtMin");
	cuts.cutZPtMax     = getconfig(conf, "cutZPtMax");

	cuts.cuthMinvMin   = getconfig(conf, "cuthMinvMin");
	cuts.cuthMinvMax   = getconfig(conf, "cuthMinvMax");

	std::cout << "nCat: "   << bins.nCat << std::endl;
	std::cout << "nLevel: " << bins.nLevel << std::endl;
	std::cout << "nMult: "  << bins.nMult << std::endl;

	std::cout << "nPtBins: " << bins.nPtBins << std::endl;
	std::cout << "PtMin: "   << bins.PtMin   << std::endl;
	std::cout << "PtMax: "   << bins.PtMax   << std::endl;

	AllocateArrayXYZ(histo.PtDistr,   bins.nCat,bins.nMult,bins.nLevel);
	AllocateArrayXYZ(histo.EtaDistr,  bins.nCat,bins.nMult,bins.nLevel);
	AllocateArrayXY (histo.MinvDistr, bins.nCat,           bins.nLevel);
	AllocateArrayX  (histo.nObj,      bins.nCat                       );
	histo.mZhDistr = new TH1D*[bins.nLevel];

	loopxyz( iCat, iMult, iLvl, bins.nCat, bins.nMult, bins.nLevel)
	{
		std::string histoname_pt  = "Pt "+label_Multiplicity(iMult)+" "+tag_Cat(iCat)+" "+label_GenRecLevel(iLvl)+"-level";
		std::string histoname_eta = "Eta "+label_Multiplicity(iMult)+" "+tag_Cat(iCat)+" "+label_GenRecLevel(iLvl)+"-level";

		std::string label_pt   = ";p_{T}("+label_Multiplicity(iMult)+label_Cat(iCat)+") [GeV/c] "+label_GenRecLevel(iLvl)+"-level";
		std::string label_eta  = ";#eta("+label_Multiplicity(iMult)+label_Cat(iCat)+") "+label_GenRecLevel(iLvl)+"-level";

		histo.PtDistr [iCat][iMult][iLvl] = new TH1D(histoname_pt.c_str(),  label_pt.c_str(),  bins.nPtBins,  bins.PtMin,  bins.PtMax);
		histo.EtaDistr[iCat][iMult][iLvl] = new TH1D(histoname_eta.c_str(), label_eta.c_str(), bins.nEtaBins, bins.EtaMin, bins.EtaMax);
	}

	loopxy( iCat, iLvl, bins.nCat, bins.nLevel )
	{
		std::string histoname_minv = "Minv "+tag_Cat(iCat)+" "+label_GenRecLevel(iLvl)+"-level";
		std::string label_minv 		= ";m_{inv}(di-"+label_Cat(iCat)+") [GeV/c^{2}] "+label_GenRecLevel(iLvl)+"-level";

		histo.MinvDistr[iCat][iLvl] = new TH1D(histoname_minv.c_str(),label_minv.c_str(), bins.nMinvBins, bins.MinvMin, bins.MinvMax);
	}


	loopx( iCat, bins.nCat)
	{
		std::string histoname_nobj = "n"+tag_Cat(iCat);
		std::string label_nobj 		= ";N_{"+label_Cat(iCat)+"}";
		histo.nObj[iCat] = new TH1D(histoname_nobj.c_str(), label_nobj.c_str(), bins.nObjBins, bins.ObjMin, bins.ObjMax);
	}

	loopx( iLvl, bins.nLevel)
	{
		std::string histoname_jjmumu = "mZh_jjmumu"+label_GenRecLevel(iLvl);
		std::string label_jjmumu 	  = ";m_{inv}(#mu#mujj) "+label_GenRecLevel(iLvl)+"-level";
		histo.mZhDistr[iLvl] = new TH1D(histoname_jjmumu.c_str(), label_jjmumu.c_str(), bins.nmZhBins, bins.mZhMin, bins.mZhMax);
	}

};



AnalysisFW::AnalysisFW( const char confFilePath_[] )
{
	confFilePath = confFilePath_;

	histo.PtDistr   = NULL;
	histo.MinvDistr = NULL;
	histo.EtaDistr  = NULL;
	histo.mZhDistr  = NULL;

	Init();
}

//
bool AnalysisFW::CutJet(Jet* jet)
{
}

//
bool AnalysisFW::CutMuon(Muon* mu)
{
}

//
bool AnalysisFW::CutElectron(Electron* el)
{
}


////////////////////
//                //
// -- Analyzer -- //
//                //
////////////////////

void AnalysisFW::Analyzer( ExRootTreeReader* reader)
{

	// - Get pointers to branches used in this analysis
	TClonesArray *branchParticle 				= reader->UseBranch("Particle");
	TClonesArray *branchElectron 				= reader->UseBranch("Electron");
	TClonesArray *branchPhoton 				= reader->UseBranch("Photon");
	TClonesArray *branchMuon   				= reader->UseBranch("Muon");
	TClonesArray *branchTrack 					= reader->UseBranch("Track");
	TClonesArray *branchTower 					= reader->UseBranch("Tower");
	TClonesArray *branchEFlowTrack         = reader->UseBranch("EFlowTrack");
	TClonesArray *branchEFlowTower         = reader->UseBranch("EFlowTower");
	TClonesArray *branchEFlowMuon          = reader->UseBranch("EFlowMuon");
	TClonesArray *branchEFlowNeutralHadron = reader->UseBranch("EFlowNeutralHadron");
	TClonesArray *branchJet  		         = reader->UseBranch("Jet");

	// - Create physics objects
	Muon *muA 				 = NULL;
	Muon *muB 				 = NULL;
	Jet *jetA 				 = NULL;
	Jet *jetB 				 = NULL;
	Jet *jet_A 				 = NULL;
	Jet *jet_B 				 = NULL;
	GenParticle *particle = NULL;
	GenParticle *g0mother = NULL;
	GenParticle *g1mother = NULL;
	GenParticle *g2mother = NULL;
	GenParticle *g3mother = NULL;
	GenParticle *g4mother = NULL;
	Track *track 			 = NULL;
	Tower *tower 			 = NULL;
	TObject *object       = NULL;

	// - Lorentz Four-momenta
	TLorentzVector p_mumu; 
	TLorentzVector p_jj; 
	TLorentzVector p_mumujj; 
	TLorentzVector momentum;

	////////////////////////
	//                    //
	// --- Event loop --- //
	//                    //
	////////////////////////
	
	Long64_t nEntries = reader->GetEntries();
	if (nEvents == -1) {nEvents = nEntries;}
	std::cout << "nEvents: " << nEvents << std::endl;
	// - Loop over all events
	for(Int_t iEv = 0; iEv < nEvents; ++iEv)
	{
	
		// - Load Event
		reader->ReadEntry(iEv);
		
		////////////////
		// -- Jets -- //
		////////////////

		int nJets = branchJet->GetEntries();
		int nBJets = 0;
		histo.nObj[jet]->Fill(nJets);

		for(int iJet = 0; iJet < nJets; iJet++)
		{

	   	jetA = (Jet*) branchJet->At(iJet);
			histo.PtDistr [jet][mono][reco]->Fill( jetA->PT );
			histo.EtaDistr[jet][mono][reco]->Fill( jetA->Eta );

			if( jetA->BTag == true )
			{
				nBJets++;
				histo.PtDistr [bjet][mono][reco]->Fill( jetA->PT );
				histo.EtaDistr[bjet][mono][reco]->Fill( jetA->Eta );
			}

			for(int jJet = iJet+1; jJet < nJets; jJet++)
			{
				
	   		jetB = (Jet*) branchJet->At(jJet);
				TLorentzVector p_jj = jetA->P4() + jetB->P4();

				histo.MinvDistr[jet]    [reco]->Fill( p_jj.M()  );
				histo.PtDistr  [jet][di][reco]->Fill( p_jj.Pt() );
				histo.EtaDistr [jet][di][reco]->Fill( p_jj.Eta() );

				if( (jetA->BTag == true) && (jetB->BTag == true) )
				{
					histo.MinvDistr[bjet]    [reco]->Fill( p_jj.M()  );
					histo.PtDistr  [bjet][di][reco]->Fill( p_jj.Pt() );
					histo.EtaDistr [bjet][di][reco]->Fill( p_jj.Eta() );
				}

			}

		}

		histo.nObj[bjet]->Fill(nBJets);

		// - If event contains at least 2 jet
//		if( nJets >= 2)
//		{
//
//	   // Take first jet
//	   jet_A = (Jet*) branchJet->At(0);
//	   jet_B = (Jet*) branchJet->At(1);

//		std::cerr << "jet_A " << jet_A << std::endl;
//		std::cerr << "jet_B " << jet_B << std::endl;
//		std::cerr << "jet_A->PT: " << jet_A->PT << std::endl;
//		std::cerr << "jet_B->PT: " << jet_B->PT << std::endl;

//		int nJetAConstituents = jet_A->Constituents.GetEntriesFast();
//		std::cerr << "nJetAConstituents: " << nJetAConstituents << std::endl;

//      // Loop over all jet's constituents
//      for(int j = 0; j < nJetAConstituents; j++)
//      {
//
//
//         object = jet_A->Constituents.At(j);
//
//			// Check if the constituent is accessible
//			if(object == 0) continue;
//			
//			
//			if(object->IsA() == GenParticle::Class())
//			{
//			  particle = (GenParticle*) object;
//			  //	  std::cout << "    GenPart pt: " << particle->PT << ", eta: " << particle->Eta << ", phi: " << particle->Phi << std::endl;
//			  momentum += particle->P4();
//			}
//			else if(object->IsA() == Track::Class())
//			{
//			  track = (Track*) object;
//			  //	  std::cout << "    Track pt: " << track->PT << ", eta: " << track->Eta << ", phi: " << track->Phi << std::endl;
//			  momentum += track->P4();
//			
//			  std::cout << "track " << std::endl;
//			}
//			else if(object->IsA() == Tower::Class())
//			{
//			  tower = (Tower*) object;
//			  //	  std::cout << "    Tower pt: " << tower->ET << ", eta: " << tower->Eta << ", phi: " << tower->Phi << std::endl;
//			  momentum += tower->P4();
//			}
//      }
 

//		for(int j = 0; j < jet_A->Particles.GetEntriesFast(); ++j)
//		{
//		  particle = (GenParticle *) jet_A->Particles.At(j);
//		  g0mother = (GenParticle *) branchParticle->At(particle->M1);
//		  g1mother = (GenParticle *) branchParticle->At(g0mother->M1);
//		  g2mother = (GenParticle *) branchParticle->At(g1mother->M1);
//		  g3mother = (GenParticle *) branchParticle->At(g2mother->M1);
//		  g4mother = (GenParticle *) branchParticle->At(g3mother->M1);
//		  std::cout << "PID: " << particle->PID << std::endl;
//		  std::cout << "M1: "  << particle->M1 << std::endl;
//		  std::cout << "M2: "  << particle->M2 << std::endl;
		//  std::cout << "g0mother PID: " << g0mother->PID << std::endl;
		//  std::cout << "g1mother PID: " << g1mother->PID << std::endl;
		//  std::cout << "g2mother PID: " << g2mother->PID << std::endl;
		//  std::cout << "g3mother PID: " << g3mother->PID << std::endl;
		//  std::cout << "g4mother PID: " << g4mother->PID << std::endl;
//		}


//		p_jj = jet_A->P4()+jet_B->P4();
	
		// Plot jet transverse momentum
//	   histo_m_inv_jj->Fill( p_jj.M() );
//	  	}


		///////////////////////////
		// -- Particle branch -- //
		///////////////////////////
//
//		int nParticles =branchParticle->GetEntries();
//		for (int iPart = 0; iPart < nParticles; iPart++)
//		{
//		  particle = (GenParticle *) branchParticle->At(iPart);
//		  std::cout << "PDG PID#: " << particle->PID << std::endl;
//		}
	
		/////////////////
		// -- Muons -- //
		/////////////////

		int nMuons = branchMuon->GetEntries();
		histo.nObj[mu]->Fill(nMuons);

		// - If event contains at least 2 electrons
		
		for(int iMuon = 0; iMuon < nMuons; iMuon++)
		{

	   	muA = (Muon*) branchMuon->At(iMuon);
			histo.PtDistr [mu][mono][reco]->Fill( muA->PT );
			histo.EtaDistr[mu][mono][reco]->Fill( muA->Eta );

			for(int jMuon = iMuon+1; jMuon < nMuons; jMuon++)
			{
				
	   		muB = (Muon*) branchMuon->At(jMuon);
				TLorentzVector p_mumu = muA->P4() + muB->P4();

				histo.MinvDistr[mu]    [reco]->Fill( p_mumu.M()  );
				histo.PtDistr  [mu][di][reco]->Fill( p_mumu.Pt() );
				histo.EtaDistr [mu][di][reco]->Fill( p_mumu.Eta() );

			}

		}

		//////////////////
		// -- jjmumu -- // 
		//////////////////

		for(int iJet = 0; iJet < nJets; iJet++)
		for(int jJet = iJet+1; jJet < nJets; jJet++)
		for(int iMuon = 0; iMuon < nMuons; iMuon++)
		for(int jMuon = iMuon+1; jMuon < nMuons; jMuon++)
		{
					
	   	jetA = (Jet*) branchJet->At(iJet);
	   	jetB = (Jet*) branchJet->At(jJet);
	   	muA = (Muon*) branchMuon->At(iMuon);
	   	muB = (Muon*) branchMuon->At(jMuon);

			if ( (jetA->BTag == true) && (jetB->BTag == true) ) continue;

			TLorentzVector p_jjmumu = jetA->P4() + jetB->P4() + muA->P4() + muB->P4();
			histo.mZhDistr[reco]->Fill( p_jjmumu.M() );

		}

		
		} // end-of-iEv-loop

//		  particle = (GenParticle*) mu_A->Particle.GetObject();

//	   p_mumujj = p_mumu + p_jj;
	


}



void AnalysisFW::CreatePlots( )
{

	loopxyz( iCat, iMult, iLvl, bins.nCat, bins.nMult, bins.nLevel)
	{
		std::string fig_pt  = "./figures/pt_"+label_Multiplicity(iMult)+tag_Cat(iCat)+"_"+label_GenRecLevel(iLvl);
		std::string fig_eta = "./figures/eta_"+label_Multiplicity(iMult)+tag_Cat(iCat)+"_"+label_GenRecLevel(iLvl);

		CreatePlot(histo.PtDistr  [iCat][iMult][iLvl], fig_pt.c_str());
		CreatePlot(histo.EtaDistr [iCat][iMult][iLvl], fig_eta.c_str());
	}

	loopxy( iCat, iLvl, bins.nCat, bins.nLevel )
	{
		std::string fig_minv  = "./figures/minv_"+tag_Cat(iCat)+"_"+label_GenRecLevel(iLvl);
		CreatePlot(histo.MinvDistr [iCat][iLvl], fig_minv.c_str());
	}

	loopx( iCat, bins.nCat )
	{
		std::string fig_nobj = "./figures/n"+tag_Cat(iCat);
		CreatePlot(histo.nObj[iCat], fig_nobj.c_str());
	}

	loopx( iLvl, bins.nLevel )
	{
		std::string fig_mZh = "./figures/minv_jjmumu"+label_GenRecLevel(iLvl);
		CreatePlot(histo.mZhDistr[iLvl], fig_mZh.c_str());
	}


}

/////////////////////////////////
// --- Allocation functions -- //
/////////////////////////////////

template<class TYPE>
void AllocateArrayX(TYPE **&a, int n1)
{
	a = new TYPE*[n1];
}

template<class TYPE>
void AllocateArrayXY(TYPE ***&a, int n1, int n2)
{
	a = new TYPE**[n1];

	for (int i1 = 0; i1 < n1; i1++)
	{
		a[i1] = new TYPE*[n2];
	}
}

template<class TYPE>
void AllocateArrayXYZ(TYPE ****&a, int n1, int n2, int n3)
{
	a = new TYPE***[n1];

	for (int i1 = 0; i1 < n1; i1++)
	{
		a[i1] = new TYPE**[n2];

		for (int i2 = 0; i2 < n2; i2++)
		{
			a[i1][i2] = new TYPE*[n3];
		}

	}
}
