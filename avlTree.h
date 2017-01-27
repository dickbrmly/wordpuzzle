/*  Richard Bromley 5001075854 (AVL TREE)
*/

#include <iostream>
#include <algorithm> 

using namespace std;

enum treeTraversalOptions { INORDER, PREORDER, POSTORDER, LEVELORDER, NONE};

# define TRUE   1
# define FALSE  0
# define BAL    1		   //allowable difference in binary branches
# define starting_level 0   //starting_level = -1 level to start

using namespace std;
//*****************************************************************************
template <class myType>
struct nodeType
{
  myType keyValue;
  int nodeHeight;
  nodeType <myType> *left;
  nodeType <myType> *right;
};							
//-----------------------------------------------------------------------------
template <class myType>
class avlTree
{
private:
  nodeType<myType> *root;

//*****************************************************************************
// recurse through all nodes and reverse delete by fall-through to delete
void destroyTree(nodeType<myType>* &target)
{
  if(target == NULL) return;
  if (target->left != NULL) destroyTree(target->left);
  if (target->right != NULL) destroyTree(target->right);
  target = NULL;
  delete target;
}
//*****************************************************************************
int countNodes(nodeType <myType> *target)
{
  int amount = 0;
  if(target == NULL) return amount;
  amount++;
  amount += countNodes(target->left);
  amount += countNodes(target->right);
  return amount;
}
//*****************************************************************************
  int height(nodeType <myType> *target)
{
  int level = 0;
  if (target == NULL) return level;
  level = max(height(target->left),height(target->right)) + 1;
  return level;
}
//*****************************************************************************
bool search(myType token, nodeType <myType> *target)
{
  if(target == NULL) return false;
  if (token < target->keyValue) return search(token, target->left);
  else if (token > target->keyValue) return search(token, target->right);
  else return true;
}
//*****************************************************************************
void printTree(nodeType <myType> *target, treeTraversalOptions x)
{
  if(target == NULL) return;
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
	  int level = height(root);
	  for(int i = starting_level; i <= level + 1; ++i)
	  {
	    printLevel(i, target);
	    cout << endl;
	  }
	}
  }
}
//*****************************************************************************
void printLevel(int level, nodeType <myType> *target)
{
  if(target == NULL) return;
  if(target->nodeHeight == level)
  {
    cout << target->keyValue << " ";
    return;
  }
  printLevel(level,target->left);
  printLevel(level,target->right);
}
//*****************************************************************************
  void insert(myType item, nodeType <myType>* &target,int lastLevel)
  {
    if(target == NULL)
    {
	 target = new nodeType<myType>;
	 target->right = NULL;
	 target->left = NULL;
	 target->keyValue = item;
	 target->nodeHeight = ++lastLevel;
    }
    else if (item < target->keyValue)
    insert(item, target->left, target->nodeHeight);
    else if (item > target->keyValue)
    insert(item, target->right, target->nodeHeight);

    balance(target);
  }
//******************************************************************************
void balance(nodeType <myType> *target)
{
  switch(difference(target))
  {
    case -2:
    {
	 switch (difference(target->right))
	 {
	   case -1:
		leftRotate(target);
		break;
	   case 1:
		doubleLeft(target);
		break;
	 }
    }
    case -1:
    case 0:
    case 1:
	 break;
    case 2:
    {
	 switch (difference(target->left))
	 {
	   case -1:
		doubleRight(target);
		break;
	   case 1:
		rightRotate(target);
		break;
	 }
    }
  }
}
//******************************************************************************
int difference(nodeType <myType> *target)
{
  if (target == NULL) return 0;
  else return height(target->left) - height(target->right);
}
//******************************************************************************
void doubleRight(nodeType <myType>* &target)
{
  nodeType<myType> *hinge;
  nodeType<myType> *pivot;
  
  hinge = target->left;
  pivot = hinge->right;
  
  Switch(target,pivot);			 //move 1
  hinge->right = pivot->left;		 //move 2
  pivot->left = pivot->right;		 //move 2
  pivot->right = target->right;	 //move 3
  target->right = pivot;			 //move 4
  reposition(target);
}
//******************************************************************************
void doubleLeft(nodeType <myType>* &target)
{
  nodeType<myType> *hinge;
  nodeType<myType> *pivot;
  
  hinge = target->right;
  pivot = hinge->left;
  
  Switch(target,pivot);			 //move 1
  hinge->left = pivot->right;		 //move 2
  pivot->right = pivot->left;		 //move 2
  pivot->left = target->left;		 //move 3
  target->left = pivot;			 //move 4
  reposition(target);
}
//******************************************************************************
void rightRotate(nodeType <myType>* &target)
{
  nodeType<myType> *hinge;
  nodeType<myType> *pivot;
  
  pivot = target->left;
  hinge = pivot->left;
  
  Switch(target,pivot);			 //move 1
  target->left = hinge;			 //move 2
  pivot->left = pivot->right;		 //move 2
  pivot->right = target->right;	 //move 3
  target->right = pivot;			 //move 4
  reposition(target);
}
//******************************************************************************
void leftRotate(nodeType <myType>* &target)
{
  nodeType<myType> *hinge;
  nodeType<myType> *pivot;
  
  pivot = target->right;
  hinge = pivot->right;
  
  Switch(target,pivot);			 //move 1
  target->right = hinge;			 //move 2
  pivot->right = pivot->left;		 //move 2
  pivot->left = target->left;		 //move 3
  target->left = pivot;			 //move 4
  reposition(target);
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
void reposition(nodeType <myType> *target)
{
  if(target == NULL) return;
  if(target->left != NULL) target->left->nodeHeight = target->nodeHeight + 1;
  if(target->right != NULL) target->right->nodeHeight = target->nodeHeight + 1;
  reposition(target->left);
  reposition(target->right);
}
//******************************************************************************
void deleteNode(myType value,nodeType<myType> *parent,nodeType<myType> *target)
{
  nodeType<myType> *pivot;
  nodeType<myType> *hinge;
  
  if(target == NULL) return;
  if (value < target->keyValue) deleteNode(value, target, target->left);
  else if (value > target->keyValue) deleteNode(value, target, target->right);
  else
  {
    if(target->left == NULL && target->right == NULL)
    {
	 if(parent->left == target) parent->left = NULL;
	 else parent->right = NULL;
	 delete target;
    }
    else if(target->left == NULL)
    {
	 if(parent->left == target) parent->left = target->right;
	 else parent->right = target->right;
	 delete target;
    }
    else if(target->right == NULL)
    {
	 if(parent->left == target) parent->left = target->left;
	 else parent->right = target->left;
	 delete target;
    }
    else
    {
	 pivot = target->left;
	 hinge = target;
	 while(pivot->right != NULL)
	 {
	   hinge = pivot;
	   pivot = pivot->right;
	 }
	 Switch(pivot,target);
	 if(hinge != target) hinge->right = pivot->left;
	 else hinge->left = pivot->left;
	 delete pivot;
    }
    reposition(parent);
  }
  balance(target);
}
//******************************************************************************
public:
//******************************************************************************
  avlTree() { root = NULL; }
//*****************************************************************************
  ~avlTree(){ destroyTree(root);}
//*****************************************************************************
  void destroyTree(void){ destroyTree(root); }
//*****************************************************************************
  int countNodes(void){ return countNodes(root); }
//*****************************************************************************
  int height(void) { return height(root); }
//*****************************************************************************
  bool search(myType item) { return search(item, root); }
//*****************************************************************************
  void printTree(treeTraversalOptions how) { printTree(root,how); }
//*****************************************************************************
  void insert(myType item) { insert(item,root,starting_level); }
//*****************************************************************************
//  enter item to delete, parent node (can be same), beginning search node
  void deleteNode(myType item) { deleteNode(item, root, root); }
//*****************************************************************************
};
