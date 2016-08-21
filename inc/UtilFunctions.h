#ifndef UTILFUNCTIONS_H
#define UTILFUNCTIONS_H

#include <string>
#include <iostream>

enum Category { jet, bjet, mu };
enum Level { gene, genecut, reco, recocut };
enum Mult { mono, di };

std::string label_Cat          (const int id);
std::string label_Level        (const int id);
std::string label_Multiplicity (const int id);
std::string tag_Cat            (const int  id);
std::string tag_Multiplicity   (const int  id);
std::string tag_Level          (const int  id);

void progress_bar( double percent );

#endif
