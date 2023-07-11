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

	Search an element in a Linked List (Recursive Approach): 

	Follow the below steps to solve the problem:
		- If the head is NULL, return false.
		- If the head’s key is the same as X, return true;
		- Else recursively search in the next node. 

	Time Complexity: O(N)
	Auxiliary Space: O(N), Stack space used by recursive calls
 */

/* Link list node */
struct Node {
	int key;
	struct Node* next;
};

/* Given a reference (pointer to pointer) to the head
of a list and an int, push a new node on the front
of the list. */
void push(struct Node** head_ref, int new_key)
{
	/* allocate node */
	struct Node* new_node
		= (struct Node*)malloc(sizeof(struct Node));

	/* put in the key */
	new_node->key = new_key;

	/* link the old list of the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

/* Checks whether the value x is present in linked list */
bool search(struct Node* head, int x)
{
	// Base case
	if (head == NULL)
		return false;

	// If key is present in current node, return true
	if (head->key == x)
		return true;

	// Recur for remaining list
	return search(head->next, x);
}

/* Driver code*/
int main()
{
	/* Start with the empty list */
	struct Node* head = NULL;
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
