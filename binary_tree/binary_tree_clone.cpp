#include<bits/stdc++.h>
#include<iostream>
#include<unordered_map>

using namespace std;

// https://www.geeksforgeeks.org/clone-binary-tree-random-pointers/

/**
	Clone a Binary Tree with Random Pointers

	Method 1 (Use Hashing): The idea is to store a mapping from given tree nodes to clone
	tree nodes in the hashtable. Following are detailed steps.

	1) Recursively traverse the given Binary and copy key-value, left pointer, and a right
	pointer to clone tree. While copying, store the mapping from the given tree node to
	clone the tree node in a hashtable. In the following pseudo-code, ‘cloneNode’ is the
	currently visited node of the clone tree and ‘treeNode’ is the currently visited node
	of the given tree. 

	2) Recursively traverse both trees and set random pointers using entries from the hash
	table.

	Time complexity: O(n), this is because we need to traverse the entire tree in order to
	copy the left and right pointers, and then we need to traverse the tree again to copy
	the random pointers.
	Auxiliary Space: O(n), this is because we need to store a mapping of the original
	tree’s nodes to their clones.
*/

/* A binary tree node has data, pointer to left child,
	a pointer to right child and a pointer to
	random node*/
struct Node
{
	int key;
	struct Node* left, *right, *random;
};

/* Helper function that allocates a new Node with the
given data and NULL left, right and random pointers. */
Node* newNode(int key)
{
	Node* temp = new Node;
	temp->key = key;
	temp->random = temp->right = temp->left = NULL;
	return (temp);
}

/* Given a binary tree, print its Nodes in inorder*/
void printInorder(Node* node)
{
	if (node == NULL)
		return;

	/* First recur on left subtree */
	printInorder(node->left);

	/* then print data of Node and its random */
	cout << "[" << node->key << " ";
	if (node->random == NULL)
		cout << "NULL], ";
	else
		cout << node->random->key << "], ";

	/* now recur on right subtree */
	printInorder(node->right);
}

/* This function creates clone by copying key
and left and right pointers. This function also
stores mapping from given tree node to clone. */
Node* copyLeftRightNode(Node* treeNode, unordered_map<Node *, Node *> &mymap)
{
	if (treeNode == NULL)
		return NULL;
	Node* cloneNode = newNode(treeNode->key);
	mymap[treeNode] = cloneNode;
	cloneNode->left = copyLeftRightNode(treeNode->left, mymap);
	cloneNode->right = copyLeftRightNode(treeNode->right, mymap);
	return cloneNode;
}

// This function copies random node by using the hashmap built by
// copyLeftRightNode()
void copyRandom(Node* treeNode, unordered_map<Node *, Node *> &mymap)
{
	if (treeNode == NULL)
		return;
	mymap[treeNode]->random = mymap[treeNode->random];
	copyRandom(treeNode->left, mymap);
	copyRandom(treeNode->right, mymap);
}

// This function makes the clone of given tree. It mainly uses
// copyLeftRightNode() and copyRandom()
Node* cloneTree(Node* tree)
{
	if (tree == NULL)
		return NULL;
	unordered_map<Node *, Node *> mymap;
	Node* newTree = copyLeftRightNode(tree, mymap);
	copyRandom(tree, mymap);
	return newTree;
}

/* Driver program to test above functions*/
int main()
{
	//Test No 1
	Node *tree = newNode(1);
	tree->left = newNode(2);
	tree->right = newNode(3);
	tree->left->left = newNode(4);
	tree->left->right = newNode(5);
	tree->random = tree->left->right;
	tree->left->left->random = tree;
	tree->left->right->random = tree->right;

	// Test No 2
	// tree = NULL;

	// Test No 3
	// tree = newNode(1);

	// Test No 4
	/* tree = newNode(1);
		tree->left = newNode(2);
		tree->right = newNode(3);
		tree->random = tree->right;
		tree->left->random = tree;
	*/

	cout << "Inorder traversal of original binary tree is: \n";
	printInorder(tree);

	Node *clone = cloneTree(tree);

	cout << "\n\nInorder traversal of cloned binary tree is: \n";
	printInorder(clone);

	return 0;
}
