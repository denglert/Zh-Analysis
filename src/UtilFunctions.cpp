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
