#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/introduction-to-red-black-tree/
// https://www.geeksforgeeks.org/insertion-in-red-black-tree/
// https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/

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

	Time Complexity:  O(log n), as the height of red-black tree is O(log n) at most, and
	complexity of rotation is constant.
	Space Complexity:  O(n),  here ‘n’ is the number of nodes in the red-black trees.
*/

enum Color {RED, BLACK};

struct Node
{
	int data;
	bool color;
	Node *left, *right, *parent;

	// Constructor
	Node(int data)
	{
	this->data = data;
	left = right = parent = NULL;
	this->color = RED;
	}
};

// Class to represent Red-Black Tree
class RBTree
{
private:
	Node *root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixViolation(Node *&, Node *&);
public:
	// Constructor
	RBTree() { root = NULL; }
	void insert(const int &n);
	void inorder();
	void levelOrder();
};

// A recursive function to do inorder traversal
void inorderHelper(Node *root)
{
	if (root == NULL)
		return;

	inorderHelper(root->left);
	cout << root->data << " ";
	inorderHelper(root->right);
}

/* A utility function to insert
	a new node with given key
in BST */
Node* BSTInsert(Node* root, Node *pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL)
	return pt;

	/* Otherwise, recur down the tree */
	if (pt->data < root->data)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->data > root->data)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

// Utility function to do level order traversal
void levelOrderHelper(Node *root)
{
	if (root == NULL)
		return;

	std::queue<Node *> q;
	q.push(root);

	while (!q.empty())
	{
		Node *temp = q.front();
		cout << temp->data << " ";
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);

		if (temp->right != NULL)
			q.push(temp->right);
	}
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violations
// caused by BST insertion
void RBTree::fixViolation(Node *&root, Node *&pt)
{
	Node *parent_pt = NULL;
	Node *grand_parent_pt = NULL;

	while ((pt != root) && (pt->color != BLACK) &&
		(pt->parent->color == RED))
	{

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/* Case : A
			Parent of pt is left child
			of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left)
		{

			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			The uncle of pt is also red
			Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color ==
												RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else
			{
				/* Case : 2
				pt is right child of its parent
				Left-rotation required */
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is left child of its parent
				Right-rotation required */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color,
						grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/* Case : B
		Parent of pt is right child
		of Grand-parent of pt */
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color ==
													RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				pt is right child of its parent
				Left-rotation required */
				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color,
						grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}

// Function to insert a new node with given data
void RBTree::insert(const int &data)
{
	Node *pt = new Node(data);

	// Do a normal BST insert
	root = BSTInsert(root, pt);

	// fix Red Black Tree violations
	fixViolation(root, pt);
}

// Function to do inorder and level order traversals
void RBTree::inorder()	 { inorderHelper(root);}
void RBTree::levelOrder() { levelOrderHelper(root); }

// Driver Code
int main()
{
	RBTree tree;

	tree.insert(7);
	tree.insert(6);
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);

	cout << "Inorder Traversal of Created Tree\n";
	tree.inorder();

	cout << "\n\nLevel Order Traversal of Created Tree\n";
	tree.levelOrder();

	return 0;
}
