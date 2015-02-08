// stringdemo.cpp
/*
#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
	char mystring[80] = "Electrical Engineering";
	char yourstring[80];
	char* astring = 0;

	//yourstring = mystring;
	//strncpy(astring, mystring, 80);
	
	astring = mystring; // make a copy?
	strncpy(yourstring, mystring, 80); // make a copy?EE 355 Lab 4 - Party Like A Char Star
	
	cout << astring << endl;
	cout << yourstring << endl;
	
	mystring[0] = '*'; // which one actually made a copy?
	cout << astring << endl;
	cout << yourstring << endl;
	
	cin.sync();
	cin.get();
	return 0;
}
*/

// hangman.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <ctype.h>

using namespace std;

// Prototype
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
/*const*/ char* wordBank[] = { "computer", "president", "trojan", "program", "coffee",
"library", "football", "popcorn", "science", "engineer" };

const int numWords = 10;

int main()
{
	srand(time(0));
	char guess;
	bool wordGuessed = false;
	int numTurns = 10;

	/*for (int j = 0; j < 10; j++) {
		cout << wordBank[j] << endl;
	}*/
	
	// Pick a random word from the wordBank
	char* targetWord = wordBank[rand() % 10];

	// More initialization code as needed
	char word[80];  // a blank array to use to build up the answer
	// It should be initialized with *'s and then
	//  change them to the actual letters when the 
	//  user guesses the letter
	for (int i = 0; i < strlen(targetWord); i++) {
		word[i] = '*';
	}
	word[strlen(targetWord)] = '\0';

	// An individual game continues until a word
	//  is guessed correctly or 10 turns have elapsed
	while (strcmp(word, targetWord) && numTurns != 0) {
		cout << "Current word: " << word << endl;
		cout << numTurns << " remain...Enter a letter to guess: " << endl;
		cin >> guess; // user could enter a 7 or multiple characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl;
		
		if (!isalpha(guess)) {
			cout << "Please enter a valid letter" << endl;
			continue;
		}
		
		if (!processGuess(word, targetWord, guess)) {
			numTurns--;
		}
	}

	// Print out end of game status
	if (numTurns == 0) {
		cout << "Too many turns...You lose!" << endl;
	}
	else {
		cout << "The word was: " << targetWord << ". You win!" << endl;
	}
	cin.sync();
	cin.get();
	return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
	bool isLetterFound = false;
	for (int i = 0; i < strlen(targetWord); i++) {
		if (targetWord[i] == guess) {
			if (word[i] == guess) {
				cout << "You already guessed the word!" << endl;
				return 1;
			}
			else {
				word[i] = guess;
				isLetterFound = true;
			}
		}
	}
	if (isLetterFound) {
		return 1;
	}
	else {
		return 0;
	}

}
