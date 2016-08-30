#include "AnalysisFW.h"

//////////////////////
// -- AnalysisFW -- //
//////////////////////

void AnalysisFW::Init()
{
	chain = TChain("Delphes");

	conf.append(  binConfigFilePath.c_str() );
	conf.append( compConfigFilePath.c_str() );

	components.nComp = getconfig(conf, "nComp");

	for( int i=0; i < components.nComp; i++ )
	{
		components.component_name = getconfig(conf, Form("compname%d",i) );
		components.component_path = getconfig(conf, Form("comppath%d",i) );
		components.component_xsec = getconfig(conf, Form("compxsec%d",i) );
	}

	// Bins
	bins.nCat      = getconfig(conf, "nCat"  );
	bins.nMult     = getconfig(conf, "nMult" );
	bins.nLevel    = getconfig(conf, "nLevel");

	bins.nCatmZh   = getconfig(conf, "nCatmZh");

	bins.nPtBins   = getconfig(conf, "nPtBins");
	bins.PtMin     = getconfig(conf, "PtMin"  );
	bins.PtMax     = getconfig(conf, "PtMax"  );

	bins.nEtaBins  = getconfig(conf, "nEtaBins");
	bins.EtaMin    = getconfig(conf, "EtaMin");
	bins.EtaMax    = getconfig(conf, "EtaMax");

	bins.nMinvBins = getconfig(conf, "nMinvBins");
	bins.MinvMin   = getconfig(conf, "MinvMin");
	bins.MinvMax   = getconfig(conf, "MinvMax");

	bins.nmZhBins  = getconfig(conf, "nmZhBins");
	bins.mZhMin    = getconfig(conf, "mZhMin");
	bins.mZhMax    = getconfig(conf, "mZhMax");

	bins.nObjBins  = getconfig(conf, "nObjBins");
	bins.ObjMin    = getconfig(conf, "ObjMin");
	bins.ObjMax    = getconfig(conf, "ObjMax");

	// Cuts
	cuts.cutMuonPtMin  = getconfig(conf, "cutMuonPtMin");
	cuts.cutMuonEtaMax = getconfig(conf, "cutMuonEtaMax");

	cuts.cutElectronPtMin  = getconfig(conf, "cutElectronPtMin");
	cuts.cutElectronEtaMax = getconfig(conf, "cutElectronEtaMax");

	cuts.cutJetPtMin  = getconfig(conf, "cutJetPtMin");
	cuts.cutJetEtaMax = getconfig(conf, "cutJetEtaMax");

	cuts.cutZMinvMin   = getconfig(conf, "cutZMinvMin");
	cuts.cutZMinvMax   = getconfig(conf, "cutZMinvMax");

	cuts.cutZPtMin     = getconfig(conf, "cutZPtMin");
	cuts.cutZPtMax     = getconfig(conf, "cutZPtMax");

	cuts.cuthMinvMin   = getconfig(conf, "cuthMinvMin");
	cuts.cuthMinvMax   = getconfig(conf, "cuthMinvMax");

	std::cout << "nComp: " << nComp << std::endl;

	std::cout << "nCat: "    << bins.nCat << std::endl;
	std::cout << "nLevel: "  << bins.nLevel << std::endl;
	std::cout << "nMult: "   << bins.nMult << std::endl;

	std::cout << "nCatmZh: " << bins.nCatmZh << std::endl;

	std::cout << "nPtBins: " << bins.nPtBins << std::endl;
	std::cout << "PtMin: "   << bins.PtMin   << std::endl;
	std::cout << "PtMax: "   << bins.PtMax   << std::endl;

	// - Allocate multi-dim arrays for the histograms
	AllocateArrayXYZ(histo.PtDistr,   bins.nCat,bins.nMult,bins.nLevel);
	AllocateArrayXYZ(histo.EtaDistr,  bins.nCat,bins.nMult,bins.nLevel);
	AllocateArrayXY (histo.MinvDistr, bins.nCat,           bins.nLevel);
	AllocateArrayXY (histo.mZhDistr,  bins.nCatmZh,        bins.nLevel);
	AllocateArrayX  (histo.nObj,      bins.nCat                       );


	// - Book histograms
	loopxyz( iCat, iMult, iLvl, bins.nCat, bins.nMult, bins.nLevel)
	{
		std::string histoname_pt  = tag_Multiplicity(iMult)+tag_Cat(iCat)+"_pt_" +tag_Level(iLvl)+"-level";
		std::string histoname_eta = tag_Multiplicity(iMult)+tag_Cat(iCat)+"_eta_"+tag_Level(iLvl)+"-level";

		std::string label_pt   = ";p_{T}("+label_Multiplicity(iMult)+label_Cat(iCat)+") [GeV/c] "+label_Level(iLvl)+"-level";
		std::string label_eta  = ";#eta("+label_Multiplicity(iMult)+label_Cat(iCat)+") "+label_Level(iLvl)+"-level";

		histo.PtDistr [iCat][iMult][iLvl] = new TH1D(histoname_pt.c_str(),  label_pt.c_str(),  bins.nPtBins,  bins.PtMin,  bins.PtMax);
		histo.EtaDistr[iCat][iMult][iLvl] = new TH1D(histoname_eta.c_str(), label_eta.c_str(), bins.nEtaBins, bins.EtaMin, bins.EtaMax);

		fHistos.insert(histo.PtDistr   [iCat][iMult][iLvl]);
		fHistos.insert(histo.EtaDistr  [iCat][iMult][iLvl]);
	}

	loopxy( iCat, iLvl, bins.nCat, bins.nLevel )
	{
		std::string histoname_minv = "Minv_di-"+tag_Cat(iCat)+"_"+tag_Level(iLvl)+"-level";
		std::string label_minv 		= ";m_{inv}(di-"+label_Cat(iCat)+") [GeV/c^{2}] "+label_Level(iLvl)+"-level";

		histo.MinvDistr[iCat][iLvl] = new TH1D(histoname_minv.c_str(),label_minv.c_str(), bins.nMinvBins, bins.MinvMin, bins.MinvMax);

		fHistos.insert(histo.MinvDistr[iCat][iLvl]);


	}

	loopxy( iCat, iLvl, bins.nCatmZh, bins.nLevel )
	{
		std::string histoname_jjmumu = "mZh_jjmumu_"+tag_Cat(iCat)+"_"+tag_Level(iLvl)+"-level";
		std::string label_jjmumu 	  = ";m_{inv}(#mu#mujj) [GeV/c^{2}] "+tag_Cat(iCat)+"_"+label_Level(iLvl)+"-level";
		histo.mZhDistr[iCat][iLvl] = new TH1D(histoname_jjmumu.c_str(), label_jjmumu.c_str(), bins.nmZhBins, bins.mZhMin, bins.mZhMax);

		fHistos.insert(histo.mZhDistr[iCat][iLvl]);
	}



	loopx( iCat, bins.nCat)
	{
		std::string histoname_nobj = "n"+tag_Cat(iCat);
		std::string label_nobj 		= ";N_{"+label_Cat(iCat)+"}";
		histo.nObj[iCat] = new TH1D(histoname_nobj.c_str(), label_nobj.c_str(), bins.nObjBins, bins.ObjMin, bins.ObjMax);

		fHistos.insert(histo.nObj[iCat]);
	}

	histo.ZThetaDistr = new TH1D("ZThetaDistr", ";#Theta [rad];", 100, -0.1, 3.15);

	fHistos.insert( histo.ZThetaDistr );
//
//	loopx( iLvl, bins.nLevel)
//	{
//		std::string histoname_jjmumu = "mZh_jjmumu"+tag_Level(iLvl);
//		std::string label_jjmumu 	  = ";m_{inv}(#mu#mujj) "+label_Level(iLvl)+"-level";
//		histo.mZhDistr[iLvl] = new TH1D(histoname_jjmumu.c_str(), label_jjmumu.c_str(), bins.nmZhBins, bins.mZhMin, bins.mZhMax);
//
//		fHistos.insert(histo.mZhDistr[iLvl]);
//	}

	histo.nJetConstituents = new TH1D("nJetConstituents", ";# of jet constitutents;", 20, 0.0, 20.0);
	fHistos.insert(histo.nJetConstituents);

};



AnalysisFW::AnalysisFW( )
{
}

AnalysisFW::AnalysisFW( const char confFilePath_[] )
{
	confFilePath = confFilePath_;

	histo.PtDistr   = NULL;
	histo.MinvDistr = NULL;
	histo.EtaDistr  = NULL;
	histo.mZhDistr  = NULL;

	Init();
}

void AnalysisFW::CreateOutput( )
{
	std::string prepath    = "./results/"+tag+"/";
	std::string outputfile = prepath+"ana.root";
	output = new TFile(outputfile.c_str(),"RECREATE");
}

void AnalysisFW::WriteOutput( )
{
  output->cd();
  std::set<TObject*>::iterator itHisto;
  for(itHisto = fHistos.begin(); itHisto != fHistos.end(); ++itHisto)
  {
	 (*itHisto)->Write();
  }
}

void AnalysisFW::MakePlots( )
{


  std::string prepath = "./results/"+tag+"/";

  std::set<TObject*>::iterator itHisto;
  for(itHisto = fHistos.begin(); itHisto != fHistos.end(); ++itHisto)
  {
	 std::string name        = (*itHisto)->GetName();
	 std::string figfullpath = prepath+name;
	 CreatePlot((TH1D*)(*itHisto), figfullpath.c_str());
  }

//  	PlotSettings settings;
//  	TObject *object;
//  	TH1 *histogram;
//  	THStack *stack;
//  	TPaveStats *stats;
//  	TString name;

//  	TCanvas *canvas = GetCanvas();

//  	map<TObject*, PlotSettings>::iterator itPlotMap;
//
//  	for(itPlotMap = fPlotMap.begin(); itPlotMap != fPlotMap.end(); ++itPlotMap)
//  	{
//  	  object = itPlotMap->first;
//  	  settings = itPlotMap->second;
//  	  name = object->GetName();
//  	  histogram = 0;
//  	  stack = 0;
//
//  	  if(object->IsA()->InheritsFrom(TH1::Class()))
//  	  {
//  	    histogram = static_cast<TH1*>(object);
//  	  }
//  	  else if(object->IsA()->InheritsFrom(THStack::Class()))
//  	  {
//  	    stack = static_cast<THStack*>(object);
//  	    histogram = static_cast<TH1*>(stack->GetHists()->First());
//  	  }
//
//  	  canvas->SetLogx(settings.logx);
//  	  if(histogram == 0 || histogram->Integral() > 0.0)
//  	  {
//  	    canvas->SetLogy(settings.logy);
//  	  }
//  	  else
//  	  {
//  	    canvas->SetLogy(0);
//  	  }
//
//  	  if(object->IsA()->InheritsFrom(THStack::Class()))
//  	  {
//  	    object->Draw("nostack");
//  	    stack->GetXaxis()->SetTitle(histogram->GetXaxis()->GetTitle());
//  	    stack->GetYaxis()->SetTitle(histogram->GetYaxis()->GetTitle());
//  	    stack->GetXaxis()->SetTitleOffset(1.5);
//  	    stack->GetYaxis()->SetTitleOffset(1.75);
//  	  }
//  	  else
//  	  {
//  	    object->Draw();
//  	  }
//
//  	  canvas->Update();
//
//  	  if(histogram)
//  	  {
//  	    stats = static_cast<TPaveStats*>(histogram->FindObject("stats"));
//  	    if(stats)
//  	    {
//  	      stats->SetX1NDC(0.67);
//  	      stats->SetX2NDC(0.99);
//  	      stats->SetY1NDC(0.77);
//  	      stats->SetY2NDC(0.99);
//  	      stats->SetTextFont(kExRootFont);
//  	      stats->SetTextSize(kExRootFontSize);
//  	      canvas->Draw();
//  	    }
//  	  }
//
//  	  if(settings.attachments)
//  	  {
//  	    TIter iterator(settings.attachments);
//  	    while((object = iterator()))
//  	    {
//  	      object->Draw();
//  	    }
//  	  }
//
//  	  canvas->Print(name + "." + format);
//  	}


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
