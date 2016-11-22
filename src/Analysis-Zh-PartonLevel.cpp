#include "AnalysisFW.h"

////////////////////
//                //
// -- Analyzer -- //
//                //
////////////////////

// --- Prerequisites:
//   - needs ExRootTreeReader reader set up already.

void AnalysisFW::Analyzer( TChain *chain, ResultContainer<TH1D> *histo)
{
	std::cout << "AnalysisFW::Analyzer started." << std::endl;

	// -  Create object of class ExRootTreeReader
	reader = new ExRootTreeReader(chain);

	// - Get pointers to branches used in this analysis
	TClonesArray *branchParticle 				= reader->UseBranch("Particle");
	GenParticle *particle = NULL;

	TLorentzVector p_h;
	TLorentzVector p_Z;


   ////////////////////////
   //                    //
   // --- Event loop --- //
   //                    //
   ////////////////////////

   Long64_t nEntries = reader->GetEntries();
   if (nEvents == -1) {nEvents = nEntries;}
   std::cout << "nEvents: " << nEvents << std::endl;
   // - Loop over all events -- //
   for(Int_t iEv = 0; iEv < nEvents; ++iEv)
   {

      double percent = iEv/double(nEvents)*100.0;
      progress_bar (percent);

      // - Load Event -- //
      reader->ReadEntry(iEv);


//		printf("-------------------------\n");
//		printf("---    iEv: %03d   ---\n", iEv);
//		printf("-------------------------\n");

		int nParticles = branchParticle->GetEntries();

//		//std::cout << "PID Status MotherPID MotherStatus GrMotherPID GrMotherStatus Pt" << std::endl;
//		int nParticles =branchParticle->GetEntries();
//		for (int iPart = 0; iPart < nParticles; iPart++)
//		{
//	
//			  particle = (GenParticle *) branchParticle->At(iPart);
//	
//			  int PID    = particle->PID;
//			  int Status = particle->Status;
//	
//			  printf("%5d %1d\n", PID, Status);
//				
//				if ( (particle->PID == 23) && (particle->Status == 3) )
//				{ p_Z = particle->P4(); }
//	
//				if ( (particle->PID == 25) && (particle->Status == 3) )
//				{ p_h = particle->P4(); }
//	
//		}

 		int iPart = 0;

		bool hFound = false;
		bool ZFound = false;

		while ( ! ( hFound && ZFound) && (iPart < nParticles) )
		{
	
			  particle = (GenParticle *) branchParticle->At(iPart);
	
			  int PID    = particle->PID;
			  int Status = particle->Status;
	
				if ( (particle->PID == 25) && (particle->Status == 3) )
				{ 
					p_h = particle->P4();
					hFound = true;

//		  			printf("h found: %5d %1d\n", PID, Status);
				}

				if ( (particle->PID == 23) && (particle->Status == 3) )
				{ 
					p_Z = particle->P4();
					ZFound = true;

//		  			printf("Z found: %5d %1d\n", PID, Status);
				}
				
				iPart++;
//	    		printf("iPart/nParticles: %d / %d |||| ZFound: %d | hFound: %d\n", iPart, nParticles, ZFound, hFound);
	
		}

		TLorentzVector p_Zh = p_Z + p_h;	

		histo->mZhDistr[0][0] -> Fill( p_Zh.M() );


	}

//				if ( (particle->PID == 23) && (particle->Status == 3) )
//				{ p_Z = particle->P4(); }


	std::cout << std::endl;
	std::cout << "AnalysisFW::Analyzer finished." << std::endl;

}
