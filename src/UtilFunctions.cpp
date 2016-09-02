#include "UtilFunctions.h"

std::string tag_Cat (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "jet";  return out;
		case 1: out = "bjet"; return out;
		case 2: out = "mu";   return out;
	}
}


std::string tag_Level (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "gene";     return out;
		case 1: out = "gene-cut"; return out;
		case 2: out = "reco";     return out;
		case 3: out = "reco-cut"; return out;
	}
}


std::string tag_Multiplicity (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "";    return out;
		case 1: out = "di-"; return out;
	}
}


std::string label_Cat (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "jet";   return out;
		case 1: out = "b-jet"; return out;
		case 2: out = "#mu";   return out;
	}
}


std::string label_Level (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "GEN";      return out;
		case 1: out = "GEN-cut";  return out;
		case 2: out = "RECO";     return out;
		case 3: out = "RECO-cut"; return out;
	}
}

std::string label_Multiplicity (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "";    return out;
		case 1: out = "di-"; return out;
	}
}


void progress_bar(double percent)
{
	std::string bar;
	
	double maxPercent = 100;
	int barWidth      = 50;
	double ratio      = barWidth/maxPercent; 

	for(int i = 0; i < barWidth; i++)
	{
	    if( i < (percent*ratio))
	    {
	        bar.replace(i,1,"=");
	    }
	    else if( i == (percent*ratio))
	    {
	        bar.replace(i,1,">");
	    }
	    else
	    {
	        bar.replace(i,1," ");
	    }
	}
	
	std::cout << "\033[1;34m" << "\r" "[" << bar << "] ";
	std::cout << "\033[0m" << percent << "%" << std::flush;
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


void SetupHistos( Histograms *histo, Binning *bins, std::string tag, std::set<TObject*> *fHistos)
{
	// - Allocate multi-dim arrays for the histo->rams
	AllocateArrayXYZ(histo->PtDistr,   bins->nCat,bins->nMult,bins->nLevel);
	AllocateArrayXYZ(histo->EtaDistr,  bins->nCat,bins->nMult,bins->nLevel);
	AllocateArrayXY (histo->MinvDistr, bins->nCat,           bins->nLevel);
	AllocateArrayXY (histo->mZhDistr,  bins->nCatmZh,        bins->nLevel);
	AllocateArrayX  (histo->nObj,      bins->nCat                       );


	// - Book histo->rams
	loopxyz( iCat, iMult, iLvl, bins->nCat, bins->nMult, bins->nLevel)
	{
		std::string histoname_pt  = tag+"_"+tag_Multiplicity(iMult)+tag_Cat(iCat)+"_pt_" +tag_Level(iLvl)+"-level";
		std::string histoname_eta = tag+"_"+tag_Multiplicity(iMult)+tag_Cat(iCat)+"_eta_"+tag_Level(iLvl)+"-level";

		std::string label_pt   = ";p_{T}("+label_Multiplicity(iMult)+label_Cat(iCat)+") [GeV/c] "+label_Level(iLvl)+"-level";
		std::string label_eta  = ";#eta("+label_Multiplicity(iMult)+label_Cat(iCat)+") "+label_Level(iLvl)+"-level";

		histo->PtDistr [iCat][iMult][iLvl] = new TH1D(histoname_pt.c_str(),  label_pt.c_str(),  bins->nPtBins,  bins->PtMin,  bins->PtMax);
		histo->EtaDistr[iCat][iMult][iLvl] = new TH1D(histoname_eta.c_str(), label_eta.c_str(), bins->nEtaBins, bins->EtaMin, bins->EtaMax);

		fHistos->insert(histo->PtDistr   [iCat][iMult][iLvl]);
		fHistos->insert(histo->EtaDistr  [iCat][iMult][iLvl]);
	}

	loopxy( iCat, iLvl, bins->nCat, bins->nLevel )
	{
		std::string histoname_minv = tag+"_"+"Minv_di-"+tag_Cat(iCat)+"_"+tag_Level(iLvl)+"-level";
		std::string label_minv 		= ";m_{inv}(di-"+label_Cat(iCat)+") [GeV/c^{2}] "+label_Level(iLvl)+"-level";

		histo->MinvDistr[iCat][iLvl] = new TH1D(histoname_minv.c_str(),label_minv.c_str(), bins->nMinvBins, bins->MinvMin, bins->MinvMax);

		fHistos->insert(histo->MinvDistr[iCat][iLvl]);


	}

	loopxy( iCat, iLvl, bins->nCatmZh, bins->nLevel )
	{
		std::string histoname_jjmumu = tag+"_"+"mZh_jjmumu_"+tag_Cat(iCat)+"_"+tag_Level(iLvl)+"-level";
		std::string label_jjmumu 	  = ";m_{inv}(#mu#mujj) [GeV/c^{2}] "+tag_Cat(iCat)+"_"+label_Level(iLvl)+"-level";
		histo->mZhDistr[iCat][iLvl] = new TH1D(histoname_jjmumu.c_str(), label_jjmumu.c_str(), bins->nmZhBins, bins->mZhMin, bins->mZhMax);

		fHistos->insert(histo->mZhDistr[iCat][iLvl]);
	}



	loopx( iCat, bins->nCat)
	{
		std::string histoname_nobj = tag+"_"+"n"+tag_Cat(iCat);
		std::string label_nobj 		= ";N_{"+label_Cat(iCat)+"}";
		histo->nObj[iCat] = new TH1D(histoname_nobj.c_str(), label_nobj.c_str(), bins->nObjBins, bins->ObjMin, bins->ObjMax);

		fHistos->insert(histo->nObj[iCat]);
	}

	std::string ZThetaDistr_name = tag+"_"+"ZThetaDistr";
	histo->ZThetaDistr = new TH1D( ZThetaDistr_name.c_str(), ";#Theta [rad];", 100, -0.1, 3.15);

	fHistos->insert( histo->ZThetaDistr );
//
//	loopx( iLvl, bins->nLevel)
//	{
//		std::string histoname_jjmumu = "mZh_jjmumu"+tag_Level(iLvl);
//		std::string label_jjmumu 	  = ";m_{inv}(#mu#mujj) "+label_Level(iLvl)+"-level";
//		histo->mZhDistr[iLvl] = new TH1D(histoname_jjmumu.c_str(), label_jjmumu.c_str(), bins->nmZhBins, bins->mZhMin, bins->mZhMax);
//
//		fHistos->insert(histo->mZhDistr[iLvl]);
//	}

	std::string nJetConstituents_name = tag+"_"+"nJetConstituents";
	histo->nJetConstituents = new TH1D(nJetConstituents_name.c_str(), ";# of jet constitutents;", 20, 0.0, 20.0);
	fHistos->insert(histo->nJetConstituents);

}




void LoadBinningConfig( config *conf, Binning *bins)
{
	// Bins
	bins->nCat      = getconfig((*conf), "nCat"  );
	bins->nMult     = getconfig((*conf), "nMult" );
	bins->nLevel    = getconfig((*conf), "nLevel");

	bins->nCatmZh   = getconfig((*conf), "nCatmZh");

	bins->nPtBins   = getconfig((*conf), "nPtBins");
	bins->PtMin     = getconfig((*conf), "PtMin"  );
	bins->PtMax     = getconfig((*conf), "PtMax"  );

	bins->nEtaBins  = getconfig((*conf), "nEtaBins");
	bins->EtaMin    = getconfig((*conf), "EtaMin");
	bins->EtaMax    = getconfig((*conf), "EtaMax");

	bins->nMinvBins = getconfig((*conf), "nMinvBins");
	bins->MinvMin   = getconfig((*conf), "MinvMin");
	bins->MinvMax   = getconfig((*conf), "MinvMax");

	bins->nmZhBins  = getconfig((*conf), "nmZhBins");
	bins->mZhMin    = getconfig((*conf), "mZhMin");
	bins->mZhMax    = getconfig((*conf), "mZhMax");

	bins->nObjBins  = getconfig((*conf), "nObjBins");
	bins->ObjMin    = getconfig((*conf), "ObjMin");
	bins->ObjMax    = getconfig((*conf), "ObjMax");
}


void LoadCutsConfig(    config *conf, Cuts *cuts)
{
	// Cuts
	cuts->cutMuonPtMin      = getconfig((*conf), "cutMuonPtMin");
	cuts->cutMuonEtaMax     = getconfig((*conf), "cutMuonEtaMax");

	cuts->cutElectronPtMin  = getconfig((*conf), "cutElectronPtMin");
	cuts->cutElectronEtaMax = getconfig((*conf), "cutElectronEtaMax");

	cuts->cutJetPtMin       = getconfig((*conf), "cutJetPtMin");
	cuts->cutJetEtaMax      = getconfig((*conf), "cutJetEtaMax");

	cuts->cutZMinvMin       = getconfig((*conf), "cutZMinvMin");
	cuts->cutZMinvMax       = getconfig((*conf), "cutZMinvMax");

	cuts->cutZPtMin         = getconfig((*conf), "cutZPtMin");
	cuts->cutZPtMax         = getconfig((*conf), "cutZPtMax");

	cuts->cuthMinvMin       = getconfig((*conf), "cuthMinvMin");
	cuts->cuthMinvMax       = getconfig((*conf), "cuthMinvMax");
}
