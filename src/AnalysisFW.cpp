#include "AnalysisFW.h"

//////////////////////
// -- AnalysisFW -- //
//////////////////////

void AnalysisFW::Init()
{

	conf.append(  binConfigFilePath.c_str() ); // - binning configuration 
	conf.append( compConfigFilePath.c_str() ); // - components configuration

	LoadBinningConfig( &conf, &bins);
  	   LoadCutsConfig( &conf, &cuts);

	components.nComp = (int)    getconfig(conf, "nComp"); // - number of components
	components.lumi  = (double) getconfig(conf,  "lumi"); // - integrated luminosity

	tag  = (std::string) getconfig(conf,  "tag");


	histos  = new TH1DContainer[components.nComp];
	hstacks = THStackContainer();

	std::string stacktag = "stacks";
	hstacks.Allocate( &bins, stacktag );

	printf("Total integrated luminosity:  %12.6f (fb-1)\n", components.lumi);
	printf("Component name | cross section (fb) | nPhysEvents | nGenEvents | scale\n");

	// - Extracting component config
	for( int i=0; i < components.nComp; i++ )
	{
		std::string compname  = Form("compname%d",i);
		std::string comppath  = Form("comppath%d",i);
		std::string compxsec  = Form("compxsec%d",i);
		std::string compnev   = Form("compnev%d",i);
		std::string compcolor = Form("compcolor%d",i);

		components.component_name[i]    = (std::string) getconfig(conf, compname.c_str() );
		components.component_path[i]    = (std::string) getconfig(conf, comppath.c_str() );
		components.component_xsec[i]    = (double)      getconfig(conf, compxsec.c_str() );
		components.component_nEvents[i] = (double)      getconfig(conf, compnev.c_str()  );
		components.component_scale[i]   = components.lumi * components.component_xsec[i] / components.component_nEvents[i];
		components.component_color[i]   = (int) getconfig(conf, compcolor.c_str() );

		histos[i].Allocate(  &bins, components.component_name[i] );
		histos[i].SetupBins( &bins ); 

		printf("%14s %20.6f %12.2f %12.2f %12.8f\n", components.component_name[i].c_str(), components.component_xsec[i], components.lumi*components.component_xsec[i], components.component_nEvents[i], components.component_scale[i]);
	}


	std::cout << "nComp: " << components.nComp << std::endl;

	std::cout << "nCat: "    << bins.nCat << std::endl;
	std::cout << "nLevel: "  << bins.nLevel << std::endl;
	std::cout << "nMult: "   << bins.nMult << std::endl;

	std::cout << "nCatmZh: " << bins.nCatmZh << std::endl;

	std::cout << "nPtBins: " << bins.nPtBins << std::endl;
	std::cout << "PtMin: "   << bins.PtMin   << std::endl;
	std::cout << "PtMax: "   << bins.PtMax   << std::endl;

};



AnalysisFW::AnalysisFW( )
{
  	chain = new TChain("Delphes");
}

void AnalysisFW::CreateOutputFile( )
{
	std::string prepath    = "./results/"+tag+"/";
	std::string outputfile = prepath+"ana.root";
	output = new TFile(outputfile.c_str(),"RECREATE");
}

void AnalysisFW::WriteOutput( )
{

 	for(int i = 0; i < components.nComp; i++)
	{
		histos[i].WriteToROOTFile( output );
	}

//  for(itHisto = fCollection.begin(); itHisto != fCollection.end(); ++itHisto)
//  {
//	 (*itHisto)->Write();
//  }
}

void AnalysisFW::MakePlots( )
{

  std::string prepath = "./results/"+tag+"/";


//  Warning: Need to fix this !!!


    std::set<TObject*>::iterator itHisto;
    for(int iComp = 0; iComp < components.nComp; iComp++)
	 {

    	for(itHisto = histos[iComp].fCollection.begin(); itHisto != histos[iComp].fCollection.end(); ++itHisto)
    	{
  	 	std::string name        = (*itHisto)->GetName();
  	 	std::string figfullpath = prepath+name;
		TH1D* histo = (TH1D*) (*itHisto);
  	 	CreatePlot( histo, figfullpath.c_str() );

		histo->Scale( components.component_scale[iComp] );

    	}

	 }

    std::set<TObject*>::iterator itHistos[components.nComp];
    for(int iComp = 0; iComp < components.nComp; iComp++)
	 {
		itHistos[iComp] = histos[iComp].fCollection.begin();
	 }

    std::set<TObject*>::iterator itStack;
    for(itStack = hstacks.fCollection.begin(); itStack != hstacks.fCollection.end(); ++itStack)
	 {

		THStack* hstack = (THStack*) (*itStack);

	    for(int iComp = 0; iComp < components.nComp; iComp++)
		 {
			TH1D* histo = (TH1D*) (*itHistos[iComp]);
			histo->SetFillColor  ( Colors[iComp] );
			histo->SetMarkerColor( Colors[iComp] );
			histo->SetMarkerStyle( 21 );
			histo->SetStats(false);
			hstack->Add ( histo );
			itHistos[iComp]++;
		 }

  	 	std::string name        = hstack->GetName();
  	 	std::string figfullpath = prepath+name;
  	 	CreateStackPlot( hstack, figfullpath.c_str() );

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
