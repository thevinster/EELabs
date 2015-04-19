// PA1
/*********************************************************
* File name : tp.cpp
* Author    :
* Date      :
* Purpose   : Simulates the toilet-paper problem
* Notes     : None
*********************************************************/

#include "stdafx.h"
#include <iostream>   // Basic I/O => cin, cout, etc.
#include <cstdlib>    // Other helpful functions => rand(), RANDMAX
#include <ctime>

using namespace std;

// Prototype/declaration of a function that returns a
// uniform random number between [0,1]
double rand_uniform();

// Prototype/declaration of a function that will perform a single
// simulation of two rolls of paper and users
// Returns the number of squares left on the non-empty roll
int single_roll_sim(int N, double p);

int main(int argc, char *argv[])
{
	const int num_sims = 1000000;  // number of trials for our simulation

	int N;                // initial number of squares on each roll

	double p;             // probability of a big-chooser

	int total_squares; // for each trial we'll keeping a running sum
	// of the squares left on the non-empty roll

	// Do some error checking to make sure the user
	// entered the correct number of arguments to the program
	if (argc < 3){
		cout << "Usage: " << argv[0] << " N p" << endl;
		cout << "\tN = number of squares on each roll to start" << endl;
		cout << "\tp = probability of a big-chooser" << endl;
		//return 1;
	}

	//N = atoi(argv[1]);   // convert the argument to an integer
	//p = atof(argv[2]);   // convert the argument to a floating point

	N = 10;
	p = 0.5;
	srand(time(0));
	total_squares = 0;
	for (int i = 0; i < num_sims; i++) {
		total_squares += single_roll_sim(N, p);
	}

	cout << "Average number of squares left for N=" << N << ", p=" << p << " is " << (double)total_squares / num_sims << endl;
	cin.sync();
	cin.get();


	return 0;
}

// return the number of squares on the non-empty roll
int single_roll_sim(int N, double p)
{
	int roll1 = N;
	int roll2 = N;

	// Add your code here
	while (roll1 != 0 && roll2 != 0) {
		if (p >= rand_uniform()) {
			//big
			if (roll1 == roll2) {
				roll1--;
			}
			else if (roll1 > roll2) {
				roll1--;
			}
			else {
				roll2--;
			}
		}
		else {
			// little 
			if (roll1 == roll2) {
				roll1--;
			}
			else if (roll1 > roll2) {
				roll2--;
			}
			else {
				roll1--;
			}
		}
	}

	if (roll1 == 0) {
		return roll2;
	}
	else {
		return roll1;
	}

}

// returns a uniformly-distributed number in the range [0,1]
double rand_uniform()
{
	return static_cast<double>(rand()) / (RAND_MAX);
}

