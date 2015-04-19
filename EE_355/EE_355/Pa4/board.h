#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <functional>

using namespace std;

class Board
{
public:
	Board();
	// Init a board of given size and scramble it with numInitMoves 
	// by moving the space tile with a randomly chosen direction N, W, S, E
	// some of which may be invalid, in which case we skip that move
	Board(int size, int numInitMoves, int seed);

	// Copy constructor
	Board(const Board &b);

	// Destructor
	~Board();

	// Swaps the blank with the specified tile
	void move(int tile);

	// Generate potential moves and fill in the map with 
	// Key=tile, Value=Ptr to corresponding Board
	// Clear the moveMap as the first order of business.
	//void potentialMoves(map<int, Board*> &moveMap); 
	map<int, Board*> potentialMoves() const;

	// Returns true if the board is solved, false otherwise
	bool solved() const;

	// Operators
	friend ostream& operator<<(ostream &os, const Board &b);
	bool operator<(const Board& rhs) const;

	// Accessors
	// returns tile at location loc in the array
	int getTile(int loc) const;
	// returns the size of the array (i.e. board)
	int getSize() const;
	// retruns the dimension of a side of the board
	int getDim() const;

private:
	int *_tiles; // Will point to an array
	int _size;   // Size of the array
};


#endif
