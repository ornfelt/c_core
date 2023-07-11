#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

/**
	Postorder traversal:
    Traverse the left subtree, i.e., call Postorder(left->subtree)
    Traverse the right subtree, i.e., call Postorder(right->subtree)
    Visit the root

	Uses of Postorder:
	Postorder traversal is used to delete the tree. Please see the question for the
	deletion of a tree for details. See: binary_tree_post_delete.cpp
	Postorder traversal is also useful to get the postfix expression of an expression
	tree.
	Example: Postorder traversal for the above-given figure is 4 5 2 3 1

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

/* Given a binary tree, print its nodes according to the
"bottom-up" postorder traversal. */
void printPostorder(struct Node* node)
{
	if (node == NULL)
		return;

	// first recur on left subtree
	printPostorder(node->left);

	// then recur on right subtree
	printPostorder(node->right);

	// now deal with the node
	cout << node->data << " ";
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
	cout << "\nPostorder traversal of binary tree is \n";
	printPostorder(root);

	return 0;
}
