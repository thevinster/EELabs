#include "stdafx.h"
#include "LogicSim.h"
#include <string>
#include <sstream>

using namespace std;

LogicSim::LogicSim(vector<string> pis, Design *d): _pis(pis.begin(), pis.end()) {
	_d = d;
}

int LogicSim::parse(char* filename, char* filenameOut) {
	ifstream in(filename);
	if (in.fail()) {
		cerr << "Failed to open the file: ERROR in Line 0" << endl;
		return 1;
	}
	string lineText, word;
	int lineNo = 0;
	getline(in, lineText);
	lineNo++;
	stringstream ss(lineText);
	while (ss >> word) {
		if (_pis.find(word) == _pis.end()) {
			cerr << "Invalid Input String: ERROR in Line " << lineNo << endl;
			return 1;
		}
		_pisOrder.push_back(word);
	}
	
	if (!WriteOutputHeader(filenameOut)) {
		cerr << "Error writing header file: ERROR in Line " << lineNo << endl;
		return 1;
	}

	vector<Net*>* fList = _d->toposort();
	while (getline(in, lineText)) {
		vector<string> inputVal;
		lineNo++;
		stringstream ss(lineText);
		while (ss >> word) {
			// check if valid by 1, X or 0
			if (word != "X" && word != "1" && word != "0") {
				cerr << "Invalid Input Value: ERROR in Line " << lineNo << endl;
				return 1;
			}
			inputVal.push_back(word);
		}
		
		// check the size
		if (inputVal.size() != _pisOrder.size()) {
			cerr << "Too many Inputs: ERROR in Line: " << lineNo << endl;
			return 1;
		}
		
		//Simulate
		for (int i = 0; i < inputVal.size(); i++) {
			_d->findNet(_pisOrder[i])->setVal((inputVal[i][0]));
		}
		
		// iterate through the list
		for (int i = 0; i < fList->size(); i++) {
			fList->at(i)->setVal(fList->at(i)->computeVal());
			fList->at(i)->setDelay(fList->at(i)->computeDelay());
		}

		if (!dump(filenameOut, inputVal)) {
			cerr << "Error in writing output values: ERROR in Line " << lineNo << endl;
			return 1;
		}
	}
}

bool LogicSim::dump(char* filenameOut, vector<string> &inputVal) {
	// write out to disk
	ofstream out(filenameOut, ios::app);
	if (out.fail()) {
		cerr << "Unable to open output file" << endl;
		return false;
	}
	for (int i = 0; i < inputVal.size(); i++) {
		out << inputVal[i] << " ";
	}
	out << "=> ";
	// get the output values
	vector<string> poVal = _d->getPO();
	for (int i = 0; i < poVal.size(); i++) {
		out << _d->findNet(poVal[i])->getVal() << "@" << _d->findNet(poVal[i])->getDelay() << " ";
	}
	out << endl;
	return true;
}

bool LogicSim::WriteOutputHeader(char* filenameOut) {
	ofstream out(filenameOut);
	if (out.fail()) {
		cerr << "Unable to open output file" << endl;
		return false;
	}
	for (int i = 0; i < _pisOrder.size(); i++) {
		out << _pisOrder[i] << " ";
	}
	out << "=> ";
	vector<string> poVal = _d->getPO();
	for (int i = 0; i < poVal.size(); i++) {
		out << poVal[i] << " ";
	}
	out << endl;
	out.flush();
	out.close();
	return true;
}