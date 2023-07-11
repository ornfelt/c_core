#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/trie-insert-and-search/

/**
	What is Trie?
	Trie is a type of k-ary search tree used for storing and searching a specific key from
	a set. Using Trie, search complexities can be brought to optimal limit (key length). 

	Definition: A trie (derived from retrieval) is a multiway tree data structure used for
	storing strings over an alphabet. It is used to store a large amount of strings. The
	pattern matching can be done efficiently using tries.

	The trie shows words like allot, alone, ant, and, are, bat, bad. The idea is that all
	strings sharing common prefix should come from a common node. The tries are used in
	spell checking programs.

	Preprocessing pattern improves the performance of pattern matching algorithm. But if a
	text is very large then it is better to preprocess text instead of pattern for
	efficient search.
	A trie is a data structure that supports pattern matching queries in time proportional
	to the pattern size.

	If we store keys in a binary search tree, a well balanced BST will need time
	proportional to M * log N, where M is the maximum string length and N is the number of
	keys in the tree. Using Trie, the key can be searched in O(M) time. However, the
	penalty is on Trie storage requirements (Please refer to Applications of Trie for more
	details).

	Time complexity and space:
	Insertion	O(n)	O(n*m)
	Searching	O(n)	O(1)
*/

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	// isEndOfWord is true if the node represents
	// end of a word
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->isEndOfWord);
}

// Driver
int main()
{
	// Input keys (use only 'a' through 'z'
	// and lower case)
	string keys[] = {"the", "a", "there",
					"answer", "any", "by",
					"bye", "their" };
	int n = sizeof(keys)/sizeof(keys[0]);

	struct TrieNode *root = getNode();

	// Construct trie
	for (int i = 0; i < n; i++)
		insert(root, keys[i]);

	// Search for different keys
	char output[][32] = {"Not present in trie", "Present in trie"};

	// Search for different keys
	cout<<"the"<<" --- "<<output[search(root, "the")]<<endl;
	cout<<"these"<<" --- "<<output[search(root, "these")]<<endl;
	cout<<"their"<<" --- "<<output[search(root, "their")]<<endl;
	cout<<"thaw"<<" --- "<<output[search(root, "thaw")]<<endl;
	return 0;
}
