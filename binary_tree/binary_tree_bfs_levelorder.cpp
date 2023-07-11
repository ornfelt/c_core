#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/level-order-tree-traversal/

/**
	Given the root of the Binary Tree. The task is to print the Level order traversal of a
	tree is breadth first traversal for the tree. 

	Level Order Binary Tree Traversal using Recursion:

	Print the level order traversal of the tree using recursive function to traverse all
	nodes of a level. Find height of tree and run depth first search and maintain current
	height, print nodes for every height from root and for 1 to height and match if the
	current height is equal to height of the iteration then print node’s data.

	Steps:
    Run a for loop for counter i, i.e. current height from 1 to h (height of the tree).
    Use DFS to traverse the tree and maintain height for the current node.
        If the Node is NULL then return;
        If level is 1 print(tree->data);
        Else if the level is greater than 1, then
            Recursively call to for tree->left, level-1.
            Recursively call to for tree->right, level-1.

	Time Complexity: O(N2), where N is the number of nodes in the skewed tree. So time
	complexity of printLevelOrder() is O(n) + O(n-1) + O(n-2) + .. + O(1) which is O(N2). 
	Auxiliary Space:  O(N) in the worst case. For a skewed tree, printGivenLevel() uses
	O(n) space for the call stack. For a Balanced tree, the call stack uses O(log n)
	space, (i.e., the height of the balanced tree). 
*/

/* A binary tree node has data,
pointer to left child
and a pointer to right child */
class node {
public:
	int data;
	node *left, *right;
};

/* Function prototypes */
void printCurrentLevel(node* root, int level);
int height(node* node);
node* newNode(int data);

/* Function to print level
order traversal a tree*/
void printLevelOrder(node* root)
{
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
		printCurrentLevel(root, i);
}

/* Print nodes at a current level */
void printCurrentLevel(node* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		cout << root->data << " ";
	else if (level > 1) {
		printCurrentLevel(root->left, level - 1);
		printCurrentLevel(root->right, level - 1);
	}
}

/* Compute the "height" of a tree -- the number of
	nodes along the longest path from the root node
	down to the farthest leaf node.*/
int height(node* node)
{
	if (node == NULL)
		return 0;
	else {
		/* compute the height of each subtree */
		int lheight = height(node->left);
		int rheight = height(node->right);

		/* use the larger one */
		if (lheight > rheight) {
			return (lheight + 1);
		}
		else {
			return (rheight + 1);
		}
	}
}

/* Helper function that allocates
a new node with the given data and
NULL left and right pointers. */
node* newNode(int data)
{
	node* Node = new node();
	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;

	return (Node);
}

/* Driver code*/
int main()
{
	node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);

	cout << "Level Order traversal of binary tree is \n";
	printLevelOrder(root);

	return 0;
}
