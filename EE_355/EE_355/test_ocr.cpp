#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include "character.h"
#include "point.h"
#include "bmplib.h"

using namespace std;

#define THRESH 80

unsigned char image[SIZE][SIZE];		// Input Image Data Array
unsigned char explored[SIZE][SIZE];		// 
int lut[256][256];
vector<Character> charFound;

// Function Prototypes
void find_bounding_box(int &ulr, int &ulc, int &height, int &width);

int main(int argc, char *argv[])
{
	/*if (argc < 3) {
		cout << "Usage: " << argv[0] << " filename N" << endl;
		return
	}*/
	// read in the file into the image
	//readGSBMP(argv[1], image);
	readGSBMP("C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\ocr4.bmp", image);

	// convert to absolute black/white
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			if (image[row][col] > THRESH) { // white
				image[row][col] = 255;
			}
			else { // black
				image[row][col] = 0;
			}
			lut[row][col] = -1;
		}
	}
	
	/// TODO:
	/// Make sure we we have our bounding box coordinates so we don't capture any char twice
	int height, width;
	for (int r = 0; r < SIZE; r++) {
		
		for (int c = 0; c < SIZE; c++) {	
			int sr = r;
			int sc = c;
			int er = r;
			int ec = c;
			if (image[r][c] == 0 && lut[r][c] == -1) {		
				find_bounding_box(sr, sc, height, width);
				Character tempCharacter(image, sr, sc, height, width);
				tempCharacter.get_bounding_box(sr, sc, er, ec);
#ifdef DEBUG
				cout << "this block is working" << endl;
				for (int i = sc; i < ec + 1; i++) {
					image[sr][i] = 128;
					image[er][i] = 128;
				}

				for (int j = sr; j < er + 1; j++) {
					image[j][sc] = 128;
					image[j][ec] = 128;
				}
#endif
				// set all of lut to -2
				for (int ix = sr; ix < er + 1; ix++) {
					for (int iy = sc; iy < ec + 1; iy++) {
						lut[ix][iy] = -2;
					}
				}
				
				charFound.push_back(tempCharacter);
		
			}
		}
		
	}

	for (int i = 0; i < charFound.size(); i++) {
		charFound.at(i).perform_tests();
		charFound.at(i).classify();
		charFound.at(i).print_calculations(i + 1);
	}
	getchar();
	//writeGSBMP("C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\ocr4out.bmp", image);

	return 0;
}

void find_bounding_box(int &ulr, int &ulc, int &height, int &width) {
	
	int lrr = ulr;
	int lrc = ulc;
	// BFS
	deque<int> bfsList;
	int lut[256][256]; 
	// reset our lut to all -1 except ulr, and ulc
	for (int i = 0; i < 256 * 256; i++) {
		*((int*)lut + i) = -1;
		if (i == ulr * 256 + ulc) {
			*((int*)lut + i) = -2;
			bfsList.push_back(i);
		}
	}

	while (bfsList.size() > 0) {
		int r = bfsList.front() / 256;
		int c = bfsList.front() % 256;
		// N S E W NW SW SE NE
		// North
		if (r != 0) {
			if (lut[r - 1][c] == -1) { // unexplored
				lut[r - 1][c] = -2;
				if (image[r - 1][c] == 0) { // see if it's black
					bfsList.push_back((r - 1) * 256 + c);
					if (r - 1 < ulr)
						ulr = r - 1;
				}
			}
		}

		// South
		if (r != 255) {
			if (lut[r + 1][c] == -1) {
				lut[r + 1][c] = -2;
				if (image[r + 1][c] == 0) {
					bfsList.push_back((r + 1) * 256 + c);
					if (r + 1 > lrr)
						lrr = r + 1;
				}
			}
		}

		// East
		if (c != 255) {
			if (lut[r][c + 1] == -1) {
				lut[r][c + 1] = -2;
				if (image[r][c + 1] == 0) {
					bfsList.push_back(r * 256 + (c + 1));
					if (c + 1 > lrc)
						lrc = c + 1;
				}
			}
		}

		// West
		if (c != 0) {
			if (lut[r][c - 1] == -1) {
				lut[r][c - 1] = -2;
				if (image[r][c - 1] == 0) {
					bfsList.push_back(r * 256 + (c - 1));
					if (c - 1 < ulc)
						ulc = c - 1;
				}
			}
		}

		// NorthWest
		if (r != 0 && c != 0) {
			if (lut[r - 1][c - 1] == -1) {
				lut[r - 1][c - 1] = -2;
				if (image[r - 1][c - 1] == 0) {
					bfsList.push_back((r - 1) * 256 + (c - 1));
					if (r - 1 < ulr)
						ulr = r - 1;
					if (c - 1 < ulc)
						ulc = c - 1;
				}
			}
		}

		// SouthWest
		if (r != 255 && c != 0) {
			if (lut[r + 1][c - 1] == -1) {
				lut[r + 1][c - 1] = -2;
				if (image[r + 1][c - 1] == 0) {
					bfsList.push_back((r + 1) * 256 + (c - 1));
					if (r + 1 > lrr) {
						lrr = r + 1;
					}
					if (c - 1 < ulc) {
						ulc = c - 1;
					}
				}
			}
		}

		// SouthEast
		if (r != 255 && c != 255) {
			if (lut[r + 1][c + 1] == -1) {
				lut[r + 1][c + 1] = -2;
				if (image[r + 1][c + 1] == 0) {
					bfsList.push_back((r + 1) * 256 + (c + 1));
					if (r + 1 > lrr)
						lrr = r + 1;
					if (c + 1 > lrc)
						lrc = c + 1;
				}
			}
		}

		// NorthEast
		if (r != 0 && c != 255) {
			if (lut[r - 1][c + 1] == -1) {
				lut[r - 1][c + 1] = -2;
				if (image[r - 1][c + 1] == 0) {
					bfsList.push_back((r - 1) * 256 + (c + 1));
					if (r - 1 < ulr)
						ulr = r - 1;
					if (c + 1 > lrc)
						lrc = c + 1;
				}
			}
		}
		bfsList.pop_front();
	}

	height = lrr - ulr + 1;
	width = lrc - ulc + 1;
}