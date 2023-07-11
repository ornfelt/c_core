#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/

/**
	A binary search tree (BST) is a node-based binary tree data structure that has the
	following properties. 

    The left subtree of a node contains only nodes with keys less than the node’s key.
    The right subtree of a node contains only nodes with keys greater than the node’s key.
    Both the left and right subtrees must also be binary search trees.
    Each node (item in the tree) has a distinct key.

	The idea is to write a utility helper function isBSTUtil(struct node* node, int min,
	int max) that traverses down the tree keeping track of the narrowing min and max
	allowed values as it goes, looking at each node only once. The initial values for min
	and max should be INT_MIN and INT_MAX — they narrow from there. 

	Steps:
	Call the isBstUtil function for the root node and set the minimum value as INT_MIN and
	the maximum value as INT_MAX

    If the current node is NULL then return true
	If the value of the node is less than the minimum value possible or greater than the
	maximum value possible then return false
	Call the same function for the left and the right subtree and narrow down the minimum
	and maximum values for these calls accordingly

	Time Complexity: O(N), Where N is the number of nodes in the tree
	Auxiliary Space: O(1), if Function Call Stack size is not considered, otherwise O(H)
	where H is the height of the tree
*/

/* A binary tree node has data,
pointer to left child and
a pointer to right child */
class node {
public:
	int data;
	node* left;
	node* right;

	/* Constructor that allocates
	a new node with the given data
	and NULL left and right pointers. */
	node(int data)
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

int isBSTUtil(node* node, int min, int max);

/* Returns true if the given
tree is a binary search tree
(efficient version). */
int isBST(node* node)
{
	return (isBSTUtil(node, INT_MIN, INT_MAX));
}

/* Returns true if the given
tree is a BST and its values
are >= min and <= max. */
int isBSTUtil(node* node, int min, int max)
{
	/* an empty tree is BST */
	if (node == NULL)
		return 1;

	/* false if this node violates
	the min/max constraint */
	if (node->data < min || node->data > max)
		return 0;

	/* otherwise check the subtrees recursively,
	tightening the min or max constraint */
	return isBSTUtil(node->left, min, node->data - 1)
		&& // Allow only distinct values
		isBSTUtil(node->right, node->data + 1,
					max); // Allow only distinct values
}

/* Driver code*/
int main()
{
	node* root = new node(4);
	root->left = new node(2);
	root->right = new node(5);
	root->left->left = new node(1);
	root->left->right = new node(3);

	// Function call
	if (isBST(root))
		cout << "Is BST";
	else
		cout << "Not a BST";

	return 0;
}
