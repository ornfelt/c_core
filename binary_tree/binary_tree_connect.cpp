#include <iostream>
#include <queue>

using namespace std;

// https://www.geeksforgeeks.org/connect-nodes-at-same-level/

/**
	Given a Binary Tree, The task is to connect all the adjacent nodes at the same level
	starting from the left-most node of that level, and ending at the right-most node
	using nextRight pointer by setting these pointers to point the next right for each
	node. 

	Steps:
    Initialize a node pointer Prev to NULL and a queue of node pointer Q.
    Traverse the tree in Breadth-first search order starting from the root.
        Calculate the size sz of the Q and run a for loop from 0 to sz – 1.
            If prev is Null then set prev to the current node.
            Else set prev’s next to the current node and prev to the current node.
        Set prev’s next to Null and prev to Null.
        If the current node’s left is not null push it into the queue.  
        If the current node’s right is not null push it into the queue.

	Time Complexity: O(N)
	Auxiliary Space: O(N)
*/

// A Binary Tree Node
class node {
public:
	int data;
	node* left;
	node* right;
	node* nextRight;

	/* Constructor that allocates a new node with the
	given data and NULL left and right pointers. */
	node(int data)
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
		this->nextRight = NULL;
	}
};
// setting right pointer to next right node
/*
			10 ----------> NULL
			/ \
		8 --->2 --------> NULL
		/
		3 ----------------> NULL
		*/
void connect(node* root)
{
	// Base condition
	if (root == NULL)
		return;
	// Create an empty queue like level order traversal
	queue<node*> q;
	q.push(root);
	while (!q.empty()) {
		// size indicates no. of nodes at current level
		int size = q.size();
		// for keeping track of previous node
		node* prev = NULL;
		while (size--) {
			node* temp = q.front();
			q.pop();

			if (temp->left)
				q.push(temp->left);

			if (temp->right)
				q.push(temp->right);

			if (prev != NULL)
				prev->nextRight = temp;
			prev = temp;
		}
		prev->nextRight = NULL;
	}
}

int main()
{
	/* Constructed binary tree is
		10
		/ \
		8	 2
	/
	3
	*/
	// Let us create binary tree shown above
	node* root = new node(10);
	root->left = new node(8);
	root->right = new node(2);
	root->left->left = new node(3);
	connect(root);
	// Let us check the values
	// of nextRight pointers
	cout << "Following are populated nextRight pointers in "
			"the tree"
			" (-1 is printed if there is no nextRight)\n";
	cout << "nextRight of " << root->data << " is "
		<< (root->nextRight ? root->nextRight->data : -1)
		<< endl;
	cout << "nextRight of " << root->left->data << " is "
		<< (root->left->nextRight
				? root->left->nextRight->data
				: -1)
		<< endl;
	cout << "nextRight of " << root->right->data << " is "
		<< (root->right->nextRight
				? root->right->nextRight->data
				: -1)
		<< endl;
	cout << "nextRight of " << root->left->left->data
		<< " is "
		<< (root->left->left->nextRight
				? root->left->left->nextRight->data
				: -1)
		<< endl;
	return 0;
}
