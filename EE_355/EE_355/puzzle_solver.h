#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <vector>
#include <deque>
#include <set>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "heap.h"

class PuzzleSolver
{
 public:
  //*** Typedef for the open-list set.  Declare your open list variable as
  //***   PuzzleMoveHeap openlist;
  //*** when you write your code for the run() funciton
  typedef Heap<PuzzleMove*, PuzzleMoveScoreComp > PuzzleMoveHeap;

  //*** Typedef for the closed-list set.  Declare your closed list variable as
  //***   PuzzleMoveSet closedlist;
  //*** when you write your code for the run() funciton
  typedef std::set<PuzzleMove*, PuzzleMoveBoardComp> PuzzleMoveSet;

  PuzzleSolver();
  // Constructor (makes a copy of the Board and stores it in _b
  PuzzleSolver(const Board& b, PuzzleHeuristic *ph);

  // Destructor
  ~PuzzleSolver();

  // Run the A* search
  void run();

  // Return the solution deque
  std::deque<int> getSolution();

  // Return how many expansions were performed in the search
  int getNumExpansions();
 private:
  Board _b;
  std::deque<int> _solution;
  int _expansions;
  PuzzleHeuristic *_ph;
};

#endif
