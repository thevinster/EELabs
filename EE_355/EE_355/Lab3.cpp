/// prime23.cpp
#include "stdafx.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
	int num;
	int numTwo = 0;
	int numThree = 0;
	cout << "Enter a positive integer: ";
	cin >> num;
	assert(num > 0);
	
	while ((num % 2) == 0 || (num % 3)  == 0) {
		if (num % 6 == 0) {
			numTwo++;
			numThree++;
			num = num / 6;
		}
		else if (num % 3 == 0) {
			numThree++;
			num = num / 3;
		}
		else if (num % 2 == 0) {
			numTwo++;
			num = num / 2;
		}
	}

	if (num == 1) {
		cout << "Yes" << endl;
		cout << "Twos=" << numTwo << ", Threes=" << numThree << endl;
	}
	else {
		cout << "No" << endl;
	}

	cin.sync();
	cin.get();
	return 0;
}

// Tri.cpp
#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.14159265
int main() {
	double theta;	

	cout << "Please enter in a value of theta between 15 and 75: ";
	cin >> theta;
	for (int i = 1; i <= 30; i++) {
		int x = round(i * tan(theta * PI/180.0));
		if (x <= 30 && x >= 20) {
			x = 20;
		}
		for (int j = 0; j < x; j++) {
			cout << "*";
		}
		cout << endl;
	}


	cin.sync();
	cin.get();
	return 0;
}
