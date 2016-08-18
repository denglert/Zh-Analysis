#include "GraphTools.h"

TStyle* TStyle_Scheme ()
{

	TStyle* myStyle = new TStyle("myStyle","My own Root Style");
//	myStyle->SetTitleSize(0.3); 
//	myStyle->SetTitleX(0.3); 
	myStyle->SetTitleXOffset(1.5); 
	myStyle->SetTitleSize(0.04,"xy"); 
//	myStyle->SetLabelSize(0.06,"xy"); 
//

	
	return myStyle;

}

void CreatePlot (TH1D *histo, const char basename[])
{
	TCanvas canvas("canvas", "canvas", 600, 600);
	gPad->SetLeftMargin(0.14);
	gPad->SetBottomMargin(0.15);
	histo->Draw();
	std::string outfig = basename;
	outfig = outfig+".pdf";
	canvas.SaveAs(outfig.c_str());
}
