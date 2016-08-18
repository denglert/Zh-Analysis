#include <string>
enum Category { mu, jet, bjet };
enum GenReco { gen, reco, recocut };
enum Mult { mono, di };

std::string label_Cat          (const int id);
std::string label_GenRecLevel  (const int id);
std::string label_Multiplicity (const int id);
std::string tag_Cat (const int  id);
