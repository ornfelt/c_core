#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/deletion-in-binary-search-tree/

/**
	A binary Search Tree is a node-based binary tree data structure which has the following properties:  

	The left subtree of a node contains only nodes with keys lesser than the node’s key.
	The right subtree of a node contains only nodes with keys greater than the node’s key.
    The left and right subtree each must also be a binary search tree. 
    There must be no duplicate nodes.

	The above properties of the Binary Search Tree provide an ordering among keys so that
	the operations like search, minimum and maximum can be done fast. If there is no
	order, then we may have to compare every key to search for a given key.

	Some Interesting Facts:  
    Inorder traversal of BST always produces sorted output.
	We can construct a BST with only Preorder or Postorder or Level Order traversal. Note
	that we can always get inorder traversal by sorting the only given traversal.
    Number of unique BSTs with n distinct keys is Catalan Number

	We recursively call delete() for the successor in the above recursive code. We can
	avoid recursive calls by keeping track of the parent node of the successor so that we
	can simply remove the successor by making the child of a parent NULL. We know that the
	successor would always be a leaf node.

	Time Complexity: O(h) ,where h is the height of the BST. 
	Auxiliary Space: O(1).
*/

struct Node {
	int key;
	struct Node *left, *right;
};

// A utility function to create a new BST node
Node* newNode(int item)
{
	Node* temp = new Node;
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

// A utility function to do inorder traversal of BST
void inorder(Node* root)
{
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

/* A utility function to insert a new node with given key in
* BST */
Node* insert(Node* node, int key)
{
	/* If the tree is empty, return a new node */
	if (node == NULL)
		return newNode(key);

	/* Otherwise, recur down the tree */
	if (key < node->key)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);

	/* return the (unchanged) node pointer */
	return node;
}

/* Given a binary search tree and a key, this function
deletes the key and returns the new root */
Node* deleteNode(Node* root, int k)
{
	// Base case
	if (root == NULL)
		return root;

	// Recursive calls for ancestors of
	// node to be deleted
	if (root->key > k) {
		root->left = deleteNode(root->left, k);
		return root;
	}
	else if (root->key < k) {
		root->right = deleteNode(root->right, k);
		return root;
	}

	// We reach here when root is the node
	// to be deleted.

	// If one of the children is empty
	if (root->left == NULL) {
		Node* temp = root->right;
		delete root;
		return temp;
	}
	else if (root->right == NULL) {
		Node* temp = root->left;
		delete root;
		return temp;
	}

	// If both children exist
	else {

		Node* succParent = root;

		// Find successor
		Node* succ = root->right;
		while (succ->left != NULL) {
			succParent = succ;
			succ = succ->left;
		}

		// Delete successor. Since successor
		// is always left child of its parent
		// we can safely make successor's right
		// right child as left of its parent.
		// If there is no succ, then assign
		// succ->right to succParent->right
		if (succParent != root)
			succParent->left = succ->right;
		else
			succParent->right = succ->right;

		// Copy Successor Data to root
		root->key = succ->key;

		// Delete Successor and return root
		delete succ;
		return root;
	}
}

// Driver Code
int main()
{
	/* Let us create following BST
			50
		/	 \
		30	 70
		/ \ / \
	20 40 60 80 */
	Node* root = NULL;
	root = insert(root, 50);
	root = insert(root, 30);
	root = insert(root, 20);
	root = insert(root, 40);
	root = insert(root, 70);
	root = insert(root, 60);
	root = insert(root, 80);

	printf("Inorder traversal of the given tree \n");
	inorder(root);

	printf("\n\nDelete 20\n");
	root = deleteNode(root, 20);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

	printf("\n\nDelete 30\n");
	root = deleteNode(root, 30);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

	printf("\n\nDelete 50\n");
	root = deleteNode(root, 50);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

	return 0;
}
