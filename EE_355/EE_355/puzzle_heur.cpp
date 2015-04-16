#include "stdafx.h"
#include "puzzle_heur.h"
#include <cmath>

using namespace std;
// Manhattan
int PuzzleManhattanHeuristic::compute(const Board& b) {
	
	int dim = b.getDim();
	int expectedRow, expectedCol, actualRow, actualCol;
	int hScore = 0;
	// find the row and column for the tile
	for (int i = 0; i < b.getSize(); i++) {
		if (b.getTile(i) == 0) continue;
		expectedRow = b.getTile(i) / dim;
		expectedCol = b.getTile(i) % dim;
		actualRow = i / dim;
		actualCol = i % dim;
		hScore += abs(expectedRow - actualRow) + abs(expectedCol - actualCol);
	}

	return hScore;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b) {
	int hScore = 0;
	for (int i = 0; i < b.getSize(); i++) {
		if (b.getTile(i) != i) { // we are counting blank space as error as well
			hScore++;
		}
	}
	return hScore;
}

int PuzzleBFSHeuristic::compute(const Board& b) { 
	return 0; 
}
