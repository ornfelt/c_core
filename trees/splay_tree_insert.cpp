#include<bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/insertion-in-splay-tree/

/**
	Splay tree is a binary search tree. In a splay tree, M consecutive operations can be
	performed in O (M log N) time.

	A single operation may require O(N) time but average time to perform M operations will
	need O (M Log N) time.

	When a node is accessed, it is moved to the top through a set of operations known as
	splaying. Splaying technique is similar to rotation in an AVL tree. This will make the
	future access of the node cheaper.

	Unlike AVL tree, splay trees do not have the requirement of storing Balance Factor of
	every node. This saves the space and simplifies algorithm to a great extent.

	There are two standard techniques of splaying.
	1. Bottom up Splaying:
	Idea behind bottom up splaying is explained below: Rotation is performed bottom up
	along the access path.

	2. Top Down Splaying:
	When an item X is inserted as a leaf, a series of tree rotations brings X at the root.
	These rotations are known as splaying. A splay is also performed during searches, and
	if an item is not found, a splay is performed on the last node on the access path.

	The important thing to note is, the search or splay operation not only brings the
	searched key to root, but also balances the BST. For example in above case, height of
	BST is reduced by 1

	Following are different cases to insert a key k in splay tree.
	1) Root is NULL: We simply allocate a new node and return it as root.
	2) Splay the given key k. If k is already present, then it becomes the new root. If
	not present, then last accessed leaf node becomes the new root.
	3) If new root’s key is same as k, don’t do anything as k is already present.
	4) Else allocate memory for new node and compare root’s key with k. 
	…….4.a) If k is smaller than root’s key, make root as right child of new node, copy
	left child of root as left child of new node and make left child of root as NULL. 
	…….4.b) If k is greater than root’s key, make root as left child of new node, copy
	right child of root as right child of new node and make right child of root as NULL.
	5) Return new node as new root of tree.

	The worst case time complexity of Binary Search Tree (BST) operations like search,
	delete, insert is O(n). The worst case occurs when the tree is skewed. We can get the
	worst case time complexity as O(Logn) with AVL and Red-Black Trees. 
	Can we do better than AVL or Red-Black trees in practical situations? 
	Like AVL and Red-Black Trees, Splay tree is also self-balancing BST. The main idea of
	splay tree is to bring the recently accessed item to root of the tree, this makes the
	recently searched item to be accessible in O(1) time if accessed again. The idea is to
	use locality of reference (In a typical application, 80% of the access are to 20% of
	the items). Imagine a situation where we have millions or billions of keys and only
	few of them are accessed frequently, which is very likely in many practical
	applications.
	All splay tree operations run in O(log n) time on average, where n is the number of
	entries in the tree. Any single operation can take Theta(n) time in the worst case.
*/

// An AVL tree node
class node
{
	public:
	int key;
	node *left, *right;
};

/* Helper function that allocates
a new node with the given key and
	NULL left and right pointers. */
node* newNode(int key)
{
	node* Node = new node();
	Node->key = key;
	Node->left = Node->right = NULL;
	return (Node);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
node *rightRotate(node *x)
{
	node *y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
node *leftRotate(node *x)
{
	node *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

// This function brings the key at
// root if key is present in tree.
// If key is not present, then it
// brings the last accessed item at
// root. This function modifies the
// tree and returns the new root
node *splay(node *root, int key)
{
	// Base cases: root is NULL or
	// key is present at root
	if (root == NULL || root->key == key)
		return root;

	// Key lies in left subtree
	if (root->key > key)
	{
		// Key is not in tree, we are done
		if (root->left == NULL) return root;

		// Zig-Zig (Left Left)
		if (root->left->key > key)
		{
			// First recursively bring the
			// key as root of left-left
			root->left->left = splay(root->left->left, key);

			// Do first rotation for root,
			// second rotation is done after else
			root = rightRotate(root);
		}
		else if (root->left->key < key) // Zig-Zag (Left Right)
		{
			// First recursively bring
			// the key as root of left-right
			root->left->right = splay(root->left->right, key);

			// Do first rotation for root->left
			if (root->left->right != NULL)
				root->left = leftRotate(root->left);
		}

		// Do second rotation for root
		return (root->left == NULL)? root: rightRotate(root);
	}
	else // Key lies in right subtree
	{
		// Key is not in tree, we are done
		if (root->right == NULL) return root;

		// Zig-Zag (Right Left)
		if (root->right->key > key)
		{
			// Bring the key as root of right-left
			root->right->left = splay(root->right->left, key);

			// Do first rotation for root->right
			if (root->right->left != NULL)
				root->right = rightRotate(root->right);
		}
		else if (root->right->key < key)// Zag-Zag (Right Right)
		{
			// Bring the key as root of
			// right-right and do first rotation
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}

		// Do second rotation for root
		return (root->right == NULL)? root: leftRotate(root);
	}
}

// Function to insert a new key k
// in splay tree with given root
node *insert(node *root, int k)
{
	// Simple Case: If tree is empty
	if (root == NULL) return newNode(k);

	// Bring the closest leaf node to root
	root = splay(root, k);

	// If key is already present, then return
	if (root->key == k) return root;

	// Otherwise allocate memory for new node
	node *newnode = newNode(k);

	// If root's key is greater, make
	// root as right child of newnode
	// and copy the left child of root to newnode
	if (root->key > k)
	{
		newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
	}

	// If root's key is smaller, make
	// root as left child of newnode
	// and copy the right child of root to newnode
	else
	{
		newnode->left = root;
		newnode->right = root->right;
		root->right = NULL;
	}

	return newnode; // newnode becomes new root
}

// A utility function to print
// preorder traversal of the tree.
// The function also prints height of every node
void preOrder(node *root)
{
	if (root != NULL)
	{
		cout<<root->key<<" ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

/* Driver code*/
int main()
{
	node *root = newNode(100);
	root->left = newNode(50);
	root->right = newNode(200);
	root->left->left = newNode(40);
	root->left->left->left = newNode(30);
	root->left->left->left->left = newNode(20);
	root = insert(root, 25);
	cout<<"Preorder traversal of the modified Splay tree is \n";
	preOrder(root);
	return 0;
}
