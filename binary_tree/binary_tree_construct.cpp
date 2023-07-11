#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/construct-tree-from-given-inorder-and-preorder-traversal/

/**
	Construct Tree from given Inorder and Preorder traversals

	Let us consider the below traversals:
    Inorder sequence: D B E A F C 
    Preorder sequence: A B D E C F

	In a Preorder sequence, the leftmost element is the root of the tree. So we know ‘A’
	is the root for given sequences. By searching ‘A’ in the Inorder sequence, we can find
	out all elements on the left side of ‘A’ is in the left subtree and elements on right
	in the right subtree. So we know the below structure now. 

	Algorithm: buildTree():
	- Pick an element from Preorder. Increment a Preorder Index Variable (preIndex in
	below code) to pick the next element in the next recursive call. 
	- Create a new tree node tNode with the data as the picked element. 
    - Find the picked element’s index in Inorder. Let the index be inIndex. 
	- Call buildTree for elements before inIndex and make the built tree as a left subtree
	of tNode. 
	- Call buildTree for elements after inIndex and make the built tree as a right subtree
	of tNode. 
    - return tNode.

	We can optimize the above solution using hashing (unordered_map in C++ or HashMap in
	Java). We store indexes of inorder traversal in a hash table. So that search can be
	done O(1) time. 

	Time Complexity: O(n)
	Auxiliary Space: O(n), The extra space is used to store the elements in the map also due to recursive function call stack.

*/

/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct Node {
	char data;
	struct Node* left;
	struct Node* right;
};

struct Node* newNode(char data)
{
	struct Node* node = new Node;
	node->data = data;
	node->left = node->right = NULL;
	return (node);
}

/* Recursive function to construct binary of size
len from Inorder traversal in[] and Preorder traversal
pre[]. Initial values of inStrt and inEnd should be
0 and len -1. The function doesn't do any error
checking for cases where inorder and preorder
do not form a tree */
struct Node* buildTree(char in[], char pre[], int inStrt,
					int inEnd, unordered_map<char, int>& mp)
{
	static int preIndex = 0;

	if (inStrt > inEnd)
		return NULL;

	/* Pick current node from Preorder traversal using preIndex
	and increment preIndex */
	char curr = pre[preIndex++];
	struct Node* tNode = newNode(curr);

	/* If this node has no children then return */
	if (inStrt == inEnd)
		return tNode;

	/* Else find the index of this node in Inorder traversal */
	int inIndex = mp[curr];

	/* Using index in Inorder traversal, construct left and
	right subtress */
	tNode->left = buildTree(in, pre, inStrt, inIndex - 1, mp);
	tNode->right = buildTree(in, pre, inIndex + 1, inEnd, mp);

	return tNode;
}

// This function mainly creates an unordered_map, then
// calls buildTree()
struct Node* buldTreeWrap(char in[], char pre[], int len)
{
	// Store indexes of all items so that we
	// we can quickly find later
	unordered_map<char, int> mp;
	for (int i = 0; i < len; i++)
		mp[in[i]] = i;

	return buildTree(in, pre, 0, len - 1, mp);
}

/* This function is here just to test buildTree() */
void printInorder(struct Node* node)
{
	if (node == NULL)
		return;
	printInorder(node->left);
	printf("%c ", node->data);
	printInorder(node->right);
}

/* Driver program to test above functions */
int main()
{
	char in[] = { 'D', 'B', 'E', 'A', 'F', 'C' };
	char pre[] = { 'A', 'B', 'D', 'E', 'C', 'F' };
	int len = sizeof(in) / sizeof(in[0]);

	struct Node* root = buldTreeWrap(in, pre, len);

	/* Let us test the built tree by printing
	Inorder traversal */
	printf("Inorder traversal of the constructed tree is \n");
	printInorder(root);
}
