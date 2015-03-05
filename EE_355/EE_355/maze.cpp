#include "stdafx.h"
#include <iostream>
#include "maze_io.h"
using namespace std;

// Prototype for maze_search
int maze_search(char *, int, int);

int main(int argc, char *argv[])
{
  int rows, cols, result;
  char *mymaze;

  if(argc < 3){
    cerr << "Usage: ./maze in_filename out_filename" << endl;
    return 1;
  }

  mymaze = read_maze(argv[1], &rows, &cols);

  // For checkpoint 1, just leave maze_search() unedited
  //  and the program should read in the maze, print it
  //  and write it back to the output file
  result = maze_search(mymaze, rows, cols);

  if( result == 1 ){
    cout << "Path successfully found!" << endl;
    print_maze(mymaze,rows,cols);
    write_maze(argv[2],mymaze,rows,cols);
  }
  else if (result == 0) {
    cout << "No path could be found!" << endl;
  }
  else {
    cout << "Error occurred during search!" << endl;
  }

  delete [] mymaze;
  getchar();
  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if an error occurred (no start of finish
 *     cell present in the maze)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char *maze, int rows, int cols)
{
	// Find S and F
	int *trail = new int[rows*cols]; // this is your lookup table
	int *bfsList = new int[rows*cols];
	int head = 0, tail = 0;
	bool isFinishFound = false, isStartFound = false;
	for (int i = 0; i < (rows*cols); i++) {
		trail[i] = -1;
		if (maze[i] == 'S') {
			bfsList[0] = i;
			trail[i] = -2;
			tail++;
			isStartFound = true;
		}
		if (maze[i] == 'F') {
			isFinishFound = true;
		}
	}
	if (!isStartFound) {
		cout << "Cannot Find Start" << endl;
		return -1;
	}
	if (!isFinishFound) {
		cout << "Cannot Find Finish" << endl;
		return -1;
	}
	// Implement BFS
	while (tail - head > 0) {
		//int idx = trail[head];
		int r = bfsList[head] / cols;
		int c = bfsList[head] % cols;
		// North
		if (r != 0) {
			int northIdx = (r - 1)*cols + c;
			if (trail[northIdx] == -1) {
				if (maze[northIdx] == 'F') {		
					break; // headpointer will track where you are
				}
				else if (maze[northIdx] == '.') {
					bfsList[tail] = northIdx;
					trail[northIdx] = bfsList[head];
					tail++;
				}
			}
		}

		// West
		if (c != 0) {
			int westIdx = r*cols + (c - 1);
			if (trail[westIdx] == -1) {
				if (maze[westIdx] == 'F') {
					break;
				}
				else if (maze[westIdx] == '.') {
					bfsList[tail] = westIdx;
					trail[westIdx] = bfsList[head];
					tail++;
				}
			}
		}
		
		// South
		if (r != rows - 1) {
			int southIdx = (r + 1)*cols + c;
			if (trail[southIdx] == -1) {
				if (maze[southIdx] == 'F') {
					break;
				}
				else if (maze[southIdx] == '.') {
					bfsList[tail] = southIdx;
					trail[southIdx] = bfsList[head];
					tail++;
				}
			}
		}

		// East
		if (c != cols - 1) {
			int eastIdx = r*cols + (c + 1);
			if (trail[eastIdx] == -1) {
				if (maze[eastIdx] == 'F') {
					break;
				}
				else if (maze[eastIdx] == '.') {
					bfsList[tail] = eastIdx;
					trail[eastIdx] = bfsList[head];
					tail++;
				}
			}
		}
		head++;
	}
	
	if (tail == head) {
		cout << "cannot find shortest path" << endl;
		return 0;
	}
	// Change Shortest path to '*'s
	head = bfsList[head];
	while (trail[head] != -2) {
		maze[head] = '*';
		head = trail[head];
	}
	delete[] trail;
	delete[] bfsList;
	// Change appropriately after Checkpoint 1 is working
	return 1;
}
