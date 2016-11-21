#include "Zh-Analyzer.h"

int main(int argc, const char *argv[] ) 
{

	if (argc != 5)
	{
		std::cerr << "Usage: ./Zh-Analyzer <tag> <comp.conf> <bin.conf> <nEvents>" << std::endl;
		exit(1);
	}

	std::string                tag = argv[1];
	std::string compConfigFilePath = argv[2];
	std::string  binConfigFilePath = argv[3];
	int nEvents 				       = atoi(argv[4]);
	
	// - Plotting style
	TStyle *myStyle = TStyle_Scheme();
	gROOT->SetStyle("myStyle");

	// - Analysis FrameWork
	AnalysisFW AnaFW;
	AnaFW.tag 		          = tag;
	AnaFW.nEvents            = nEvents;
	AnaFW.compConfigFilePath = compConfigFilePath.c_str();
	AnaFW.binConfigFilePath  =  binConfigFilePath.c_str();

	// Initialize
	AnaFW.Init();

	// Iterate over each component
   for(int i=0; i < AnaFW.components.nComp; i++)
	{
		AnaFW.chain->Add( AnaFW.components.component_path[i].c_str() );
		AnaFW.Analyzer( AnaFW.chain, &AnaFW.histos[i] );
		AnaFW.chain->Reset();
	}

  std::map<TObject*, PlotSettings>::iterator itPlotMap;
  for(itPlotMap = AnaFW.hstacks.fPlotMap.begin(); itPlotMap != AnaFW.hstacks.fPlotMap.end(); ++itPlotMap)
  {
    PlotSettings *settings = &itPlotMap->second;
    settings->DrawingOption = "E";
  }
	AnaFW.CreateOutputFile();
	AnaFW.WriteOutput();
	std::cout << std::endl;
	AnaFW.MakePlots();
	// Custom plots
/*	TCanvas canvas("canvas", "canvas", 600, 600);

	gPad->SetLeftMargin(   0.14 );
	gPad->SetBottomMargin( 0.15 );
	
	AnaFW.histos[0].mZhDistr[bjet][recocut]->SetMaximum(0.05);
	AnaFW.histos[0].mZhDistr[bjet][recocut]->SetMinimum(-0.05);
	AnaFW.histos[0].mZhDistr[bjet][recocut]->Draw();
	AnaFW.histos[1].mZhDistr[bjet][recocut]->Draw("SAME");
	AnaFW.histos[2].mZhDistr[bjet][recocut]->Draw("SAME");
	canvas.SaveAs("plot.pdf");
*/	
	return 0;

}
