#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/

/**
	Given two values n1 and n2 in a Binary Search Tree, find the Lowest Common Ancestor
	(LCA). You may assume that both values exist in the tree. 

	Let T be a rooted tree. The lowest common ancestor between two nodes n1 and n2 is
	defined as the lowest node in T that has both n1 and n2 as descendants (where we allow
	a node to be a descendant of itself). The LCA of n1 and n2 in T is the shared ancestor
	of n1 and n2 that is located farthest from the root [i.e., closest to n1 and n2].

	Time Complexity: O(H). where H is the height of the tree
	Auxiliary Space: O(1). The space complexity of the above solution is constant.
*/

class node {
public:
	int data;
	node *left, *right;
};

/* Function to find LCA of n1 and n2.
The function assumes that both n1 and n2
are present in BST */
node* lca(node* root, int n1, int n2)
{
	while (root != NULL) {
		// If both n1 and n2 are smaller than root,
		// then LCA lies in left
		if (root->data > n1 && root->data > n2)
			root = root->left;

		// If both n1 and n2 are greater than root,
		// then LCA lies in right
		else if (root->data < n1 && root->data < n2)
			root = root->right;

		else
			break;
	}
	return root;
}

/* Helper function that allocates
a new node with the given data.*/
node* newNode(int data)
{
	node* Node = new node();
	Node->data = data;
	Node->left = Node->right = NULL;
	return (Node);
}

/* Driver code*/
int main()
{
	// Let us construct the BST
	// shown in the above figure
	node* root = newNode(20);
	root->left = newNode(8);
	root->right = newNode(22);
	root->left->left = newNode(4);
	root->left->right = newNode(12);
	root->left->right->left = newNode(10);
	root->left->right->right = newNode(14);

	// Function calls
	int n1 = 10, n2 = 14;
	node* t = lca(root, n1, n2);
	cout << "LCA of " << n1 << " and " << n2 << " is "
		<< t->data << endl;

	n1 = 14, n2 = 8;
	t = lca(root, n1, n2);
	cout << "LCA of " << n1 << " and " << n2 << " is "
		<< t->data << endl;

	n1 = 10, n2 = 22;
	t = lca(root, n1, n2);
	cout << "LCA of " << n1 << " and " << n2 << " is "
		<< t->data << endl;
	return 0;
}
