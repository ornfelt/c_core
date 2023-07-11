#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/convert-a-binary-tree-to-a-circular-doubly-link-list/
// Also: https://www.geeksforgeeks.org/the-great-tree-list-recursion-problem/

/**
	Given a Binary Tree, convert it to a Circular Doubly Linked List (In-Place).  

	The left and right pointers in nodes are to be used as previous and next pointers
	respectively in the converted Circular Linked List.
	The order of nodes in the List must be the same as in Inorder for the given Binary
	Tree.
    The first node of Inorder traversal must be the head node of the Circular List.

	The idea is to make a general-purpose function that concatenates two given circular
	doubly lists

	Follow these steps below to solve the problem:

	- Recursively convert the left subtree to a circular DLL. Let the converted list be
	leftList.
	- Recursively convert the right subtree to a circular DLL. Let the converted list be
	rightList. 
	- Make a circular linked list of roots of the tree, and make the left and right root
	points to themselves. 
	- Concatenate leftList with the list of the single root node. 
    - Concatenate the list produced in the step above with rightList.

	Note: The above approach traverses the tree in a Postorder fashion. We can traverse in
	an inorder fashion also. We can first concatenate left subtree and root, then recur
	for the right subtree and concatenate the result with left-root concatenation.

	How do Concatenate two circular DLLs? 

	- Get the last node of the left list. Retrieving the last node is an O(1) operation
	since the prev pointer of the head points to the last node of the list.
    - Connect it with the first node of the right list
    - Get the last node of the second list
    - Connect it with the head of the list.

	Time Complexity: O(N), As every node is visited at most once.
	Auxiliary space: O(log N), The extra space is used in the recursion call stack which
	can grow up to a maximum size of logN as it is a binary tree.
*/

// To represents a node of a Binary Tree
struct Node {
	struct Node *left, *right;
	int data;
};

// A function that appends rightList at the end
// of leftList.
Node* concatenate(Node* leftList, Node* rightList)
{
	// If either of the list is empty
	// then return the other list
	if (leftList == NULL)
		return rightList;
	if (rightList == NULL)
		return leftList;

	// Store the last Node of left List
	Node* leftLast = leftList->left;

	// Store the last Node of right List
	Node* rightLast = rightList->left;

	// Connect the last node of Left List
	// with the first Node of the right List
	leftLast->right = rightList;
	rightList->left = leftLast;

	// Left of first node points to
	// the last node in the list
	leftList->left = rightLast;

	// Right of last node refers to the first
	// node of the List
	rightLast->right = leftList;

	return leftList;
}

// Function converts a tree to a circular Linked List
// and then returns the head of the Linked List
Node* bTreeToCList(Node* root)
{
	if (root == NULL)
		return NULL;

	// Recursively convert left and right subtrees
	Node* left = bTreeToCList(root->left);
	Node* right = bTreeToCList(root->right);

	// Make a circular linked list of single node
	// (or root). To do so, make the right and
	// left pointers of this node point to itself
	root->left = root->right = root;

	// Step 1 (concatenate the left list with the list
	//		 with single node, i.e., current node)
	// Step 2 (concatenate the returned list with the
	//		 right List)
	return concatenate(concatenate(left, root), right);
}

// Display Circular Link List
void displayCList(Node* head)
{
	cout << "Circular Linked List is :\n";
	Node* itr = head;
	do {
		cout << itr->data << " ";
		itr = itr->right;
	} while (head != itr);
	cout << "\n";
}

// Create a new Node and return its address
Node* newNode(int data)
{
	Node* temp = new Node();
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

// Driver Program to test above function
int main()
{
	Node* root = newNode(10);
	root->left = newNode(12);
	root->right = newNode(15);
	root->left->left = newNode(25);
	root->left->right = newNode(30);
	root->right->left = newNode(36);

	Node* head = bTreeToCList(root);
	displayCList(head);

	return 0;
}
