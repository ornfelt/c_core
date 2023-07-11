#include <iostream>

// https://www.geeksforgeeks.org/introduction-to-binary-tree-data-structure-and-algorithm-tutorials/

/**
	Tree is a hierarchical data structure. Main uses of trees include maintaining
	hierarchical data, providing moderate access and insert/delete operations. Binary
	trees are special cases of tree where every node has at most two children.

	Why to use Tree Data Structure? 
	1. One reason to use trees might be because you want to store information that
	naturally forms a hierarchy. For example, the file system on a computer: 
	2. Trees (with some ordering e.g., BST) provide moderate access/search (quicker than
	Linked List and slower than arrays). 
	3. Trees provide moderate insertion/deletion (quicker than Arrays and slower than
	Unordered Linked Lists). 
	4. Like Linked Lists and unlike Arrays, Trees don’t have an upper limit on the number
	of nodes as nodes are linked using pointers.

	The main applications of tree data structure: 

    - Manipulate hierarchical data. 
    - Make information easy to search (see tree traversal). 
    - Manipulate sorted lists of data. 
    - As a workflow for compositing digital images for visual effects. 
    - Router algorithms 
    - Form of multi-stage decision-making (see business chess). 
	- Trees can be used to represent the structure of a sentence, and can be used in
	parsing algorithms to analyze the grammar of a sentence.
	- Trees can be used to represent the decision-making process of computer-controlled
	characters in games, such as in decision trees.
	- Huffman coding uses a tree to represent the frequency of characters in a text, which
	can be used for data compression.
	- Trees are used to represent the syntax of a programming language, and can be used in
	compiler design to check the syntax of a program and generate machine code.
	- Binary Search Tree is a tree that allows fast search, insert, delete on a sorted
	data. It also allows finding closest item
	- Heap is a tree data structure which is implemented using arrays and used to
	implement priority queues.

	A binary tree is a tree data structure in which each node can have at most two
	children, which are referred to as the left child and the right child. The topmost
	node in a binary tree is called the root, and the bottom-most nodes are called leaves.
	A binary tree can be visualized as a hierarchical structure with the root at the top
	and the leaves at the bottom.

	Binary trees have many applications in computer science, including data storage and
	retrieval, expression evaluation, network routing, and game AI. They can also be used
	to implement various algorithms such as searching, sorting, and graph algorithms.
	A Binary Tree is labeled if every node is assigned a label and a Binary Tree is
	unlabelled if nodes are not assigned any label. 

	Tree Traversal algorithms can be classified broadly into two categories:
		Depth-First Search (DFS) Algorithms
		Breadth-First Search (BFS) Algorithms

	Traversal using DFS can be further classified into:
		Preorder Traversal (current-left-right)
		Inorder Traversal (left-current-right)
		Postorder Traversal (left-right-current)
	
	Traversal using BFS can be further classified into one class:
		Level Order Traversal:  Visit nodes level-by-level and left-to-right fashion at
		the same level. Here, the traversal is level-wise. 

	Time Complexity: O(h), h is height of tree.
	Auxiliary Space: O(h), h is height of tree.
*/

struct Node {
	int data;
	Node* left;
	Node* right;

	Node(int data) {
		this->data = data;
		this->left = nullptr;
		this->right = nullptr;
	}
};

class BinaryTree {
	public:
	Node* root;

	BinaryTree() {
		root = nullptr;
	}

	void addNode(int data) {
		Node* newNode = new Node(data);

		if (root == nullptr) {
			root = newNode;
		} else {
			Node* focusNode = root;
			Node* parent;

			while (true) {
				parent = focusNode;

				if (data < focusNode->data) {
					focusNode = focusNode->left;
					if (focusNode == nullptr) {
						parent->left = newNode;
						return;
					}
				} else {
					focusNode = focusNode->right;
					if (focusNode == nullptr) {
						parent->right = newNode;
						return;
					}
				}
			}
		}
	}

	void preOrderTraversal(Node* focusNode) {
		if (focusNode != nullptr) {
			std::cout << focusNode->data << " ";
			preOrderTraversal(focusNode->left);
			preOrderTraversal(focusNode->right);
		}
	}
};

int main() {
	BinaryTree tree;

	tree.addNode(50);
	tree.addNode(25);
	tree.addNode(75);
	tree.addNode(12);
	tree.addNode(37);
	tree.addNode(43);
	tree.addNode(30);

	tree.preOrderTraversal(tree.root);

	return 0;
}
