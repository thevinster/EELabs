#include "stdafx.h"
#include "gates.h"
#include "net.h"

//vector<Net*>* inputs;
//Net* output;
//string inst_name;
//int delay;

Gate::Gate(string n): inst_name(n) {
	inputs = new vector<Net*>();
}

Gate::Gate(string n, int d): inst_name(n), delay(d) {
	inputs = new vector<Net*>();
}

/**
* Destructor
*/
Gate::~Gate() {
	//TODO: Delete all dynamically allocated stuff
	delete inputs;
}

string Gate::name() const {
	return inst_name;
}

int Gate::getDelay() const {
	return delay;
}

void Gate::addInput(Net *n) {
	inputs->push_back(n);
}

vector<Net*>* Gate::getInputs() {
	return inputs;
}

/**
* Sets the output net of this gate
*
* @param[in] n Pointer to the output Net
*/
void Gate::addOutput(Net *n) {
	output = n;
}

Net* Gate::getOutput() const {
	return output;
}

int Gate::getNumInputs() const {
	return (int) inputs->size();
}

//=============================AND GATE===================================
And::And(string n, int d): Gate(n,d) {

}

And::~And() {

}

char And::eval() {
	bool seenZero, seenX;
	seenZero = seenX = false;
	for (int i = 0; i < getNumInputs(); i++) {
		if (inputs->at(i)->getVal() == '0') {
			seenZero = true;
		}
		else if (inputs->at(i)->getVal() == 'X') {
			seenX = true;
		}
		if (seenZero) return '0';
	}
	if (!seenZero && seenX) return 'X';
	else return '1';
}

void And::dump(ostream &os) {
	os << "and ";
}

//==================================Or=================================
Or::Or(string n, int d): Gate(n, d) {

}

Or::~Or() {

}

char Or::eval() {
	bool seenOne, seenX;
	seenOne = seenX = false;
	for (int i = 0; i < getNumInputs(); i++) {
		if (inputs->at(i)->getVal() == '1') {
			seenOne = true;
		}
		else if (inputs->at(i)->getVal() == 'X') {
			seenX = true;
		}
		if (seenOne) return '1';
	}
	if (!seenOne && seenX) return 'X';
	else return '0';
}

void Or::dump(ostream &os) {
	os << "or ";
}

//==========================Nor================================
Nor::Nor(string n, int d): Gate(n,d) {

}

Nor::~Nor() {

}

char Nor::eval() {
	bool seenOne, seenX;
	seenOne = seenX = false;
	for (int i = 0; i < getNumInputs(); i++) {
		if (inputs->at(i)->getVal() == '1') {
			seenOne = true;
		}
		else if (inputs->at(i)->getVal() == 'X') {
			seenX = true;
		}
		if (seenOne) return '0';
	}
	if (!seenOne && seenX) return 'X';
	else return '1';
}

void Nor::dump(ostream &os) {
	os << "nor ";
}
//===============================Nand==============================
Nand::Nand(string n, int d): Gate(n,d) {

}

Nand::~Nand() {

}

char Nand::eval() {
	bool seenZero, seenX;
	seenZero = seenX = false;
	for (int i = 0; i < getNumInputs(); i++) {
		if (inputs->at(i)->getVal() == '0') {
			seenZero = true;
		}
		else if (inputs->at(i)->getVal() == 'X') {
			seenX = true;
		}
		if (seenZero) return '1';
	}
	if (!seenZero && seenX) return 'X';
	else return '0';
}

void Nand::dump(ostream &os) {
	os << "nand ";
}
//===========================Xor==========================
Xor::Xor(string n, int d): Gate(n, d) {

}

Xor::~Xor() {

}

char Xor::eval() {
	int sum = 0;
	for (int i = 0; i < getNumInputs(); i++) {
		if (inputs->at(i)->getVal() == 'X') {
			return 'X';
		}	
		sum += inputs->at(i)->getVal() - '0';
	}
	return (sum % 2) + '0';
}

void Xor::dump(ostream &os) {
	os << "xor ";
}
//============================Not=======================
Not::Not(string n, int d): Gate(n,d) {

}

Not::~Not() {

}

char Not::eval() {
	for (int i = 0; i < getNumInputs(); i++) {
		if (inputs->at(i)->getVal() == 'X') {
			return 'X';
		}
		else if (inputs->at(i)->getVal() == '1') {
			return '0';
		}
		else {
			return '1';
		}
	}
	return 'X';
}

void Not::dump(ostream &os) {
	os << "not ";
}

