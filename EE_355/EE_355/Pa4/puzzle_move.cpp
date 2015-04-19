#include "stdafx.h"
#include "puzzle_move.h"

using namespace std;

PuzzleMove::PuzzleMove() {

}

PuzzleMove::PuzzleMove(Board* board) {
	// What's happening here is that when you delete initBoard, it will delete PuzzleSolver's Board and we do call destructor on puzzle solver after outputting the expansions which will then destroy Board's object since it was delcared as a member in its class
	b = new Board(*board); // we don't want to reference the puzzle_solver's one
	//b = board;
	tileMove = g = h = 0;
	prev = NULL;
}

PuzzleMove::PuzzleMove(int tile, Board *board, PuzzleMove *parent) {
	tileMove = tile;
	b = board;
	prev = parent;
	g = (parent->g) + 1;
	h = 0;
}

PuzzleMove::~PuzzleMove() {
	//delete prev; don't want to delete this, prev is not allocated with new
	delete b;
}

bool PuzzleMove::operator<(const PuzzleMove& p) const {
	// want to comapre the f value 
	// and if the f value is the same, we take the h value to compare in the struct
	int f_lhs = g + h;
	int f_rhs = p.g + p.h;
	/*if (f_lhs < f_rhs) {
		return true;
	}
	else if (f_lhs == f_rhs) {
		if (h < p.h) {
			return true;
		}
	}
	return false;*/
	return ((f_lhs < f_rhs) || ((f_lhs == f_rhs) && (h < p.h)));
}

void PuzzleMove::score(PuzzleHeuristic* ph) {
	// update the g and h values accordingly to its ph 
	//cout << *b << endl;
	h = ph->compute(*b);
}