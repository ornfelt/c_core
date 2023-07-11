#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/threaded-binary-tree/

/**
	Inorder traversal of a Binary tree can either be done using recursion or with the use
	of a auxiliary stack. The idea of threaded binary trees is to make inorder traversal
	faster and do it without stack and without recursion. A binary tree is made threaded
	by making all right child pointers that would normally be NULL point to the inorder
	successor of the node (if it exists).

	A threaded binary tree is a type of binary tree data structure where the empty left
	and right child pointers in a binary tree are replaced with threads that link nodes
	directly to their in-order predecessor or successor, thereby providing a way to
	traverse the tree without using recursion or a stack.

	Threaded binary trees can be useful when space is a concern, as they can eliminate the
	need for a stack during traversal. However, they can be more complex to implement than
	standard binary trees.

	There are two types of threaded binary trees. 
	Single Threaded: Where a NULL right pointers is made to point to the inorder successor (if successor exists)
	Double Threaded: Where both left and right NULL pointers are made to point to inorder
	predecessor and inorder successor respectively. The predecessor threads are useful for
	reverse inorder traversal and postorder traversal.
	The threads are also useful for fast accessing ancestors of a node.
	Following diagram shows an example Single Threaded Binary Tree. The dotted lines
	represent threads. 

	See link for applications, advantages and disadvantages for threaded binary tree...
*/


// Use any below method to represent a Threaded Node
// Method 1: Using "struct" to make
// user-define data type
// struct node {
// 	int data;
// 	struct node* left;
// 	struct node* right;
// 	bool rightThread;
// };

// Method 2: Using "class" to make
// user-define data type
class Node {
public:
	int data;
	Node* left;
	Node* right;
	bool rightThread;
	// Val is the key or the value that has to be added to
	// the data part
	Node(int val){
		data = val;
		// Left and right child for node will be initialized
		// to null
		left = NULL;
		right = NULL;
		// rightThread will be initialized to false
		rightThread = false;
	}
};

// Utility function to find leftmost node in a tree rooted with n
Node* leftMost(Node* n){
	if (n == NULL)
		return NULL;

	while (n->left != NULL)
		n = n->left;

	return n;
}

// CPP code to do inorder traversal in a threaded binary tree
void inOrder(Node* root){
	Node* cur = leftMost(root);
	while (cur != NULL) {
		cout<<cur->data<<" ";

		// If this node is a thread node, then go to
		// inorder successor
		if (cur->rightThread)
			cur = cur->right;
		else // Else go to the leftmost child in right
			// subtree
			cur = leftMost(cur->right);
	}
}

int main() {
	cout << "hello world" << endl;
	// TODO: implement the tree above...
	return 0;
}
