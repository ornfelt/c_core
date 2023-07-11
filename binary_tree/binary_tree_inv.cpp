#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/invert-binary-tree/description/
// Also see this for how to construct and print tree: https://www.gormanalysis.com/blog/making-a-binary-search-tree-in-cpp/

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // Base Case
        if(root==NULL)
            return NULL;
        invertTree(root->left); //Call the left substree
        invertTree(root->right); //Call the right substree
        // Swap the nodes
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        return root; // Return the root
    }
};

// Class Node and main function (except the leetcode part is from link below)
// https://www.geeksforgeeks.org/introduction-to-binary-tree-data-structure-and-algorithm-tutorials/

class Node {
	public:
		int data;
		Node* left;
		Node* right;
		// Val is the key or the value that
		// has to be added to the data part
		Node(int val)
		{
			data = val;
			// Left and right child for node
			// will be initialized to null
			left = NULL;
			right = NULL;
		}
};

int main()
{
	/*create root*/
	Node* root = new Node(1);

	/* following is the tree after above statement
	1
	/ \
	NULL NULL
	*/
	root -> left = new Node(2);
	root -> right = new Node(3);

	/* 2 and 3 become left and right children of 1
	1
	/ \
	2 3
	/ \ / \
	NULL NULL NULL NULL
	*/
	root -> left -> left = new Node(4);
	/* 4 becomes left child of 2
		1
	/ \
	2	 3
	/ \ / \
	4 NULL NULL NULL
	/ \
	NULL NULL
	*/

	// ----------------------------------------------------------------------------------
	// Leetcode problem:
	// Input: root = [4,2,7,1,3,6,9]
	// Output: [4,7,2,9,6,3,1]

	// Time complexity: O(N)
	// Space complexity: O(N) Recursive stack space

	Solution s;
	// Make the nodes
	TreeNode testRoot(4);
	TreeNode testLeft(2);
	TreeNode testRight(7);
	TreeNode testLeftLeft(1);
	TreeNode testLeftRight(3);
	TreeNode testRightLeft(6);
	TreeNode testRightRight(9);

	// Connect nodes
	testRoot.left = &testLeft;
	testRoot.right = &testRight;

	testLeft.left = &testLeftLeft;
	testLeft.right = &testLeftRight;
	testRight.left = &testRightLeft;
	testRight.right = &testRightRight;

    // Print info about the root
	// Root children
    std::cout << "Root val: " << testRoot.val << ", left: " << testRoot.left->val << ", right: " << testRoot.right->val << std::endl;
	// Left childs children 
    std::cout << "Left child val: " << testRoot.left->val << ", left: " << testRoot.left->left->val << ", right: " << testRoot.left->right->val << std::endl;
	// Right childs children 
    std::cout << "Right child val: " << testRoot.right->val << ", left: " << testRoot.right->left->val << ", right: " << testRoot.right->right->val << std::endl;

	cout << endl;
	// Inverting the tree using recursive function
	TreeNode* invertedTree = s.invertTree(&testRoot);
    // Print info about the inverted root
    std::cout << "Root val: " << invertedTree->val << ", left: " << invertedTree->left->val << ", right: " << invertedTree->right->val << std::endl;
	// Left childs children 
    std::cout << "Left child val: " << invertedTree->left->val << ", left: " << invertedTree->left->left->val << ", right: " << invertedTree->left->right->val << std::endl;
	// Right childs children 
    std::cout << "Right child val: " << invertedTree->right->val << ", left: " << invertedTree->right->left->val << ", right: " << invertedTree->right->right->val << std::endl;

	return 0;
}
