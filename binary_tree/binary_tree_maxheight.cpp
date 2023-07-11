#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/find-the-maximum-depth-or-height-of-a-tree/

/**
	Given a binary tree, the task is to find the height of the tree. Height of the tree is
	the number of edges in the tree from the root to the deepest node, Height of the empty
	tree is 0.

	Recursively calculate height of left and right subtrees of a node and assign height to
	the node as max of the heights of two children plus 1. See below pseudo code and
	program for details.

	Steps:
    Recursively do a Depth-first search.
    If the tree is empty then return -1
    Otherwise, do the following:
		Get the max depth of the left subtree recursively  i.e. call maxDepth(
		tree->left-subtree)
		Get the max depth of the right subtree recursively  i.e. call maxDepth(
		tree->right-subtree)
		Get the max of max depths of left and right subtrees and add 1 to it for the
		current node.
			max_depth = max(max dept of left subtree, max depth of right subtree) + 1
    Return max_depth.

	Time Complexity: O(N) (Please see our post Tree Traversal for details)
	Auxiliary Space: O(N) due to recursive stack.

*/

/* A binary tree node has data, pointer to left child
and a pointer to right child */
class node {
public:
	int data;
	node* left;
	node* right;
};

/* Compute the "maxDepth" of a tree -- the number of
	nodes along the longest path from the root node
	down to the farthest leaf node.*/
int maxDepth(node* node)
{
	if (node == NULL)
		return 0;
	else {
		/* compute the depth of each subtree */
		int lDepth = maxDepth(node->left);
		int rDepth = maxDepth(node->right);

		/* use the larger one */
		if (lDepth > rDepth)
			return (lDepth + 1);
		else
			return (rDepth + 1);
	}
}

// Find the Maximum Depth or Height of a Tree using Level Order Traversal
// Same complexity...
int height(node* root)
{
 
  // Initialising a variable to count the
  // height of tree
  queue<node*> q;
  q.push(root);
  int height = 0;
  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; i++) {
      node* temp = q.front();
      q.pop();
      if (temp->left != NULL) {
        q.push(temp->left);
      }
      if (temp->right != NULL) {
        q.push(temp->right);
      }
    }
    height++;
  }
  return height;
}



/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
node* newNode(int data)
{
	node* Node = new node();
	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;

	return (Node);
}

// Driver code
int main()
{
	node* root = newNode(1);

	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);

	cout << "Height of tree is " << maxDepth(root) << endl;

	// Find the Maximum Depth or Height of a Tree using Level Order Traversal
	// Same complexity...
	cout << "Height (using level order traversal) of tree is " << height(root) << endl;
	return 0;
}
