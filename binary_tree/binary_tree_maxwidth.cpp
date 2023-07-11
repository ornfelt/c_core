#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/maximum-width-of-a-binary-tree/

/**
	Given a binary tree, the task is to find the maximum width of the given tree. 

	Input:
				1
			/   \
		2      3
		/   \       \
	4     5       8 
				/     \
			6        7
	Output:  3
	Explanation: For the above tree, 
	width of level 1 is 1, 
	width of level 2 is 2, 
	width of level 3 is 3 
	width of level 4 is 2. 
	So the maximum width of the tree is 3.

	Level Order Traversal using Queue:
	When a queue is used, we can count all the nodes in a level in constant time. This
	reduces the complexity to be a linear one. 

	In this method do the following:

    Store all the child nodes at the current level in the queue. 
		Count the total number of nodes after the level order traversal for a particular
		level is completed. 
		Since the queue now contains all the nodes of the next level, we can easily find
		out the total number of nodes in the next level by finding the size of the queue. 
    Follow the same procedure for the successive levels. 
    Store and update the maximum number of nodes found at each level.

	Time Complexity: O(N) where N is the total number of nodes in the tree. Every node of
	the tree is processed once and hence the complexity is O(N).
	Auxiliary Space: O(w) where w is the maximum width of the tree. 
*/

/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	Node(int d)
	{
		this->data = d;
		this->left = this->right = NULL;
	}
};

// Function to find the maximum width of the tree
// using level order traversal
int maxWidth(struct Node* root)
{
	// Base case
	if (root == NULL)
		return 0;

	// Initialize result
	int result = 0;

	// Do Level order traversal keeping track of number
	// of nodes at every level.
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		// Get the size of queue when the level order
		// traversal for one level finishes
		int count = q.size();

		// Update the maximum node count value
		result = max(count, result);

		// Iterate for all the nodes in the queue currently
		while (count--) {
			// Dequeue an node from queue
			Node* temp = q.front();
			q.pop();

			// Enqueue left and right children of
			// dequeued node
			if (temp->left != NULL)
				q.push(temp->left);
			if (temp->right != NULL)
				q.push(temp->right);
		}
	}

	return result;
}

// Driver code
int main()
{
	struct Node* root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(5);
	root->right->right = new Node(8);
	root->right->right->left = new Node(6);
	root->right->right->right = new Node(7);

	/* Constructed Binary tree is:
				1
			/ \
			2	 3
		/ \	 \
		4 5	 8
					/ \
				6	 7 */

	// Function call
	cout << "Maximum width is " << maxWidth(root) << endl;
	return 0;
}
