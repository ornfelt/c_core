#include <iostream>

using namespace std;

// https://www.geeksforgeeks.org/introduction-of-b-tree-2/
// https://www.geeksforgeeks.org/insert-operation-in-b-tree/

/**
	The limitations of traditional binary search trees can be frustrating. Meet the
	B-Tree, the multi-talented data structure that can handle massive amounts of data with
	ease. When it comes to storing and searching large amounts of data, traditional binary
	search trees can become impractical due to their poor performance and high memory
	usage. B-Trees, also known as B-Tree or Balanced Tree, are a type of self-balancing
	tree that was specifically designed to overcome these limitations.

	Unlike traditional binary search trees, B-Trees are characterized by the large number
	of keys that they can store in a single node, which is why they are also known as
	“large key” trees. Each node in a B-Tree can contain multiple keys, which allows the
	tree to have a larger branching factor and thus a shallower height. This shallow
	height leads to less disk I/O, which results in faster search and insertion
	operations. B-Trees are particularly well suited for storage systems that have slow,
	bulky data access such as hard drives, flash memory, and CD-ROMs.

	B-Trees maintain balance by ensuring that each node has a minimum number of keys, so
	the tree is always balanced. This balance guarantees that the time complexity for
	operations such as insertion, deletion, and searching is always O(log n), regardless
	of the initial shape of the tree.

	Search	O(log n)
	Insert	O(log n)
	Delete	O(log n)

	Properties of B-Tree: 
    - All leaves are at the same level.
	- B-Tree is defined by the term minimum degree ‘t‘. The value of ‘t‘ depends upon disk
	block size.
	- Every node except the root must contain at least t-1 keys. The root may contain a
	minimum of 1 key.
    - All nodes (including root) may contain at most (2*t – 1) keys.
    - Number of children of a node is equal to the number of keys in it plus 1.
	- All keys of a node are sorted in increasing order. The child between two keys k1 and
	k2 contains all keys in the range from k1 and k2.
	- B-Tree grows and shrinks from the root which is unlike Binary Search Tree. Binary
	Search Trees grow downward and also shrink from downward.
	- Like other balanced Binary Search Trees, the time complexity to search, insert and
	delete is O(log n).
    - Insertion of a Node in B-Tree happens only at Leaf Node.

	Traversal in B-Tree: 
	Traversal is also similar to Inorder traversal of Binary Tree. We start from the
	leftmost child, recursively print the leftmost child, then repeat the same process for
	the remaining children and keys. In the end, recursively print the rightmost child. 

	Search Operation in B-Tree: 
	Search is similar to the search in Binary Search Tree. Let the key to be searched is
	k:
    Start from the root and recursively traverse down. 
    For every visited non-leaf node, 
        If the node has the key, we simply return the node. 
		Otherwise, we recur down to the appropriate child (The child which is just before
		the first greater key) of the node. 
    If we reach a leaf node and don’t find k in the leaf node, then return NULL.

	Searching a B-Tree is similar to searching a binary tree. The algorithm is similar and
	goes with recursion. At each level, the search is optimized as if the key value is not
	present in the range of the parent then the key is present in another branch. As these
	values limit the search they are also known as limiting values or separation values.
	If we reach a leaf node and don’t find the desired key then it will display NULL.

	Applications of B-Trees:
    It is used in large databases to access data stored on the disk
    Searching for data in a data set can be achieved in significantly less time using the B-Tree
    With the indexing feature, multilevel indexing can be achieved.
    Most of the servers also use the B-tree approach.
    B-Trees are used in CAD systems to organize and search geometric data.
	B-Trees are also used in other areas such as natural language processing, computer
	networks, and cryptography.

	Advantages of B-Trees:
	B-Trees have a guaranteed time complexity of O(log n) for basic operations like
	insertion, deletion, and searching, which makes them suitable for large data sets and
	real-time applications.
	B-Trees are self-balancing.
	High-concurrency and high-throughput.
	Efficient storage utilization.

	Disadvantages of B-Trees:
	B-Trees are based on disk-based data structures and can have a high disk usage.
    Not the best for all cases.
    Slow in comparison to other data structures.
*/

// A BTree node
class BTreeNode
{
	int *keys; // An array of keys
	int t;	 // Minimum degree (defines the range for number of keys)
	BTreeNode **C; // An array of child pointers
	int n;	 // Current number of keys
	bool leaf; // Is true when node is leaf. Otherwise false
public:
	BTreeNode(int _t, bool _leaf); // Constructor

	// A utility function to insert a new key in the subtree rooted with
	// this node. The assumption is, the node must be non-full when this
	// function is called
	void insertNonFull(int k);

	// A utility function to split the child y of this node. i is index of y in
	// child array C[]. The Child y must be full when this function is called
	void splitChild(int i, BTreeNode *y);

	// A function to traverse all nodes in a subtree rooted with this node
	void traverse();

	// A function to search a key in the subtree rooted with this node.
	BTreeNode *search(int k); // returns NULL if k is not present.

// Make BTree friend of this so that we can access private members of this
// class in BTree functions
friend class BTree;
};

// A BTree
class BTree
{
	BTreeNode *root; // Pointer to root node
	int t; // Minimum degree
public:
	// Constructor (Initializes tree as empty)
	BTree(int _t)
	{ root = NULL; t = _t; }

	// function to traverse the tree
	void traverse()
	{ if (root != NULL) root->traverse(); }

	// function to search a key in this tree
	BTreeNode* search(int k)
	{ return (root == NULL)? NULL : root->search(k); }

	// The main function that inserts a new key in this B-Tree
	void insert(int k);
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1)
{
	// Copy the given minimum degree and leaf property
	t = t1;
	leaf = leaf1;

	// Allocate memory for maximum number of possible keys
	// and child pointers
	keys = new int[2*t-1];
	C = new BTreeNode *[2*t];

	// Initialize the number of keys as 0
	n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{
	// There are n keys and n+1 children, traverse through n keys
	// and first n children
	int i;
	for (i = 0; i < n; i++)
	{
		// If this is not leaf, then before printing key[i],
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			C[i]->traverse();
		cout << " " << keys[i];
	}

	// Print the subtree rooted with last child
	if (leaf == false)
		C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(int k)
{
	// Find the first key greater than or equal to k
	int i = 0;
	while (i < n && k > keys[i])
		i++;

	// If the found key is equal to k, return this node
	if (keys[i] == k)
		return this;

	// If key is not found here and this is a leaf node
	if (leaf == true)
		return NULL;

	// Go to the appropriate child
	return C[i]->search(k);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(int k)
{
	// If tree is empty
	if (root == NULL)
	{
		// Allocate memory for root
		root = new BTreeNode(t, true);
		root->keys[0] = k; // Insert key
		root->n = 1; // Update number of keys in root
	}
	else // If tree is not empty
	{
		// If root is full, then tree grows in height
		if (root->n == 2*t-1)
		{
			// Allocate memory for new root
			BTreeNode *s = new BTreeNode(t, false);

			// Make old root as child of new root
			s->C[0] = root;

			// Split the old root and move 1 key to the new root
			s->splitChild(0, root);

			// New root has two children now. Decide which of the
			// two children is going to have new key
			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->C[i]->insertNonFull(k);

			// Change root
			root = s;
		}
		else // If root is not full, call insertNonFull for root
			root->insertNonFull(k);
	}
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(int k)
{
	// Initialize index as index of rightmost element
	int i = n-1;

	// If this is a leaf node
	if (leaf == true)
	{
		// The following loop does two things
		// a) Finds the location of new key to be inserted
		// b) Moves all greater keys to one place ahead
		while (i >= 0 && keys[i] > k)
		{
			keys[i+1] = keys[i];
			i--;
		}

		// Insert the new key at found location
		keys[i+1] = k;
		n = n+1;
	}
	else // If this node is not leaf
	{
		// Find the child which is going to have the new key
		while (i >= 0 && keys[i] > k)
			i--;

		// See if the found child is full
		if (C[i+1]->n == 2*t-1)
		{
			// If the child is full, then split it
			splitChild(i+1, C[i+1]);

			// After split, the middle key of C[i] goes up and
			// C[i] is splitted into two. See which of the two
			// is going to have the new key
			if (keys[i+1] < k)
				i++;
		}
		C[i+1]->insertNonFull(k);
	}
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
	// Create a new node which is going to store (t-1) keys
	// of y
	BTreeNode *z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;

	// Copy the last (t-1) keys of y to z
	for (int j = 0; j < t-1; j++)
		z->keys[j] = y->keys[j+t];

	// Copy the last t children of y to z
	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j+t];
	}

	// Reduce the number of keys in y
	y->n = t - 1;

	// Since this node is going to have a new child,
	// create space of new child
	for (int j = n; j >= i+1; j--)
		C[j+1] = C[j];

	// Link the new child to this node
	C[i+1] = z;

	// A key of y will move to this node. Find the location of
	// new key and move all greater keys one space ahead
	for (int j = n-1; j >= i; j--)
		keys[j+1] = keys[j];

	// Copy the middle key of y to this node
	keys[i] = y->keys[t-1];

	// Increment count of keys in this node
	n = n + 1;
}

// Driver program to test above functions
int main()
{
	BTree t(3); // A B-Tree with minimum degree 3
	t.insert(10);
	t.insert(20);
	t.insert(5);
	t.insert(6);
	t.insert(12);
	t.insert(30);
	t.insert(7);
	t.insert(17);

	cout << "Traversal of the constructed tree is ";
	t.traverse();

	int k = 6;
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";

	k = 15;
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";

	return 0;
}
