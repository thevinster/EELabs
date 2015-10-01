#include "stdafx.h"
#include "net.h"

//vector<Gate*>* drivers;
//vector<Gate*>* loads;
//char val;
//string netname;
//int delay;

Net::Net(string n): netname(n) {
	drivers = new vector<Gate*>();
	loads = new vector<Gate*>();
}

Net::~Net() {
	// TODO: Delete drivers and loads
	delete drivers;
	delete loads;
}

string Net::name() const {
	return netname;
}

void Net::addDriver(Gate *g) {
	drivers->push_back(g);
}

void Net::addLoad(Gate *g) {
	loads->push_back(g);
}

vector<Gate*>* Net::getLoads() {
	return loads;
}

vector<Gate*>* Net::getDrivers() {
	return drivers;
}

/**
* Looks at the driver gates and input nets to those
*  gates to compute and return the value on this net
*
* @return Value produced on this net: '0','1','X'
*/
char Net::computeVal() {
	// if multiple drivers, output X
	size_t sz = drivers->size();
	if (sz == 0) {
		// primary input
		return val;
	}
	for (size_t i = 0; i < sz - 1; i++) {
		if (drivers->at(i)->eval() != drivers->at(i + 1)->eval()) {
			return 'X';
		}
	}
	return drivers->at(0)->eval();
}

/**
* Looks at the driver gates and input nets to those
*  gates to compute and return the time when this
*  net's value will be resolved
*
* @return Time when this net's value is resolved
*/
int Net::computeDelay() {
	int max = 0;
	for (int i = 0; i < drivers->size(); i++) {
		int tMax = drivers->at(i)->getDelay() + MaxInputs(i);
		if (tMax > max) {
			max = tMax;
		}
	}
	return max;
}

int Net::MaxInputs(int driverNum) {
	int max = -1;
	for (int j = 0; j < drivers->at(driverNum)->getNumInputs(); j++) {
		int netDelay = drivers->at(driverNum)->getInputs()->at(j)->getDelay();
		if (netDelay > max) {
			max = netDelay;
		}
	}
	return max;
}

// Debugging
void Net::printDriversLoads() {

}

