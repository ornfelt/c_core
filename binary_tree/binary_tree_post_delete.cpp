#include<bits/stdc++.h>
#include<iostream>
using namespace std;

// https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/

/**
	To delete a tree, we must traverse all the nodes of the tree and delete them one by
	one. So, which traversal we should use – inorder traversal, preorder traversal, or the
	postorder traversal? The answer is simple. We should use the postorder traversal
	because before deleting the parent node, we should delete its child nodes first.
	We can delete the tree with other traversals also with extra space complexity but why
	should we go for the other traversals if we have the postorder one available which
	does the work without storing anything in the same time complexity.
	For the following tree, nodes are deleted in the order – 4, 5, 2, 3, 1.

	Note : In Java automatic garbage collection happens, so we can simply make root null
	to delete the tree “root = null”;

	Time Complexity: O(n) 
	Space Complexity: If we don’t consider size of stack for function calls then O(1)
	otherwise O(h)
*/

/* A binary tree node has data, pointer to left child
and a pointer to right child */
class node
{
	public:
	int data;
	node* left;
	node* right;
};

/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
node* newNode(int data)
{
	node* Node = new node();

	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;
	return(Node);
}

/* This function is same as deleteTree()
in the previous program */
void _deleteTree(node* node)
{
	if (node == NULL) return;

	/* first delete both subtrees */
	_deleteTree(node->left);
	_deleteTree(node->right);

	/* then delete the node */
	cout << "Deleting node: " << node->data << endl;
	delete node;
}

/* Deletes a tree and sets the root as NULL */
void deleteTree(node** node_ref)
{
	_deleteTree(*node_ref);
	*node_ref = NULL;
}

/* Driver code*/
int main()
{
	node *root = newNode(1);
	root->left	 = newNode(2);
	root->right	 = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);

	// Note that we pass the address of root here
	deleteTree(&root);
	cout << "Tree deleted ";
	return 0;
}
