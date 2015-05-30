#ifndef LOGICSIM_H
#define LOGICSIM_H

#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include "design.h"

class LogicSim {
public:
	LogicSim(std::vector<string> pis, Design *d);
	int parse(char* filename, char* filenameOut);	
private:
	bool WriteOutputHeader(char* filenameOut);
	bool dump(char* filenameOut, vector<string> &inputVal);
private:
	std::set<string> _pis;
	std::vector<string> _pisOrder;
	Design* _d;
};

#endif // !LogicSim
