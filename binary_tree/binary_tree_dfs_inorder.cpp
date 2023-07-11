#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

/**
	Inorder Traversal:
    Traverse the left subtree, i.e., call Inorder(left->subtree)
    Visit the root.
    Traverse the right subtree, i.e., call Inorder(right->subtree)

	Uses of Inorder Traversal:

	In the case of binary search trees (BST), Inorder traversal gives nodes in
	non-decreasing order. To get nodes of BST in non-increasing order, a variation of
	Inorder traversal where Inorder traversal is reversed can be used. 
	Example: In order traversal for the above-given figure is 4 2 5 1 3.

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

/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct Node* node)
{
	if (node == NULL)
		return;

	/* first recur on left child */
	printInorder(node->left);

	/* then print the data of node */
	cout << node->data << " ";

	/* now recur on right child */
	printInorder(node->right);
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
	cout << "\nInorder traversal of binary tree is \n";
	printInorder(root);

	return 0;
}
