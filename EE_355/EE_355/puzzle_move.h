#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include <functional>
#include "puzzle_heur.h"
#include "board.h"

using namespace std;

struct PuzzleMove
{
  // Data members are public by default in a struct
  int tileMove;  // tile moved to reach the Board b
  Board *b;      // Pointer to a board representing the updated state
  int g;         // distance from the start board
  int h;         // heuristic distance to the goal
  PuzzleMove *prev;  // Pointer to parent PuzzleMove

  PuzzleMove();
  // Constructor for first Move (initial board) with no parent or tileMove
  PuzzleMove(Board* board);

  // Constructor for subsequent search boards 
  // (i.e. those returned by Board::potentialMoves() )
  PuzzleMove(int tile, Board *board, PuzzleMove *parent);

  // Destructor
  ~PuzzleMove();

  // Compare to PuzzleMoves based on f distance 
  //  (needed for priority queue maintainenance)
  bool operator<(const PuzzleMove& p) const;

  void score(PuzzleHeuristic* ph);

};


// Leave this alone and don't touch it!
struct PuzzleMoveScoreComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    // Add code to check if m1's f-score is less than m2's by utilizing
    //  the PuzzleMove's operator<()
    return *m2 < *m1;
  }
};

struct PuzzleMoveBoardComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    // Add code to check if m1's board is "less-than" m2's board by 
    // using the Board class' operator<()
    return (*(m1->b) < *(m2->b));
  }
};

#endif
