#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;

Board::Board() {
	
}

Board::Board(int size, int numInitMoves, int seed)
{
	_size = size*size;
	_tiles = new int[_size];
	int dim = static_cast<int>(sqrt(_size));
	srand(seed);
	for (int i = 0; i < _size; i++){
		_tiles[i] = i;
	}
	int blankLoc = 0;
	while (numInitMoves > 0){
		int r = rand() % 4;
		int randNeighbor = -1;
		if (r == 0){
			int n = blankLoc - dim;
			if (n >= 0){
				randNeighbor = n;
			}
		}
		else if (r == 1){
			int w = blankLoc - 1;
			if (blankLoc % dim != 0){
				randNeighbor = w;
			}
		}
		else if (r == 2){
			int s = blankLoc + dim;
			if (s < _size){
				randNeighbor = s;
			}
		}
		else {
			int e = blankLoc + 1;
			if (blankLoc % dim != dim - 1){
				randNeighbor = e;
			}
		}
		if (randNeighbor > -1){
			_tiles[blankLoc] = _tiles[randNeighbor];
			_tiles[randNeighbor] = 0;
			blankLoc = randNeighbor;
			numInitMoves--;
		}
	}
}

Board::Board(const Board &b) {
	///TODO: Need to do a deep copy on the board values 
	_size = b._size;
	_tiles = new int[_size];
	for (int i = 0; i < _size; i++) {
		// perform the deep copy
		_tiles[i] = b._tiles[i];
	}
}

Board::~Board() {
	///TODO: deallocate any piece of memory
	delete[] _tiles;
}

void Board::move(int tile)
{
	int dim = static_cast<int>(sqrt(_size));
	int tr, tc, br, bc; // tile row, blank row?

	// find the tile
	int i = -1;
	while (_tiles[++i] != tile);

	tr = i / dim;
	tc = i % dim;

	// find the blank
	int j = -1;
	while (_tiles[++j] != 0);
	br = j / dim;
	bc = j % dim;

	// if they aren't next to each other just return
	if (abs(static_cast<double>(tr - br)) + abs(static_cast<double>(tc - bc)) != 1){
		cout << "Invalid move of tile " << tile << " at ";
		cout << tr << "," << tc << " and blank spot at ";
		cout << br << "," << bc << endl;
		return;
	}
	// Swap tile and blank spot
	_tiles[j] = tile;
	_tiles[i] = 0;
}

// Write the other member functions for this class
map<int, Board*> Board::potentialMoves() const {
	map<int, Board*> moveMap;
	// figure out what moves you can that is next t blank spot
	int dim = static_cast<int>(sqrt(_size));
	// find the blank
	int j = -1;
	while (_tiles[++j] != 0);
	int br = j / dim;
	int bc = j % dim;

	if (br != 0) {
		// North is a potential move
		Board *bNorth = new Board(*this);
		int idx = dim*(br - 1) + bc;
		bNorth->move(_tiles[idx]);
		moveMap.insert(make_pair(_tiles[idx], bNorth));
	}

	if (br != dim - 1) {
		// South is a potential move
		Board *bSouth = new Board(*this);
		int idx = dim*(br + 1) + bc;
		bSouth->move(_tiles[idx]);
		moveMap.insert(make_pair(_tiles[idx], bSouth));
	}

	if (bc != 0) {
		// West is a potential move
		Board *bWest = new Board(*this);
		int idx = dim*br + (bc - 1);
		bWest->move(_tiles[idx]);
		moveMap.insert(make_pair(_tiles[idx], bWest));
	}

	if (bc != dim - 1) {
		// East is a potential move
		Board *bEast = new Board(*this);
		int idx = dim*br + (bc + 1);
		bEast->move(_tiles[idx]);
		moveMap.insert(make_pair(_tiles[idx], bEast));
	}

	return moveMap;
}

bool Board::solved() const {
	for (int i = 0; i < _size; i++) {
		if (_tiles[i] != i) {
			return false;
		}
	}
	return true;
}

int Board::getTile(int loc) const {
	return _tiles[loc];
}

int Board::getSize() const {
	return _size;
}

int Board::getDim() const {
	return static_cast<int>(sqrt(_size));
}

bool Board::operator<(const Board& rhs) const {
	for (int i = 0; i < _size; i++) {
		if (_tiles[i] < rhs._tiles[i]) {
			// rhs is bigger than lhs
			return true;
		}
		else if (_tiles[i] > rhs._tiles[i]) {
			// rhs is smaller than lhs
			return false;
		}
	}
	return false;
}

// Not part of the class functions
ostream& operator<<(ostream &os, const Board &b) {
	// Display board to the console
	// can't make a copy of os since ostream is globally one object
	int dim = static_cast<int>(sqrt(b._size));
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			if (b._tiles[dim*r + c] == 0) {
				os << fixed << setw(3) << " ";
				continue;
			}
			os << fixed << setw(3) << b._tiles[dim*r + c];
			
		}
		os << endl;
	}
	return os;
}