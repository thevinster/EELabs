#include "stdafx.h"
#include "vlg_parser_man.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void trim(string &str);

VlgParserMan::VlgParserMan() {

}

Design* VlgParserMan::parse(char *filename) {
	ifstream in(filename);
	if (in.fail()) {
		cerr << "Unable to open the file!" << endl;
		return NULL;
	}
	vector<string> ioList;
	string lineText;
	bool parseError = false;
	vector<string> ioPins = parsePortList(in, lineText, parseError);
	if (parseError) {
		cerr << "Syntax Error";
		return NULL;
	}
	Design* d = new Design(ioPins[0]);
	while (getline(in, lineText)) {
		stringstream ss(lineText);
		string word;
		ss >> word;
		if (word == "input") {
			getline(ss, word, ';');
			trim(word);
			d->addPI(word);
			d->addFindNet(word);

		}
		else if (word == "output") {
			getline(ss, word, ';');
			trim(word);
			d->addPO(word);
			d->addFindNet(word);
		}
		else if (word == "wire") {
			getline(ss, word, ';');
			trim(word);
			d->addFindNet(word);
		}
		else if (word == "and") {
			getline(ss, word);
			trim(word);
			ss.clear(); ss.str("");
			ss << word;
			int dlay = 1;
			if (word[0] == '#') {
				dlay = word[1] - '0';
				ss >> word;
			}
			string name;
			getline(ss, name, '('); // even if it got it right first time, it should be the same
			trim(name);

			getline(ss, word, ')');
			trim(word);
			ss.clear(); ss.str("");
			ss << word;

			getline(ss, word, ',');
			trim(word);
			if (d->isPI(d->addFindNet(word))) {
				parseError = true;
				cerr << "parsing error and" << endl;
				return NULL;
			}
			(d->addFindGate(0, name, dlay))->addOutput(d->addFindNet(word));
			(d->addFindNet(word))->addDriver(d->findGate(name));
			int cnt = 0;
			while (getline(ss, word, ',')) {
				trim(word);
				(d->findGate(name))->addInput(d->addFindNet(word));
				(d->addFindNet(word))->addLoad(d->findGate(name));
				cnt++;
			}
			if (cnt <= 1) {
				parseError = true;
				return NULL;
			}
		}
		else if (word == "or") {
			getline(ss, word);
			trim(word);
			ss.clear(); ss.str("");
			ss << word;
			int dlay = 1;
			if (word[0] == '#') {
				dlay = word[1] - '0';
				ss >> word;
			}
			string name;
			getline(ss, name, '('); // even if it got it right first time, it should be the same
			trim(name);
			
			getline(ss, word, ')');
			trim(word);
			ss.clear(); ss.str("");
			ss << word;

			getline(ss, word, ',');
			trim(word);
			if (d->isPI(d->addFindNet(word))) {
				parseError = true;
				cerr << "parsing error or" << endl;
				return NULL;
			}
			(d->addFindGate(1, name, dlay))->addOutput(d->addFindNet(word));
			(d->addFindNet(word))->addDriver(d->findGate(name));
			int cnt = 0;
			while (getline(ss, word, ',')) {
				trim(word);
				(d->findGate(name))->addInput(d->addFindNet(word));
				(d->addFindNet(word))->addLoad(d->findGate(name));
				cnt++;
			}
			if (cnt <= 1) {
				parseError = true;
				return NULL;
			}
		}
		else if (word == "nand") {
			getline(ss, word);
			trim(word);
			ss.clear(); ss.str("");
			ss << word;
			int dlay = 1;
			if (word[0] == '#') {
				dlay = word[1] - '0';
				ss >> word;
			}
			string name;
			getline(ss, name, '('); // even if it got it right first time, it should be the same
			trim(name);
			
			getline(ss, word, ')');
			trim(word);
			ss.clear(); ss.str("");
			ss << word;

			getline(ss, word, ',');
			trim(word);
			if (d->isPI(d->addFindNet(word))) {
				parseError = true;
				cerr << "parsing error nand" << endl;
				return NULL;
			}
			(d->addFindGate(2, name, dlay))->addOutput(d->addFindNet(word));
			(d->addFindNet(word))->addDriver(d->findGate(name));
			int cnt = 0;
			while (getline(ss, word, ',')) {
				trim(word);
				(d->findGate(name))->addInput(d->addFindNet(word));
				(d->addFindNet(word))->addLoad(d->findGate(name));
				cnt++;
			}
			if (cnt <= 1) {
				parseError = true;
				return NULL;
			}
		}
		else if (word == "nor") {
			getline(ss, word);
			trim(word);
			ss.clear(); ss.str("");
			ss << word;
			int dlay = 1;
			if (word[0] == '#') {
				dlay = word[1] - '0';
				ss >> word;
			}
			string name;
			getline(ss, name, '('); // even if it got it right first time, it should be the same
			trim(name);
			
			getline(ss, word, ')');
			trim(word);
			ss.clear(); ss.str("");
			ss << word;

			getline(ss, word, ',');
			trim(word);
			if (d->isPI(d->addFindNet(word))) {
				parseError = true;
				cerr << "parsing error nor" << endl;
				return NULL;
			}
			(d->addFindGate(3, name, dlay))->addOutput(d->addFindNet(word));
			(d->addFindNet(word))->addDriver(d->findGate(name));
			int cnt = 0;
			while (getline(ss, word, ',')) {
				trim(word);
				(d->findGate(name))->addInput(d->addFindNet(word));
				(d->addFindNet(word))->addLoad(d->findGate(name));
				cnt++;
			}
			if (cnt <= 1) {
				parseError = true;
				return NULL;
			}
		}
		else if (word == "xor") {
			getline(ss, word);
			trim(word);
			ss.clear(); ss.str("");
			ss << word;
			int dlay = 1;
			if (word[0] == '#') {
				dlay = word[1] - '0';
				ss >> word;
			}
			string name;
			getline(ss, name, '('); // even if it got it right first time, it should be the same
			trim(name);
			
			getline(ss, word, ')');
			trim(word);
			ss.clear(); ss.str("");
			ss << word;

			getline(ss, word, ',');
			trim(word);
			if (d->isPI(d->addFindNet(word))) {
				parseError = true;
				cerr << "parsing error xor" << endl;
				return NULL;
			}
			(d->addFindGate(4, name, dlay))->addOutput(d->addFindNet(word));
			(d->addFindNet(word))->addDriver(d->findGate(name));
			int cnt = 0;
			while (getline(ss, word, ',')) {
				trim(word);
				(d->findGate(name))->addInput(d->addFindNet(word));
				(d->addFindNet(word))->addLoad(d->findGate(name));
				cnt++;
			}
			if (cnt <= 1) {
				parseError = true;
				return NULL;
			}
		}
		else if (word == "not") {
			getline(ss, word);
			trim(word);
			ss.clear(); ss.str("");
			ss << word;
			int dlay = 1;
			if (word[0] == '#') {
				dlay = word[1] - '0';
				ss >> word;
			}
			string name;
			getline(ss, name, '('); // even if it got it right first time, it should be the same
			trim(name);
			
			getline(ss, word, ')');
			trim(word);
			ss.clear(); ss.str("");
			ss << word;

			getline(ss, word, ',');
			trim(word);
			if (d->isPI(d->addFindNet(word))) {
				parseError = true;
				cerr << "parsing error not" << endl;
				return NULL;
			}
			(d->addFindGate(5, name, dlay))->addOutput(d->addFindNet(word));
			(d->addFindNet(word))->addDriver(d->findGate(name));
			int cnt = 0;
			while (getline(ss, word, ',')) {
				trim(word);
				(d->findGate(name))->addInput(d->addFindNet(word));
				(d->addFindNet(word))->addLoad(d->findGate(name));
				cnt++;
			}
			
		}
	}


	return d;
}

vector<string> VlgParserMan::parsePortList(istream &mystream, string &parsemsg, bool &parse_err) {
	vector<string> portList;
	while (getline(mystream, parsemsg)) {
		stringstream ss(parsemsg);
		string word;
		ss >> word;
		if (word == "module") {
			getline(ss, word, '(');
			trim(word);
			portList.push_back(word);
			getline(ss, word, ')');
			ss.clear();
			ss.str("");
			ss << word;
			while (getline(ss, word, ',')) {
				trim(word);
				if (word[0] == ' ') {
					parse_err = true;
					break;
				}
				portList.push_back(word);
			}
			break;
		}
	}
	if (portList.size() == 0) parse_err = true;
	return portList;
}

void trim(string &str) {
	size_t startpos = str.find_first_not_of(" \t");
	if (string::npos != startpos) {
		str = str.substr(startpos);
	}
}
