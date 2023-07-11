#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

/**
	Preorder Traversal:
	Visit the root.
	Traverse the left subtree, i.e., call Preorder(left->subtree)
	Traverse the right subtree, i.e., call Preorder(right->subtree) 

	Uses of Preorder:
	Preorder traversal is used to create a copy of the tree. Preorder traversal is also
	used to get prefix expressions on an expression tree. Example: Preorder traversal for
	the above-given figure is 1 2 4 5 3.

	Time Complexity: O(N)
	Auxiliary Space: If we don’t consider the size of the stack for function calls then
	O(1) otherwise O(h) where h is the height of the tree. 
*/

/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct Node {
	int data;
	struct Node *left, *right;
};

// Utility function to create a new tree node
Node* newNode(int data)
{
	Node* temp = new Node;
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct Node* node)
{
	if (node == NULL)
		return;

	/* first print data of node */
	cout << node->data << " ";

	/* then recur on left subtree */
	printPreorder(node->left);

	/* now recur on right subtree */
	printPreorder(node->right);
}

/* Driver code*/
int main()
{
	struct Node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);

	// Function call
	cout << "\nPreorder traversal of binary tree is \n";
	printPreorder(root);

	return 0;
}
