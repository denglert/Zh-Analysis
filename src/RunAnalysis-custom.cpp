#include "Zh-Analyzer.h"
#include <cmath>

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

	int topThreshold_Min_Bin = AnaFW.histos[0].mZhDistr[0][0]->FindBin(300.0);
	int topThreshold_Max_Bin = AnaFW.histos[0].mZhDistr[0][0]->FindBin(500.0);

	double topThreshold_Integral_qq = AnaFW.histos[0].mZhDistr[0][0]->Integral( topThreshold_Min_Bin, topThreshold_Max_Bin );
	double topThreshold_Integral_gg = AnaFW.histos[1].mZhDistr[0][0]->Integral( topThreshold_Min_Bin, topThreshold_Max_Bin );

	double s = topThreshold_Integral_gg;
	double b = topThreshold_Integral_qq;
	double s_2_b = s/b;
	double s_2_sqrt_b = s/sqrt(b);

	printf("\n\n### --- Integrals --- ###\n" );
	printf("qq:        %.3f\n", topThreshold_Integral_qq);
	printf("gg:        %.3f\n", topThreshold_Integral_gg);

	printf("s/b:       %.3f\n", s_2_b      );
	printf("s/sqrt(b): %.3f\n", s_2_sqrt_b );

	printf("" );

	return 0;

}
