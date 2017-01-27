//  Main program for testing

#include <iostream>
#include <string>
#include <cstdlib>

#include "wordPuzzle.h"

using namespace std;

int main()
{

// *****************************************************************
//  Headers...

	string	bars, stars;
	bars.append(65, '-');
	stars.append(65, '*');

	cout << bars << endl << "CS 302 - Assignment #6" << endl;
	cout << "Word Search Puzzle Solver" << endl;
	cout << endl;

// ------------------------------------------------------------------

	wordPuzzle pzl;

	if (!pzl.readDictionary("smallDictionary.txt")) {
		cout << "main: Read dictionary error." << endl;
		exit(1);
	}

	if (!pzl.readLetters("words1.txt")) {
		cout << "main: Read letters file error." << endl;
		exit(1);
	}

	cout << bars << endl;
	pzl.showTitle();
	cout << endl;
	pzl.printLetters();

	pzl.findWords();
	pzl.showWords();

	cout << endl;
	cout << "Stats:" << endl;
	cout << "Word Count: " << pzl.showWordCount() << endl;
	cout << endl;

	pzl.destroyTree();


// ------------------------------------------------------------------

{
	wordPuzzle	pzl2;

	if (!pzl2.readDictionary("dictionary.txt")) {
		cout << "main: Read dictionary error." << endl;
		exit(1);
	}

	if (!pzl2.readLetters("words2.txt")) {
		cout << "main: Read letters file error." << endl;
		exit(1);
	}

	cout << bars << endl;
	pzl2.showTitle();
	cout << endl;
	pzl2.printLetters();

	pzl2.findWords();
	pzl2.showWords();

	cout << endl;
	cout << "Stats:" << endl;
	cout << "Word Count: " << pzl2.showWordCount() << endl;
	cout << endl;
}

// ------------------------------------------------------------------

	wordPuzzle	pzl3;

	if (!pzl3.readDictionary("dictionary.txt")) {
		cout << "main: Read dictionary error." << endl;
		exit(1);
	}

	if (!pzl3.readLetters("words3.txt")) {
		cout << "main: Read letters file error." << endl;
		exit(1);
	}

	cout << bars << endl;
	pzl3.showTitle();
	cout << endl;
	pzl3.printLetters();

	pzl3.findWords();
	pzl3.showWords();

	cout << endl;
	cout << "Stats:" << endl;
	cout << "Word Count: " << pzl3.showWordCount() << endl;
	cout << endl;

// ------------------------------------------------------------------

	wordPuzzle	pzl4;

	if (!pzl4.readDictionary("dictionary.txt")) {
		cout << "main: Read dictionary error." << endl;
		exit(1);
	}

	if (!pzl4.readLetters("words4.txt")) {
		cout << "main: Read letters file error." << endl;
		exit(1);
	}

	cout << bars << endl;
	pzl4.showTitle();
	cout << endl;
	pzl4.printLetters();

	pzl4.findWords();
	pzl4.showWords();

	cout << endl;
	cout << "Stats:" << endl;
	cout << "Word Count: " << pzl4.showWordCount() << endl;
	cout << endl;
	cout << bars << endl << "Game Over, thank you for playing." << endl;
	return 0;
}

