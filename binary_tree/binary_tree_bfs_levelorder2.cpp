#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/level-order-tree-traversal/

/**
	Given the root of the Binary Tree. The task is to print the Level order traversal of a
	tree is breadth first traversal for the tree. 

	Level Order Binary Tree Traversal using Queue:

	For each node, first, the node is visited and then it’s child nodes are put in a FIFO
	queue. Then again the first node is popped out and then it’s child nodes are put in a
	FIFO queue and repeat until queue becomes empty.

	Steps:
    Create an empty queue q and push root in q.
    Run While loop until q is not empty. 
        Initialize temp_node = q.front() and print temp_node->data.
        Push temp_node’s children i.e. temp_node -> left then temp_node -> right to q
        Pop front node from q.

	Time Complexity: O(N) where n is the number of nodes in the binary tree.
	Auxiliary Space: O(N) where n is the number of nodes in the binary tree.
*/

// A Binary Tree Node
struct Node {
	int data;
	struct Node *left, *right;
};

// Iterative method to find height of Binary Tree
void printLevelOrder(Node* root)
{
	// Base Case
	if (root == NULL)
		return;

	// Create an empty queue for level order traversal
	queue<Node*> q;

	// Enqueue Root and initialize height
	q.push(root);

	while (q.empty() == false) {
		// Print front of queue and remove it from queue
		Node* node = q.front();
		cout << node->data << " ";
		q.pop();

		/* Enqueue left child */
		if (node->left != NULL)
			q.push(node->left);

		/*Enqueue right child */
		if (node->right != NULL)
			q.push(node->right);
	}
}

// Utility function to create a new tree node
Node* newNode(int data)
{
	Node* temp = new Node;
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

// Driver program to test above functions
int main()
{
	// Let us create binary tree shown in above diagram
	Node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);

	cout << "Level Order traversal of binary tree is \n";
	printLevelOrder(root);
	return 0;
}
