/*     	Richard Bromley 5001075854
                (AVL TREE)
*/

#include <iostream>
using namespace std;

enum treeTraversalOptions { INORDER, PREORDER, POSTORDER, LEVELORDER, NONE};

# define TRUE 1
# define FALSE 0
# define BAL 2   //allowable balance error

using namespace std;
//*****************************************************************************
template <class myType>
struct nodeType
{ 		// entry value (template defined)
		myType keyValue;
		int nodeHeight;

		// branch left and right locations
		nodeType <myType> *left;
		nodeType <myType> *right; 
};							
//-----------------------------------------------------------------------------
template <class myType>
class avlTree
{
private:
		bool fact;
		unsigned int count; //number of literal nodes
		unsigned int counter;
		unsigned int stories;
		
		nodeType<myType> *root;
		nodeType<myType> *current;
		nodeType<myType> *temp;
		nodeType<myType> *preTarget;

//*****************************************************************************
// recurse through all nodes and reverse delete by fall-through to delete
		void destroyTree(nodeType<myType>* &target)
		{ //find leafs and delete them all...
			if (target != NULL)
			{
				destroyTree(target->left);
				destroyTree(target->right);
				if (target != NULL) delete target; //leaf found
			}
			stories = 0;
			count = 0;
		}
//*****************************************************************************
// return the global count value
		int _countNodes(void)
		{
		  return count;
		}
//*****************************************************************************
		bool search(myType token, nodeType <myType>* &target)
		{ //search all branches..  Toggle fact if item found.

		  if(target == NULL) return false;
		  if(target->keyValue == token)
		  {
		  	fact = true;
		  	temp = target;
		  	return true;
		  }
		  
		  if (target->right != NULL)
		  {
		  	if (target->right->keyValue == token) 
		  	{
		  		fact = true;
		  		temp = target;
		  		return true;
		  	}
		  }
		  
		  if (target->left != NULL)
		  {		  
		  	if (target->left->keyValue == token) 
		  	{
		  		fact = true;
		  		temp = target;
		  		return true;
		  	}
		  }
		  
		  if(target->keyValue != token && target->left != NULL)
		  search(token, target->left);
		  
		  if (target->keyValue != token && target->right != NULL) 
		  search(token, target->right);
		}
//*****************************************************************************
		void printLevel(myType floor, nodeType <myType>* &target)
		{// print all items on floor value
		  if(target == NULL) return;
		  
		  if(target->nodeHeight == floor)
		  cout << target->keyValue << " ";
		 
		  if(target->nodeHeight < floor) 
		  printLevel(floor, target->left);

		  if(target->nodeHeight < floor) 
		  printLevel(floor, target->right); 
		}
//*****************************************************************************		
	void printTree(nodeType <myType>* &target, treeTraversalOptions x)
	{
	  if(target != NULL)
	  {
	  	switch(x)
		{
			case INORDER:
			case NONE:
			{
			  printTree(target->left, INORDER);
			  cout << target->keyValue << " ";
			  printTree(target->right, INORDER);
			  break;
			}
			case PREORDER:
			{
			  cout << target->keyValue << " ";
			  printTree(target->left, PREORDER);
			  printTree(target->right, PREORDER);
			  break;				
			}
			case POSTORDER:
			{
			  printTree(target->left, POSTORDER);
			  printTree(target->right, POSTORDER);
			  cout << target->keyValue << " ";
			  break;
			}
			case LEVELORDER:
			{
				for(int i = 1; i < stories + 1; ++i)
				{
					printLevel(i, target);
					cout << endl;
				}
			}
		}	
	  }
	}
//*****************************************************************************
		void insert(myType item,nodeType <myType>* &target)
		{
		  if(target == NULL) 
		  {	
		  	target = new nodeType<myType>;
		  	target->right = NULL;
		  	target->left = NULL;
		  	target->keyValue = item;
		  	++stories;
		  	++count;
		  	target->nodeHeight = stories;
		  }
		  else if(item < target->keyValue)
		  {
		  	stories = target->nodeHeight;
		  	insert(item, target->left);
		  }
		  else if (item > target->keyValue)
		  {
		  	stories = target->nodeHeight;
		  	insert(item, target->right);
		  }
		  balance(target);
		}
//******************************************************************************
		void balance(nodeType <myType>* &target)
		{
			int left,right;
			if(target == NULL) return;
			
			counter = 0;
			left = heightLeft(target->left);
			counter = 0;
			right = heightRight(target->right);
			
			if( left - right  > BAL)
			rightRotate(target);
			
			if(right - left > BAL)
			leftRotate(target);
		}
//*****************************************************************************
	int heightLeft(nodeType <myType> * &target)
	{
		if(target == NULL) return counter;
		++counter;
		heightLeft(target->left);
	}
	
//*****************************************************************************
//*****************************************************************************
	int heightRight(nodeType <myType> * &target)
	{
		if(target == NULL) return counter;
		++counter;
		heightRight(target->right);
	}

//*****************************************************************************
//*****************************************************************************
	int height(nodeType <myType> * &target)
	{
		stories = 0;
		return findHeight(target);
	}

//*****************************************************************************
	int findHeight(nodeType <myType> * &target)
	{
		if(target == NULL) return stories;
		
		if(stories < target->nodeHeight) stories = target->nodeHeight;
		findHeight(target->left);
		findHeight(target->right);

		return stories;
	}
//*****************************************************************************//******************************************************************************
		void rightRotate(nodeType <myType>* &target)
		{
			current = target->left;
			

			if(current->right == NULL) 
			{
				Switch(current, target);
				current->right = target->right;
				target->right = current;
				target->left = current->left;
				current->left = NULL;
				decLeft(target);
			}
			else if(target->right == NULL)
			{
				Switch(current, target);
				target->left = current->left;
				target->right = current->right;
				target->right->right = current;
				current->right = NULL;
				current->left = NULL;
				decLeft(target->left);
			}
			else
			{
				Switch(current, target);
				Switch(current->right, target->right);
				target->left = current->left;
				target->right->right = current;
				current->left = NULL;
				decLeft(target->left);
			} 
		}
//*******************************************************************************
		void doubleRightRotate(nodeType <myType>* &target)
		{
			leftRotate(target->right);
			rightRotate(target);
		}
//*******************************************************************************
//*******************************************************************************
		void doubleLeftRotate(nodeType <myType>* &target)
		{
			rightRotate(target->left);
			leftRotate(target);
		}
//*******************************************************************************
		void leftRotate(nodeType <myType>* &target)
		{	
			current = target->right;
			

			if(current->left == NULL) 
			{
				Switch(current, target);
				current->left = target->left;
				target->left = current;
				target->right = current->right;
				current->right = NULL;
				decRight(target);
			}
			else if(target->left == NULL)
			{
				Switch(current, target);
				target->right = current->right;
				target->left = current->left;
				target->left->left = current;
				current->left = NULL;
				current->right = NULL;
				decRight(target->right);
			}
			else
			{
				Switch(current, target);
				Switch(current->left, target->left);
				target->right = current->right;
				target->left->left = current;
				current->right = NULL;
				decRight(target->right);
			} 
		}
//******************************************************************************
		void Switch(nodeType <myType>* &term1,nodeType <myType>* &term2)
		{
			myType holder;
			holder = term1->keyValue;
			term1->keyValue = term2->keyValue;
			term2->keyValue = holder;
		}
//******************************************************************************
//******************************************************************************
		void decLeft(nodeType <myType>* &target)
		{
			if(target == NULL) return;
			decLeft(target->left);
			--target->nodeHeight;
		}
//******************************************************************************
//******************************************************************************
		void decRight(nodeType <myType>* &target)
		{
			if(target == NULL) return;
			decRight(target->right);
			--target->nodeHeight;
		}
//******************************************************************************
		signed int getBalance(nodeType <myType>* &target,int balance)
		{
		 if(target->left != NULL) getBalance(target->left, ++balance);
		 if(target->right != NULL) getBalance(target->right, --balance);
		 return balance;
		}
//******************************************************************************
	void deleteNode(myType value, nodeType <myType>* target)
	{
	  nodeType<myType> *tempLeft;
	  nodeType<myType> *tempRight;
		
	  myType replacements[100000];
	  
	  int index = 0;
	  int index2 = 0;
	  
	  search(value, target);

	  if(fact = false) return;
	  
	  if(temp != NULL)
	   if(temp->left != NULL)
	  	if(temp->left->keyValue == value) 
	  	{
	  		tempLeft = temp->left;
	  		temp->left = NULL;
	  	}

	  if(temp != NULL)
	   if(temp->right != NULL)
	  	if(temp->right->keyValue == value) 
	  	{
	  		tempLeft = temp->right;
	  		temp->right = NULL;
	  	}
	  
	  tempRight = tempLeft;
	  
	  while (tempLeft != NULL && tempRight != NULL)
	  {
	  	if (tempLeft->left != NULL) 
	  	{
	  		replacements[index] = tempLeft->left->keyValue;
	  		++index;
	  	}
	  	if (tempRight->right != NULL)
	  	{
	  		replacements[index] = tempRight->right->keyValue;
	  		++index;
	  	}
	  	tempLeft = tempLeft->left;
	  	tempRight = tempRight->right;
	  }
	  
 	  destroyTree(temp);
 	  
 	  // insert deleted items.
 	  for(int x = index; x > 0; --x) insert(replacements[x],root);	
 	 
 	  --count;
	}
//*****************************************************************************
		nodeType <myType> * maxValueNode(nodeType <myType>* target)
		{
			if(target == NULL) return NULL;
			if(target->right == NULL) return target;
			preTarget = target;
			return maxValueNode(target->right);
		}
//*****************************************************************************
		nodeType <myType> * minValueNode(nodeType <myType>* target)
		{
			if(target == NULL) return NULL;
			if(target->left == NULL) return target;
			preTarget = target;
			return minValueNode(target->left);
		}
//*****************************************************************************
	myType * clone(nodeType <myType> * &target)
	{
		if(target == NULL) return NULL;
		else return new nodeType<myType>;
	}
//*****************************************************************************	
public:
		avlTree()
		{
			temp = NULL;
			current = NULL;
			root = NULL;
			stories = 0;
			count = 0;
		}
//*****************************************************************************		
		avlTree<myType>(const avlTree<myType>& rhs)
		//copy constructor
		{
			root = clone(rhs.root);
			root->nodeHeight = 0;
			root->keyValue = 0;
			stories = 0;
			root->left = NULL;
			root->right = NULL;
			current->left = NULL;
			current->right = NULL;
			current = NULL;
			temp->left = NULL;
			temp->right = NULL;
			temp = NULL;
			count = 0;
		}
//*****************************************************************************		
		~avlTree()
		{
		  destroyTree(root);
		}
//*****************************************************************************
		void destroyTree(void)
		{
			destroyTree(root);
		}
//*****************************************************************************
		int countNodes(void)
		{
			return _countNodes();
		}
//*****************************************************************************
		int height(void)
		{ 
		    return height(root);
		}
//*****************************************************************************
		bool search(myType item) //there or not
		{
			fact = false;
			search(item, root);
			return fact;
		}
//*****************************************************************************
		void printTree(treeTraversalOptions how)
		{
			printTree(root,how);
			return;
		}
//*****************************************************************************
		void insert(myType item) 
		{
			insert(item, root);
			return;
		}
//*****************************************************************************
		void deleteNode(myType item)
		{
			deleteNode(item, root);
			return;
		}
//*****************************************************************************
};
