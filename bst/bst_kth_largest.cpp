#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/k-largestor-smallest-elements-in-an-array/

/**
	Write an efficient program for printing K largest elements in an array. Elements in an
	array can be in any order

	Input:  [1, 23, 12, 9, 30, 2, 50], K = 3
	Output: 50, 30, 23

	Input:  [11, 5, 12, 9, 44, 17, 2], K = 2
	Output: 44, 17

	K largest(or smallest) elements in an array by creating a BST and Getting K greatest
Elements:

	To solve the problem follow the below idea:
	- We can create a BST of the given array elements and then print the K
	greatest/smallest elements

	Follow the below steps to solve the problem:
    - We will create a Binary Search Tree
    - Then traverse the BST in reverse inorder fashion for K times
    - Print the K largest elements

	Time Complexity: O(N * log(N)) + O(K) ~= O(N * log(N)) (here making of Binary Search
	Tree from array take n*log(n) time + O(n) time for finding top k element)
	Auxiliary Space: O(N) (to store the tree with N nodes we need O(N) space + O(K) space
	for storing the top K element to print)
*/

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

class Tree {
public:
	Node* root = NULL;
	void addNode(int data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		if (!root) {
			root = newNode;
		}
		else {
			Node* cur = root;
			while (cur) {
				if (cur->data > data) {
					if (cur->left) {
						cur = cur->left;
					}
					else {
						cur->left = newNode;
						return;
					}
				}
				else {
					if (cur->right) {
						cur = cur->right;
					}
					else {
						cur->right = newNode;
						return;
					}
				}
			}
		}
	}
	void printGreatest(int& K, vector<int>& sol, Node* node)
	{
		if (!node || K == 0)
			return;
		printGreatest(K, sol, node->right);
		if (K <= 0)
			return;
		sol.push_back(node->data);
		K--;
		printGreatest(K, sol, node->left);
	}
};

class Solution {
public:
	vector<int> kLargest(int arr[], int n, int k)
	{
		vector<int> sol;
		Tree tree = Tree();
		for (int i = 0; i < n; i++) {
			tree.addNode(arr[i]);
		}
		tree.printGreatest(k, sol, tree.root);
		return sol;
	}
};

// Driver code
int main()
{
	int n = 5, k = 2;
	int arr[] = { 12, 5, 787, 1, 23 };
	Solution ob;
	auto ans = ob.kLargest(arr, n, k);
	cout << "Top " << k << " Elements: ";
	for (auto x : ans) {
		cout << x << " ";
	}
	cout << "\n";
	return 0;
}
