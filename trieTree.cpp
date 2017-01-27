// Richard Bromley 5001075854
// 
//
//  trieTree.cpp
//  
//
//  Created by Richard Bromley on 10/2/14.
//
//
#ifndef bromley_TRIETREEC
#define bromley_TRIETREEC

#include <iostream>
#include <fstream>
#include <string>
#include "trietree.h"

//*****************************************************************************
trieTree::trieTree()
{  	//index is the inital index to all the letters

    index = new trieNodeType;
    index->keyValue = 0; //this is what the node represents.
    index->endWordMark = false;
    //index or index nodeCount is count zero for clear character counts.
    index->nodeCount = 0;
    // NULL values are highly necessary
	for(int x = 0; x < 26; ++x) index->children[x] = NULL;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
trieTree::~trieTree() { destroyTree(index); }
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
void trieTree::printTree(trieNodeType *target) //private print from node
{
  if(target == NULL) { return; }
  for(int x = 0; x < ALPHABET; ++x) printTree(target->children[x]);
  cout << target->keyValue << "  ";
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void trieTree::printTree(void) { printTree(index);}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
int trieTree::height(trieNodeType *target) //private from node call
{
  if (target == NULL) return 0;
  int level = 0;
  for (int x = 0; x < ALPHABET; ++x) 
  {
  	level = height(target->children[x]);
  	if (level < target->nodeCount) level = target->nodeCount;
  }
	return level;	
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int trieTree::height(void) { return height(index); }
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
void trieTree::destroyTree(trieNodeType* &target)
{//private rountine to delete from starting node. index is held for destuctor
    //if (target == NULL) return;
    //for (int x = 0; x < ALPHABET; ++x) destroyTree(target->children[x]);
    //delete target;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void trieTree::destroyTree(void) { destroyTree(index); }
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
int trieTree::countNodes(trieNodeType *target)
{
  int count = 0;
  if (target == NULL) return count;
  for (int x = 0; x < ALPHABET; ++x) count += countNodes(target->children[x]);
  return ++count;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int trieTree::countNodes(void) { return countNodes(index); }
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
void trieTree::insert(string entry)
{
	int offset;
	int x = 0;
	trieNodeType *target;
	target = index;
  
	while(entry[x] != 0)
	{
        offset = tolower(entry[x]) - 'a';
		if(target->children[offset] == NULL)
        {
          newChild(target->nodeCount,entry[x],target->children[offset]);
        }
        target = target->children[offset];
		++x;
	}
	target->endWordMark = true;
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
void trieTree::newChild(int level, char x, trieNodeType* &target)//there or not
{
  target = new trieNodeType;
  target->keyValue = x; //this is what the node represents.
  target->endWordMark = false;
  //index or index nodeCount is nodeCount zero for clear character counts.
  target->nodeCount = level + 1;
  // NULL values are highly necessary
  for (int x = 0; x < ALPHABET; ++x) { target->children[x] = NULL; }
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
bool trieTree::readDictionary(string title)
{
  ifstream infile(title.c_str());
  string word;

    if(infile.is_open())
	{
	  while (infile)
	  {
	    infile >> word;
	    insert(word);
	  }
	  infile.close();
	  return true;
	}
	else { return false;}
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
bool trieTree::search(string entry)//there or not
{
    trieNodeType *target;
  
    int offset; //character pointer
    int  x = 0;
  
	target = index;
	while(entry[x] >= 'a')
	{
        offset = entry[x] - 'a';
        if(target->children[offset] == NULL) { return false; }
		target = target->children[offset];
		++x; 
	}
    if(target->endWordMark == true) { return true; }
    else { return false; }
}
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
bool trieTree::isPrefix(string entry)
{
    char a;
	unsigned int offset;
	unsigned int  x = 0;
  
	trieNodeType *target;
	
	target = index;
	while(entry[x] != 0)
	{
      a = entry[x];
      offset = a - 'a';
      if(target->children[offset] == NULL) { return false; }
      target = target->children[offset];
      ++x;
	}
	return true;
}
//*****************************************************************************
#endif
