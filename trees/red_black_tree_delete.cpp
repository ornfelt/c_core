#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

// https://www.geeksforgeeks.org/deletion-in-red-black-tree/

/**
	When it comes to searching and sorting data, one of the most fundamental data
	structures is the binary search tree. However, the performance of a binary search tree
	is highly dependent on its shape, and in the worst case, it can degenerate into a
	linear structure with a time complexity of O(n). This is where Red Black Trees come
	in, they are a type of balanced binary search tree that use a specific set of rules to
	ensure that the tree is always balanced. This balance guarantees that the time
	complexity for operations such as insertion, deletion, and searching is always O(log
	n), regardless of the initial shape of the tree.

	Red Black Trees are self-balancing, meaning that the tree adjusts itself automatically
	after each insertion or deletion operation. It uses a simple but powerful mechanism to
	maintain balance, by coloring each node in the tree either red or black. 

	Red-Black tree is a binary search tree in which every node is colored with either red
	or black. It is a type of self balancing binary search tree. It has a good efficient
	worst case running time complexity.

	Search	O(log n)
	Insert	O(log n)
	Delete	O(log n)

	Comparison with AVL Tree:
	The AVL trees are more balanced compared to Red-Black Trees, but they may cause more
	rotations during insertion and deletion. So if your application involves frequent
	insertions and deletions, then Red-Black trees should be preferred. And if the
	insertions and deletions are less frequent and search is a more frequent operation,
	then AVL tree should be preferred over the Red-Black Tree.

	Applications: 
	1. Most of the self-balancing BST library functions like map, multiset, and multimap in
	C++ ( or  java packages like java.util.TreeMap and java.util.TreeSet ) use Red-Black
	Trees.
	2. It is used to implement CPU Scheduling Linux. Completely Fair Scheduler uses it.
	3. It is also used in the K-mean clustering algorithm in machine learning for reducing
	time complexity.
	4. Moreover, MySQL also uses the Red-Black tree for indexes on tables in order to
	reduce the searching and insertion time.
	5. Red Black Trees are used in the implementation of the virtual memory manager in
	some operating systems, to keep track of memory pages and their usage.
	6. Many programming languages such as Java, C++, and Python have implemented Red Black
	Trees as a built-in data structure for efficient searching and sorting of data.
	7. Red Black Trees are used in the implementation of graph algorithms such as
	Dijkstra’s shortest path algorithm and Prim’s minimum spanning tree algorithm.
    8. Red Black Trees are used in the implementation of game engines.

	Advantages:
	Red Black Trees have a guaranteed time complexity of O(log n) for basic operations
	like insertion, deletion, and searching.
    Red Black Trees are self-balancing.
	Red Black Trees can be used in a wide range of applications due to their efficient
	performance and versatility. 
	The mechanism used to maintain balance in Red Black Trees is relatively simple and
	easy to understand.

	Disadvantages:
	Red Black Trees require one extra bit of storage for each node to store the color of
	the node (red or black). 
    Complexity of Implementation.
	Although Red Black Trees provide efficient performance for basic operations, they may
	not be the best choice for certain types of data or specific use cases.

	Deletion:
    If the node to be deleted has no children, simply remove it and update the parent node.
    If the node to be deleted has only one child, replace the node with its child.
	If the node to be deleted has two children, then replace the node with its in-order
	successor, which is the leftmost node in the right subtree. Then delete the in-order
	successor node as if it has at most one child.
	After the node is deleted, the red-black properties might be violated. To restore
	these properties, some color changes and rotations are performed on the nodes in the
	tree. The changes are similar to those performed during insertion, but with different
	conditions.

	The deletion operation in a red-black tree takes O(log n) time on average, making it a
	good choice for searching and deleting elements in large data sets.
*/

enum COLOR { RED, BLACK };

class Node {
public:
int val;
COLOR color;
Node *left, *right, *parent;

Node(int val) : val(val) {
	parent = left = right = NULL;

	// Node is created during insertion
	// Node is red at insertion
	color = RED;
}

// returns pointer to uncle
Node *uncle() {
	// If no parent or grandparent, then no uncle
	if (parent == NULL or parent->parent == NULL)
	return NULL;

	if (parent->isOnLeft())
	// uncle on right
	return parent->parent->right;
	else
	// uncle on left
	return parent->parent->left;
}

// check if node is left child of parent
bool isOnLeft() { return this == parent->left; }

// returns pointer to sibling
Node *sibling() {
	// sibling null if no parent
	if (parent == NULL)
	return NULL;

	if (isOnLeft())
	return parent->right;

	return parent->left;
}

// moves node down and moves given node in its place
void moveDown(Node *nParent) {
	if (parent != NULL) {
	if (isOnLeft()) {
		parent->left = nParent;
	} else {
		parent->right = nParent;
	}
	}
	nParent->parent = parent;
	parent = nParent;
}

bool hasRedChild() {
	return (left != NULL and left->color == RED) or
		(right != NULL and right->color == RED);
}
};

class RBTree {
Node *root;

// left rotates the given node
void leftRotate(Node *x) {
	// new parent will be node's right child
	Node *nParent = x->right;

	// update root if current node is root
	if (x == root)
	root = nParent;

	x->moveDown(nParent);

	// connect x with new parent's left element
	x->right = nParent->left;
	// connect new parent's left element with node
	// if it is not null
	if (nParent->left != NULL)
	nParent->left->parent = x;

	// connect new parent with x
	nParent->left = x;
}

void rightRotate(Node *x) {
	// new parent will be node's left child
	Node *nParent = x->left;

	// update root if current node is root
	if (x == root)
	root = nParent;

	x->moveDown(nParent);

	// connect x with new parent's right element
	x->left = nParent->right;
	// connect new parent's right element with node
	// if it is not null
	if (nParent->right != NULL)
	nParent->right->parent = x;

	// connect new parent with x
	nParent->right = x;
}

void swapColors(Node *x1, Node *x2) {
	COLOR temp;
	temp = x1->color;
	x1->color = x2->color;
	x2->color = temp;
}

void swapValues(Node *u, Node *v) {
	int temp;
	temp = u->val;
	u->val = v->val;
	v->val = temp;
}

// fix red red at given node
void fixRedRed(Node *x) {
	// if x is root color it black and return
	if (x == root) {
	x->color = BLACK;
	return;
	}

	// initialize parent, grandparent, uncle
	Node *parent = x->parent, *grandparent = parent->parent,
		*uncle = x->uncle();

	if (parent->color != BLACK) {
	if (uncle != NULL && uncle->color == RED) {
		// uncle red, perform recoloring and recurse
		parent->color = BLACK;
		uncle->color = BLACK;
		grandparent->color = RED;
		fixRedRed(grandparent);
	} else {
		// Else perform LR, LL, RL, RR
		if (parent->isOnLeft()) {
		if (x->isOnLeft()) {
			// for left right
			swapColors(parent, grandparent);
		} else {
			leftRotate(parent);
			swapColors(x, grandparent);
		}
		// for left left and left right
		rightRotate(grandparent);
		} else {
		if (x->isOnLeft()) {
			// for right left
			rightRotate(parent);
			swapColors(x, grandparent);
		} else {
			swapColors(parent, grandparent);
		}

		// for right right and right left
		leftRotate(grandparent);
		}
	}
	}
}

// find node that do not have a left child
// in the subtree of the given node
Node *successor(Node *x) {
	Node *temp = x;

	while (temp->left != NULL)
	temp = temp->left;

	return temp;
}

// find node that replaces a deleted node in BST
Node *BSTreplace(Node *x) {
	// when node have 2 children
	if (x->left != NULL and x->right != NULL)
	return successor(x->right);

	// when leaf
	if (x->left == NULL and x->right == NULL)
	return NULL;

	// when single child
	if (x->left != NULL)
	return x->left;
	else
	return x->right;
}

// deletes the given node
void deleteNode(Node *v) {
	Node *u = BSTreplace(v);

	// True when u and v are both black
	bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
	Node *parent = v->parent;

	if (u == NULL) {
	// u is NULL therefore v is leaf
	if (v == root) {
		// v is root, making root null
		root = NULL;
	} else {
		if (uvBlack) {
		// u and v both black
		// v is leaf, fix double black at v
		fixDoubleBlack(v);
		} else {
		// u or v is red
		if (v->sibling() != NULL)
			// sibling is not null, make it red"
			v->sibling()->color = RED;
		}

		// delete v from the tree
		if (v->isOnLeft()) {
		parent->left = NULL;
		} else {
		parent->right = NULL;
		}
	}
	delete v;
	return;
	}

	if (v->left == NULL or v->right == NULL) {
	// v has 1 child
	if (v == root) {
		// v is root, assign the value of u to v, and delete u
		v->val = u->val;
		v->left = v->right = NULL;
		delete u;
	} else {
		// Detach v from tree and move u up
		if (v->isOnLeft()) {
		parent->left = u;
		} else {
		parent->right = u;
		}
		delete v;
		u->parent = parent;
		if (uvBlack) {
		// u and v both black, fix double black at u
		fixDoubleBlack(u);
		} else {
		// u or v red, color u black
		u->color = BLACK;
		}
	}
	return;
	}

	// v has 2 children, swap values with successor and recurse
	swapValues(u, v);
	deleteNode(u);
}

void fixDoubleBlack(Node *x) {
	if (x == root)
	// Reached root
	return;

	Node *sibling = x->sibling(), *parent = x->parent;
	if (sibling == NULL) {
	// No sibiling, double black pushed up
	fixDoubleBlack(parent);
	} else {
	if (sibling->color == RED) {
		// Sibling red
		parent->color = RED;
		sibling->color = BLACK;
		if (sibling->isOnLeft()) {
		// left case
		rightRotate(parent);
		} else {
		// right case
		leftRotate(parent);
		}
		fixDoubleBlack(x);
	} else {
		// Sibling black
		if (sibling->hasRedChild()) {
		// at least 1 red children
		if (sibling->left != NULL and sibling->left->color == RED) {
			if (sibling->isOnLeft()) {
			// left left
			sibling->left->color = sibling->color;
			sibling->color = parent->color;
			rightRotate(parent);
			} else {
			// right left
			sibling->left->color = parent->color;
			rightRotate(sibling);
			leftRotate(parent);
			}
		} else {
			if (sibling->isOnLeft()) {
			// left right
			sibling->right->color = parent->color;
			leftRotate(sibling);
			rightRotate(parent);
			} else {
			// right right
			sibling->right->color = sibling->color;
			sibling->color = parent->color;
			leftRotate(parent);
			}
		}
		parent->color = BLACK;
		} else {
		// 2 black children
		sibling->color = RED;
		if (parent->color == BLACK)
			fixDoubleBlack(parent);
		else
			parent->color = BLACK;
		}
	}
	}
}

// prints level order for given node
void levelOrder(Node *x) {
	if (x == NULL)
	// return if node is null
	return;

	// queue for level order
	queue<Node *> q;
	Node *curr;

	// push x
	q.push(x);

	while (!q.empty()) {
	// while q is not empty
	// dequeue
	curr = q.front();
	q.pop();

	// print node value
	cout << curr->val << " ";

	// push children to queue
	if (curr->left != NULL)
		q.push(curr->left);
	if (curr->right != NULL)
		q.push(curr->right);
	}
}

// prints inorder recursively
void inorder(Node *x) {
	if (x == NULL)
	return;
	inorder(x->left);
	cout << x->val << " ";
	inorder(x->right);
}

public:
// constructor
// initialize root
RBTree() { root = NULL; }

Node *getRoot() { return root; }

// searches for given value
// if found returns the node (used for delete)
// else returns the last node while traversing (used in insert)
Node *search(int n) {
	Node *temp = root;
	while (temp != NULL) {
	if (n < temp->val) {
		if (temp->left == NULL)
		break;
		else
		temp = temp->left;
	} else if (n == temp->val) {
		break;
	} else {
		if (temp->right == NULL)
		break;
		else
		temp = temp->right;
	}
	}

	return temp;
}

// inserts the given value to tree
void insert(int n) {
	Node *newNode = new Node(n);
	if (root == NULL) {
	// when root is null
	// simply insert value at root
	newNode->color = BLACK;
	root = newNode;
	} else {
	Node *temp = search(n);

	if (temp->val == n) {
		// return if value already exists
		return;
	}

	// if value is not found, search returns the node
	// where the value is to be inserted

	// connect new node to correct node
	newNode->parent = temp;

	if (n < temp->val)
		temp->left = newNode;
	else
		temp->right = newNode;

	// fix red red voilaton if exists
	fixRedRed(newNode);
	}
}

// utility function that deletes the node with given value
void deleteByVal(int n) {
	if (root == NULL)
	// Tree is empty
	return;

	Node *v = search(n), *u;

	if (v->val != n) {
	cout << "No node found to delete with value:" << n << endl;
	return;
	}

	deleteNode(v);
}

// prints inorder of the tree
void printInOrder() {
	cout << "Inorder: " << endl;
	if (root == NULL)
	cout << "Tree is empty" << endl;
	else
	inorder(root);
	cout << endl;
}

// prints level order of the tree
void printLevelOrder() {
	cout << "Level order: " << endl;
	if (root == NULL)
	cout << "Tree is empty" << endl;
	else
	levelOrder(root);
	cout << endl;
}
};

int main() {
	RBTree tree;

	tree.insert(7);
	tree.insert(3);
	tree.insert(18);
	tree.insert(10);
	tree.insert(22);
	tree.insert(8);
	tree.insert(11);
	tree.insert(26);
	tree.insert(2);
	tree.insert(6);
	tree.insert(13);

	tree.printInOrder();
	tree.printLevelOrder();

	cout<<endl<<"Deleting 18, 11, 3, 10, 22"<<endl;

	tree.deleteByVal(18);
	tree.deleteByVal(11);
	tree.deleteByVal(3);
	tree.deleteByVal(10);
	tree.deleteByVal(22);

	tree.printInOrder();
	tree.printLevelOrder();
	return 0;
}

