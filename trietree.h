/*  Richard Bromley 5001075854
    TRIETREE
*/



#ifndef bromley_TRIETREE
#define bromley_TRIETREE

#include <iostream>
#include <string>
#include <cctype>


#define ALPHABET 26
using namespace std;						
//-----------------------------------------------------------------------------
struct trieNodeType
{
	char keyValue;//the character the node represents
	int nodeCount; // character count from the index to this node
	bool endWordMark;// does the trail that got here equal a word?
	trieNodeType *children[26];// offsets to letters from here
};

class trieTree
{
private:
    trieNodeType *index; //index marker to dictionary.
 	// internal call to delete from entry--a tree		
    void destroyTree(trieNodeType* &);
    int countNodes(trieNodeType*);//count node possibilities from this node
    int height(trieNodeType*); //find from from given node.
    void printTree(trieNodeType*); //print all nodes from this node
    void newChild(int, char, trieNodeType* &); //pass address of 
                                               //new initialized child

public:
    trieTree();	// constructor
    ~trieTree();  	//destructor
    int countNodes(void); //count all the nodes from the index
    void destroyTree(void); // external call to delete tree
    int height(void); //return the total height from the index
    void printTree(void);//print complete node list
    void insert(string);//insert word into trieTree path
    bool readDictionary(string); //reads given dictionary title
    bool search(string); //look for given word in trieTree?
    bool isPrefix(string); //Is the string a legal prefix?
};
#endif
