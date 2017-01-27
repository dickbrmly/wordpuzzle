/*Richard Bromley 5001075854
        (AVL TREE) 


Created by Richard Bromley on 10/2/14. */

#ifndef bromley_puzzle
#define bromley_puzzle

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "trietree.h"
#include "avlTree.h"

using namespace std;						
//-----------------------------------------------------------------------------

    //global constants

class wordPuzzle: public trieTree
{
  private:
  
	string title,characters;
	int order, size;
	bool **matrix;
	char **pointer; // game grid letters
	
  
  // loads AVL Tree with all the words found...
  void wordsFound(int x, int y, string entry);
  
  // finds all words in the letter grid
  void findWords(string, int, int);

public:
  
    string puzzle;
    avlTree<string> avl;
    trieTree trie;

  // constructor  initalize all variables to 'empty' state...
  wordPuzzle();
  
  // deconstructor delete all created variables
  ~wordPuzzle();
  
  void destroyTree(void);
  // read letters reads the entry letter grid file
  // and stores it into a two dimensional array
  bool readLetters(string input);  //also reads game title
  
  // reads dictionary into a triTree returning true if successful
  bool readDictionary(string input);
  
  // displays puzzle title on the screen...
  void showTitle(void);
  
  // display the number of found words with-in the AVL Tree...
 int showWordCount(void);
  
  // shows the words loaded into the AVL Tree...
  void showWords(void);
  
  // displays game title and a formated game grid
  void printLetters(void);
  
  // looks through the trieTree dictionary for a passed word...
  void findWords(void);
  
  };
#endif
