#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/

/**
	Given a linked list and a key ‘X‘ in, the task is to check if X is present in the
	linked list or not. 

	Examples:

    Input: 14->21->11->30->10, X = 14
    Output: Yes
    Explanation: 14 is present in the linked list.

    Input: 6->21->17->30->10->8, X = 13
    Output: No

	Search an element in a Linked List (Iterative Approach): 

	Follow the below steps to solve the problem:
		- Initialize a node pointer, current = head.
		- Do following while current is not NULL
			If the current value (i.e., current->key) is equal to the key being searched return true.
			Otherwise, move to the next node (current = current->next).
		- If the key is not found, return false 

	Time Complexity: O(N), Where N is the number of nodes in the LinkedList
	Auxiliary Space: O(1)
 */

/* Link list node */
class Node {
public:
	int key;
	Node* next;
};

/* Given a reference (pointer to pointer) to the head
of a list and an int, push a new node on the front
of the list. */
void push(Node** head_ref, int new_key)
{
	/* allocate node */
	Node* new_node = new Node();

	/* put in the key */
	new_node->key = new_key;

	/* link the old list of the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

/* Checks whether the value x is present in linked list */
bool search(Node* head, int x)
{
	Node* current = head; // Initialize current
	while (current != NULL) {
		if (current->key == x)
			return true;
		current = current->next;
	}
	return false;
}

/* Driver code*/
int main()
{
	/* Start with the empty list */
	Node* head = NULL;
	int x = 21;

	/* Use push() to construct below list
	14->21->11->30->10 */
	push(&head, 10);
	push(&head, 30);
	push(&head, 11);
	push(&head, 21);
	push(&head, 14);

	// Function call
	search(head, 21) ? cout << "Yes" : cout << "No";
	return 0;
}
