#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int size, initMoves, seed, heur;

  size = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);
  heur = atoi(argv[4]);
  size = 3;//4;
  initMoves = 30;//20;
  seed = 1537;//1711;
  heur = 0;//2;

  Board b(size,initMoves,seed);

  PuzzleHeuristic* ph;
  if(heur == 0){
    ph = new PuzzleBFSHeuristic;
  }
  else if(heur == 1){
    ph = new PuzzleOutOfPlaceHeuristic;
  }
  else {
    ph = new PuzzleManhattanHeuristic;
  }

  //*********** Implement the gameplay here
  int input;
  while (true) {
	  cout << b << endl;
	  cout << "Enter a tile number to move or -1 for a cheat: ";
	  cin >> input;
	  if (input == 0) { 
		  delete ph;
		  return 0; 
	  }
	  else if (input == -1) {
		  PuzzleSolver pSolver(b, ph);
		  pSolver.run();
		  cout << "Try this sequence: "<< endl;
		  std::deque<int> soln = pSolver.getSolution();
		  for (std::deque<int>::iterator it = soln.begin(); it != soln.end(); ++it) {
			  cout << *it << " ";
		  }
		  cout << endl;
		  cout << "(Expansions = " << pSolver.getNumExpansions() << ")" << endl;
		  // PuzzleSolver dies here
	  }
	  else {
		  b.move(input);
	  }
	  if (b.solved()) {
		  delete ph;
		  return 0;
	  }
	  cout << endl;
  }

  return 0;
}
