#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/solutions/174644/c-easy-to-understand-one-approach-to-solve-zigzag-level-order-traversal/
// Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. 
// (i.e., from left to right, then right to left for the next level and alternate between).
// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[20,9],[15,7]]

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
                
        if (!root) return {};
        
        queue<TreeNode*> q;
        vector<vector<int>> out;
            
        q.push(root);  
        int level = 0; /* to alternate levels, or a bool variable */
        
        while (!q.empty()) {
            
            int sz = q.size();  
            vector<int> curr(sz); 
            
            for (int i = 0; i < sz; i++) {
                
                TreeNode* tmp = q.front();
                q.pop();
                
                if (level == 0) {
                    curr[i] = tmp->val; // odd level, insert like 0, 1, 2, 3 etc. 
                } else {
                    curr[sz - i - 1] = tmp->val; /* even level insert from end. 3, 2, 1, 0. (sz - i - 1) to get the index from end */
                }
                
                if (tmp->left) q.push(tmp->left);
                if (tmp->right) q.push(tmp->right);
            }
            out.push_back(curr); // now push the level traversed to output vector
            level = !level; // toggle the level using negation. or level == 0 ? level = 1 : level = 0;
        }
        return out;
    }

	// This approch can be used to solve both level order traversal & zig zag traversal.
	// The same idea is used, but extended for zig-zag traversal. The only difference would be,
	// if we are on an even level (say second level)** insert into the vector from end. Odd levels insert from beginning.**
	vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {}; // return if root is null
        queue<TreeNode*> q;
        q.push(root); //push the root node.
        vector<vector<int>> out; //result vector
      
		 /*
		 * Idea is to create a vector for every level based on the queue size.
		 * eg: if a level has four elements say 1, 2, 3, 4 -> Then create a vector of size 4.
		 * 
		 * note: size of the queue is computed before the loop, so that we don't consider 
		 * newly pushed elements.
		 */
		 
        while (!q.empty()) {
            
            int sz = q.size(); /* current queue size */
            vector<int> curr(sz); /* vector of size sz */
						
            for (int i = 0; i < sz; i++) {
                TreeNode* tmp = q.front();
                q.pop();
                curr[i] = tmp->val; /* insert to the correct index */
				
				/* Add the left & right nodes to the queue in the loop. */
                if (tmp->left) q.push(tmp->left);
                if (tmp->right) q.push(tmp->right);
            }
            out.push_back(curr); /* once the level is done, push the vector to output vector. */
        }
        return out;
    }
};

// Driver function
int main()
{
	cout << "Hello World";

	// Input: root = [3,9,20,null,null,15,7]
	// Output: [[3],[20,9],[15,7]]
	Solution s;
	// Make the nodes
	TreeNode testRoot(3);
	TreeNode testLeft(9);
	TreeNode testRight(20);
	TreeNode testRightLeft(15);
	TreeNode testRightRight(7);

	// Connect nodes
	testRoot.left = &testLeft;
	testRoot.right = &testRight;
	testRight.left = &testRightLeft;
	testRight.right = &testRightRight;

    // Print info about the root
	// Root children
    std::cout << "Root val: " << testRoot.val << ", left: " << testRoot.left->val << ", right: " << testRoot.right->val << std::endl;
	// Left childs children 
    //std::cout << "Left child val: " << testRoot.left->val << ", left: " << testRoot.left->left->val << ", right: " << testRoot.left->right->val << std::endl;
	// Right childs children 
    std::cout << "Right child val: " << testRoot.right->val << ", left: " << testRoot.right->left->val << ", right: " << testRoot.right->right->val << std::endl;

	cout << endl;
	// Zigzag
	vector<vector<int>> zigzagTree = s.zigzagLevelOrder(&testRoot);
    // Print info about the zigzag root
	for(int i = 0; i < zigzagTree.size(); i++){
		for(int j = 0; j < zigzagTree[i].size(); j++){
			cout << zigzagTree[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	// Another way of formatting the input
	// [3,9,20,null,null,15,7]
    // TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	cout << "New:" << endl;
	TreeNode root(3, new TreeNode(9), new TreeNode(20));
	root.right->left = &testRightLeft;
	root.right->right = &testRightRight;

    std::cout << "Root val: " << root.val << ", left: " << root.left->val << ", right: " << root.right->val << std::endl;
    std::cout << "Right child val: " << root.right->val << ", left: " << root.right->left->val << ", right: " << root.right->right->val << std::endl;

	return 0;
}
