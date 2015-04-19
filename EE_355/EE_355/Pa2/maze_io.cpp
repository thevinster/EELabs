#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "maze_io.h"

using namespace std;

/*************************************************
 * Open the file specified by filename, and read the 
 * maze into a dynamically allocated array.
 * 
 * Return the pointer to that array (don't delete it..
 * we'll do that in main() ).  Return NULL if
 * you are unable to open the file or can't read
 * the dimensions.
 *
 * We also pass in two pointers to integers. Fill 
 *  those values in with the number of rows and 
 *  columns read by from the file (first two value
 *  in the file)
 *
 *************************************************/

char * read_maze(char *filename, int *rows, int *cols )
{
	
	ifstream mFile("C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\maze3.in");
	if (mFile.fail()) {
		cout << "Cannot open File: " << filename << endl;
		return NULL;
	}
	int row, col;
	mFile >> row;
	if (mFile.fail()) {
		cout << "Unable to read in first integer" << endl;
		return NULL;
	}
	mFile >> col;
	if (mFile.fail()) {
		cout << "Unable to read in second integer" << endl;
		return NULL;
	}
	*rows = row;
	*cols = col;
	char* mazeArray = new char[row*col];
	for (int i = 0; i < (row*col); i++) {
		mFile >> mazeArray[i];
	}

	return mazeArray;
}

/*************************************************
 * Print the maze contents in a 2D format to the
 * screen
 *
 *************************************************/
void print_maze(char *maze, int rows, int cols)
{
	cout << "Shortest Path is: " << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << maze[i*cols + j];
		}
		cout << endl;
	}

}

/*************************************************
 * Write maze should open the file specified by 
 * filename and write the contents of the maze
 * array to the file with the dimensions on the first
 * line.
 *
 *************************************************/
void write_maze(char *filename, char *maze, int rows, int cols)
{
	ofstream out("C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\maze3.out");
	if (out.fail()) {
		cout << "Unable to open the output file " << filename << endl;
		return;
	}
	out << rows << " " << cols << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			out << maze[i*cols + j];
		}
		out << endl;
	}

}
