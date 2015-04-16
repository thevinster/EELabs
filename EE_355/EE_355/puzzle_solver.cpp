#include "stdafx.h"
#include "puzzle_solver.h"

using namespace std;

PuzzleSolver::PuzzleSolver() {
	_ph = NULL;
}

// Constructor (makes a copy of the Board and stores it in _b
PuzzleSolver::PuzzleSolver(const Board& b, PuzzleHeuristic *ph): _b(b) {
	//_b = b; this will only copy pointer and size, shallow copy...
	_ph = ph;
	_expansions = 0;
}

// Destructor
PuzzleSolver::~PuzzleSolver() {
}

void PuzzleSolver::run() {
	PuzzleMoveHeap openList;
	PuzzleMoveSet closedList;
	map<int, Board*> moveMap;
	PuzzleMove* initBoard = new PuzzleMove(&_b);
	openList.push(initBoard);
	closedList.insert(initBoard);
	while (!openList.empty() && !_b.solved()) {
		PuzzleMove* top = openList.top();
		openList.pop(); // this still exists in memeory
		if (top->b->solved()) {
			// trace back to solution
			while (top->prev != NULL) {
				_solution.push_front(top->tileMove);
				top = top->prev;
			}
			break;
		}
		moveMap = top->b->potentialMoves();
		
		for (map<int, Board*>::iterator it = moveMap.begin(); it != moveMap.end(); ++it) {
			PuzzleMove *s = new PuzzleMove(it->first, it->second, top);
			if (closedList.find(s) == closedList.end()) {
				s->score(_ph);
				openList.push(s);
				closedList.insert(s);
				_expansions++;
			}
			else {
				delete s;
			}
		}
	}
	// closeList contains all my expansions
	for (PuzzleMoveSet::iterator it = closedList.begin(); it != closedList.end(); ++it) {
		delete *it;
		//it = closedList.erase(it); // lost the handle to it so it can't incremenet it		
	}
	//closedList.erase(closedList.begin(), closedList.end());
}

std::deque<int> PuzzleSolver::getSolution() {
	return _solution;
}

int PuzzleSolver::getNumExpansions() {
	return _expansions;
}

