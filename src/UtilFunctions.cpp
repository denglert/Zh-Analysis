#include "UtilFunctions.h"

std::string label_Cat (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "#mu";   return out;
		case 1: out = "jet";   return out;
		case 2: out = "b-jet"; return out;
	}
}


std::string tag_Cat (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "mu";   return out;
		case 1: out = "jet";   return out;
		case 2: out = "bjet"; return out;
	}
}


std::string label_GenRecLevel (const int  id)
{
	std::string out;

	switch (id)
	{
		case 0: out = "GEN";      return out;
		case 1: out = "RECO";     return out;
		case 2: out = "RECO-cut"; return out;
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
