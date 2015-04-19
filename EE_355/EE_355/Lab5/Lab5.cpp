// Lab5 
// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Prototype
void permute(char items[], int len);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
//const char *wordBank[] = { "computer", "president", "trojan", "program", "coffee",
//"library", "football", "popcorn", "science", "engineer" };

//const int numWords = 10;

int main(int argc, char *argv[])
{
	int numWords;
	/*if (argc < 2) {
		cout << "Usage: " << argv[0] << " filename" << endl;
		cout << "\tfilename = extension in .txt" << endl;
		getchar();
		return 1;
	}*/
	
	//ifstream mFile(argv[1]);
	ifstream mFile("C:/Users/Vincent/Documents/GitHub/EELabs/EE_355/x64/Debug/wordbank.txt");
	// the above statement is needed for debugging purposes
	if (mFile.fail()) {
		cout << "Unable to open file: " << argv[1] << endl;
		getchar();
		return 1;
	}

	mFile >> numWords;
	if (mFile.fail()) {
		cout << "Unable to read in number" << endl;
		mFile.close();
		getchar();
		return 1;
	}

	char **wordBank = new char*[numWords];
	char buffer[41];
	char *lenWord;
	for (int i = 0; i < numWords; i++) {
		mFile >> buffer;
		cout << buffer << endl;
		lenWord = new char[strlen(buffer)+1];
		strcpy(lenWord, buffer); // adds null for you
		wordBank[i] = lenWord;
	}

	mFile.close();

	srand(time(0));
	char guess[80];

	bool wordGuessed = false;
	int numTurns = 10;

	// Pick a random word from the wordBank
	int target = rand() % numWords;
	int targetLen = strlen(wordBank[target]);

	// More initialization code
	char* word = new char[targetLen + 1];
	strcpy(word, wordBank[target]);
	permute(word, targetLen);

	// An individual game continues until a word
	//  is guessed correctly or 10 turns have elapsed
	while (!wordGuessed && numTurns > 0){
		cout << "\nCurrent word:  " << word << endl;
		cin >> guess;
		wordGuessed = (strncmp(guess, wordBank[target], targetLen + 1) == 0);
		numTurns--;
	}
	if (wordGuessed){
		cout << "You win!" << endl;
	}
	else {
		cout << "Too many turns...You lose!" << endl;
	}
	delete[] word;
	for (int i = 0; i < numWords; i++) {
		delete[] wordBank[i]; // the last wordBank would delete lenWord
	}
	delete[] wordBank; 
	getchar();
	return 0;
}

// Scramble the letters
void permute(char items[], int len)
{
	for (int i = len - 1; i > 0; --i){
		int r = rand() % i;
		int temp = items[i];
		items[i] = items[r];
		items[r] = temp;
	}

}
