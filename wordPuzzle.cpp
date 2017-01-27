/*					   Richard Bromley 5001075854

						    puzzle.cpp
  
Created by Richard Bromley on 1/2/15. */

#ifndef bromley_PUZZLEC
#define bromley_PUZZLEC

#include "wordPuzzle.h"


using namespace std;

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

wordPuzzle::wordPuzzle()
{
	title = "";
	order = 0;
	pointer = NULL;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

wordPuzzle::~wordPuzzle()
{
	destroyTree();
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

void wordPuzzle::destroyTree()
{
	avl.destroyTree();
	trie.destroyTree();
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

void wordPuzzle::wordsFound(int x, int y, string entry)
{
	string newWord = "";
	char xString [5];
	char yString [5];

	sprintf(xString, "%d", x);
	sprintf(yString, "%d", y);

	newWord.append("(");
	newWord.append(xString);
	newWord.append(")");
	newWord.append("(");
	newWord.append(yString);
	newWord.append(") ");
	newWord.append(entry);
	avl.insert(newWord);
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool wordPuzzle::readLetters(string input)
{
	string entry;
	ifstream infile;

	infile.open(input.c_str());
	if (!infile.is_open()) return false; //check file was found and it's open
	getline(infile, title);

	infile >> size;

	pointer = new char*[size]; // dynamic array (size) of pointers to int
	// give each pointer size chars of array area
	for (int i = 0; i < size; ++i) pointer[i] = new char[size];

	for (int y = 0; y < size; ++y)
		for (int x = 0; x < size; ++x)
			infile >> pointer[x][y]; // proper construction of file assumed.

	matrix = new bool*[size]; // dynamic array (size) of pointers to int
	for (int i = 0; i < size; ++i) matrix[i] = new bool[size];

	for (int y = 0; y < size; ++y)
		for (int x = 0; x < size; ++x) matrix[x][y] = false; //dynamic 2d array
	infile.close();
	return true;
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool wordPuzzle::readDictionary(string input)
{
	string entry;
	ifstream infile;
	infile.open(input.c_str());
	if (!infile.is_open()) return false; //check file was found and it's open
	while (infile) {
		infile >> entry;
		trie.insert(entry);
	}
	infile.close();
	return true;
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

void wordPuzzle::showTitle(void)
{
	cout << title << endl;
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

int wordPuzzle::showWordCount(void)
{
	return avl.countNodes();
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

void wordPuzzle::showWords(void)
{
	avl.printTree(INORDER);
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

void wordPuzzle::printLetters(void)
{
	cout << " ";
	for (int i = 0; i < size * 4 - 1; ++i) {
		cout << "_";
	}

	for (int y = 0; y < size; ++y) {
		cout << endl << "|";
		for (int x = 0; x < size; ++x) {
			cout << pointer[x][y] << " | ";
		}
	}
	cout << endl << " ";
	for (int i = 0; i < size * 4 - 1; ++i) {
		printf("-");
	}
	cout << endl;
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

void wordPuzzle::findWords(string entry, int x, int y)
{
	if (x < 0 || y < 0) {
		return;
	}//outside matrix
	else if (x >= size || y >= size) {
		return;
	}//outside matrix
	else if (pointer[x][y] == 0) {
		return;
	} //been there...

	entry += (pointer[x][y]); //add to string

	if (!trie.isPrefix(entry)) {
		return;
	}// no word possiblity then go back
	else {
		pointer[x][y] = 0;
	} // there is a word possiblity then blank the
	// position.

	if (trie.search(entry)) {
		wordsFound(x, y, entry);
	} //if a word--add it

	findWords(entry, x - 1, y - 1);
	findWords(entry, x, y - 1);
	findWords(entry, x + 1, y - 1);
	findWords(entry, x - 1, y); //move through all possiblities from
	findWords(entry, x + 1, y); //current position
	findWords(entry, x - 1, y + 1);
	findWords(entry, x, y + 1);
	findWords(entry, x + 1, y + 1);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void wordPuzzle::findWords(void)
{
	string entry = ""; //string to build grid character discoveries
	for (int y = 0; y < size; ++y) // traverse all grid positions
	{
		for (int x = 0; x < size; ++x) {
			findWords(entry, x, y);
			readLetters(puzzle); //restore blanked letters for next grid
		} //position.
	}
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
#endif
