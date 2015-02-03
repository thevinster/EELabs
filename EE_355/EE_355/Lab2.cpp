// Lab2
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {

	double t, r, c, Vs;
	double tempTime, Vc;

	cout << "Vs (volts): ";
	cin >> Vs;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Failed to Parse the value. Please enter valid values" << endl;
		cout << "Vs (volts): ";
		cin >> Vs;
	}

	cout << "R (ohms): ";
	cin >> r;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Failed to Parse the value. Please enter valid values" << endl;
		cout << "R (ohms): ";
		cin >> r;
	}

	cout << "C (Farads): ";
	cin >> c;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Failed to Parse the value. Please enter valid values" << endl;
		cout << "C (Farads): ";
		cin >> c;
	}

	cout << "Enter simulation time: ";
	cin >> t;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Failed to Parse the value. Please enter valid values" << endl;
		cout << "Enter simulation time: ";
		cin >> t;
	}

	cout << setw(15) << "Time(s)" << setw(15) << "Cap Voltage" << endl;
	cout << setw(15) << "_______" << setw(15) << "___________" << endl;
	// since we are going from 0 to T in T/25, we will get 26 steps
	double timeAt10 = NULL;
	double timeAt90 = NULL;
	for (int i = 0; i <= 25; i++) {
		tempTime = i / 25.0 * t;
		Vc = Vs * (1 - exp(-tempTime / (r*c)));
		cout << fixed << setprecision(2) << setw(15) << tempTime;
		cout << fixed << setprecision(2) << setw(15) << Vc << endl;
		if (timeAt10 == NULL) {
			if (Vc >= 0.1*Vs) {
				timeAt10 = tempTime;
			}
		}
		if (timeAt90 == NULL) {
			if (Vc >= 0.9*Vs) {
				timeAt90 = tempTime;
			}
		}
	}

	if (timeAt90 == NULL || timeAt10 == NULL) {
		cout << "No rise-time available" << endl;
	}
	else {
		cout << "Rise Time: " << timeAt90 - timeAt10 << " seconds" << endl;
	}

	cin.sync();
	cin.get();
	return 0;
}