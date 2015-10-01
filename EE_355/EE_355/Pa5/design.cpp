#include "stdafx.h"
#include "design.h"

enum {WHITE, GRAY, BLACK};

Design::Design(string n) : desname(n) {

}

Design::~Design() {
	//TODO: Need to delete all the Net* and Gate*
	for (map<string, Net*>::iterator it = designNets.begin(); it != designNets.end(); ++it) {
		delete it->second;
		// this proceeds to delete the Net class which has its own destructor
	}
	for (map<string, Gate*>::iterator it = designGates.begin(); it != designGates.end(); ++it) {
		delete it->second;
		// this proceeds to delete the Gate class which has its own destructor
	}
}

string Design::name() {
	return desname;
}

void Design::addPI(string n) {
	pis.push_back(n);
}

void Design::addPO(string n) {
	pos.push_back(n);
}

Net* Design::findNet(string net_name) {
	if (designNets.find(net_name) != designNets.end()) {
		return designNets[net_name];
	}
	return NULL;
}

Gate* Design::findGate(string inst_name) {
	if (designGates.find(inst_name) != designGates.end()) {
		return designGates[inst_name];
	}
	return NULL;
}

Net* Design::addFindNet(string n) {
	if (designNets.find(n) != designNets.end()) {
		return designNets[n];
	}
	Net* newNet = new Net(n);
	designNets.insert(make_pair(n, newNet));
	return newNet;
}

Gate* Design::addFindGate(int gtype, string g) {
	if (designGates.find(g) != designGates.end()) {
		return designGates[g];
	}
	Gate* newGate;
	//AND, OR, NAND, NOR, XOR, NOT
	switch (gtype) {
	case AND:
		newGate = new And(g, 1);
		break;
	case OR:
		newGate = new Or(g, 1);
		break;
	case NAND:
		newGate = new Nand(g, 1);
		break;
	case NOR:
		newGate = new Nor(g, 1);
		break;
	case XOR:
		newGate = new Xor(g, 1);
		break;
	case NOT:
		newGate = new Not(g, 1);
		break;
	default:
		return NULL;
		break;
	}
	designGates.insert(make_pair(g, newGate));
	return newGate;
}

Gate* Design::addFindGate(int gtype, string g, int d) {
	if (designGates.find(g) != designGates.end()) {
		return designGates[g];
	}
	Gate* newGate;
	//AND, OR, NAND, NOR, XOR, NOT
	switch (gtype) {
	case AND:
		newGate = new And(g, d);
		break;
	case OR:
		newGate = new Or(g, d);
		break;
	case NAND:
		newGate = new Nand(g, d);
		break;
	case NOR:
		newGate = new Nor(g, d);
		break;
	case XOR:
		newGate = new Xor(g, d);
		break;
	case NOT:
		newGate = new Not(g, d);
		break;
	default:
		return NULL;
		break;
	}
	designGates.insert(make_pair(g, newGate));
	return newGate;
}

vector<Net*>* Design::getPINets() {
	vector<Net*>* newVect = new vector<Net*>();
	for (size_t i = 0; i < pis.size(); i++) {
		newVect->push_back(addFindNet(pis[i]));
	}
	return newVect;
}

vector<Net*>* Design::getPONets() {
	vector<Net*>* newVect = new vector<Net*>();
	for (size_t i = 0; i < pos.size(); i++) {
		newVect->push_back(addFindNet(pos[i]));
	}
	return newVect;
}

vector<Net*>* Design::getWireNets() {
	vector<Net*>* newVect = new vector<Net*>();
	for (map<string, Net*>::iterator it = designNets.begin(); it != designNets.end(); it++) {
		if (isPI(it->second)) {
			continue;
		}
		else if (isPO(it->second)) {
			continue;
		}		
		newVect->push_back(it->second);		
	}
	return newVect;
}

vector<Net*>* Design::allNets() {
	vector<Net*>* newVect = new vector<Net*>();
	for (map<string, Net*>::iterator it = designNets.begin(); it != designNets.end(); it++) {
		newVect->push_back(it->second);
	}
	return newVect;
}

vector<Gate*>* Design::allGates() {
	vector<Gate*>* newVect = new vector<Gate*>();
	for (map<string, Gate*>::iterator it = designGates.begin(); it != designGates.end(); it++) {	
		newVect->push_back(it->second);
	}
	return newVect;
}

/**
* To be implemented in Part 2.  For Part 1 just return NULL
*
* Performs a topological sorting of the nets in the design
*  and returns a dynamically allocated vector with pointers
*  to Net objects in a satisfactory topological order
*
* @return Pointer to a new vector storing Net pointers
*/
vector<Net*>* Design::toposort() {
	vector<Net*>* pOut = getPONets();
	vector<Net*>* pIn = getPINets();
	for (int i = 0; i < pIn->size(); i++) 
		pIn->at(i)->setDelay(0);
	
	map<string, int> colorMap;
	for (map<string, Net*>::iterator it = designNets.begin(); it != designNets.end(); ++it) {
		colorMap.insert(make_pair(it->first, WHITE));
	}
	vector<Net*>* fList = new vector<Net*>();
	for (int i = 0; i < pos.size(); i++) {
		if (colorMap[pos.at(i)] == WHITE) {
			dfs_visit(findNet(pos.at(i)), fList, colorMap);
		}
	}
	delete pOut;
	delete pIn;
	return fList;
}

/**
* Recreates the Verilog description of the design dumping
* it to the provided ostream
*
* @param[in] os Ostream representing a file, stdout, or stringstream
*               to which the Verilog description should be output
*/
void Design::dump(ostream &os) {
	vector<Net*>* piNets = getPINets();
	vector<Net*>* poNets = getPONets();
	vector<Net*>* intNets = getWireNets();
	vector<Gate*>* eGate = allGates();
	os << "// Comment" << endl;
	os << "module " << desname << "(";
	for (size_t i = 0; i < piNets->size(); i++) {
		os << piNets->at(i)->name() << ", ";
	}
	for (size_t i = 0; i < poNets->size(); i++) {
		os << poNets->at(i)->name();
		if (i == poNets->size() - 1) {
			os << ");" << endl;
		}
		else {
			os << ", ";
		}
	}
	for (size_t i = 0; i < piNets->size(); i++) {
		os << '\t' << "input " << piNets->at(i)->name() << ';' << endl;
	}
	for (size_t i = 0; i < poNets->size(); i++) {
		os << '\t' << "output " << poNets->at(i)->name() << ';' << endl;
	}
	for (size_t i = 0; i < intNets->size(); i++) {
		os << '\t' << "wire " << intNets->at(i)->name() << ';' << endl;
	}
	os << endl;
	for (size_t i = 0; i < eGate->size(); i++) {
		os << '\t';
		eGate->at(i)->dump(os);
		if (eGate->at(i)->getDelay() != 1)
			os << "#" << eGate->at(i)->getDelay() << " ";
		os << eGate->at(i)->name() << " (" << eGate->at(i)->getOutput()->name() << ", ";
		for (int j = 0; j < eGate->at(i)->getNumInputs(); j++) {
			os << eGate->at(i)->getInputs()->at(j)->name();
			if (j == eGate->at(i)->getNumInputs() - 1) {
				os << ");" << endl;
			}
			else {
				os << ", ";
			}
		}
	}
	os << "endmodule" << endl;
	delete piNets;
	delete poNets;
	delete intNets;
	delete eGate;
	
}

bool Design::isPI(Net *n) {
	for (size_t i = 0; i < pis.size(); i++) {
		if (designNets[pis[i]] == n) {
			return true;
		}
	}
	return false;
}

bool Design::isPO(Net *n) {
	for (size_t i = 0; i < pos.size(); i++) {
		if (designNets[pos[i]] == n) {
			return true;
		}
	}
	return false;
}

void Design::dfs_visit(Net *n, vector<Net *> *flist, map<string, int> &colormap) {
	
	colormap[n->name()] = GRAY;
	// find its driver and call its inputSize function
	for (int i = 0; i < n->getDrivers()->size(); i++) {
		for (int j = 0; j < n->getDrivers()->at(i)->getNumInputs(); j++) {
			if (colormap[n->getDrivers()->at(i)->getInputs()->at(j)->name()] == WHITE) {
				dfs_visit(n->getDrivers()->at(i)->getInputs()->at(j), flist, colormap);
			}
		}
	}
	colormap[n->name()] = BLACK;
	flist->push_back(n);
}

