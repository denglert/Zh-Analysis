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


template<class T>
void CreatePlot (T *histo, const char basename[])
{
	TCanvas canvas("canvas", "canvas", 600, 600);
	gPad->SetLeftMargin(0.14);
	gPad->SetBottomMargin(0.15);
	histo->Draw("E");
	std::string outfig = basename;
	outfig = outfig+".pdf";
	canvas.SaveAs(outfig.c_str());
}

template void CreatePlot ( TH1D *histo,    const char outfig[]) ;
template void CreatePlot ( THStack *histo, const char outfig[]) ;

void CreateStackPlot (THStack *hstack, const char basename[])
{
	gStyle->SetOptStat(0);
	TCanvas canvas("canvas", "canvas", 600, 600);
	gPad->SetLeftMargin(0.14);
	gPad->SetBottomMargin(0.15);
	//hstack->Draw("");
	hstack->Draw("E");
	std::string outfig = basename;
	outfig = outfig+".pdf";
	canvas.SaveAs(outfig.c_str());
}
