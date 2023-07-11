#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/

/**
	Write a function to count the number of nodes in a given singly linked list.

	Input: 2->4->1->9->5->3->6
	Output: 7 

	A recursive approach for finding the length of the linked list:

	Follow the given steps to solve the problem:
		If the head is NULL, return 0.
		Otherwise, return 1 + getCount(head->next) 

	Time Complexity: O(N), As we are traversing the linked list only once.
	Auxiliary Space: O(N), Extra space is used in the recursion call stack.
 */

/* Link list node */
class Node {
public:
	int data;
	Node* next;
};

/* Given a reference (pointer to pointer) to the head
of a list and an int, push a new node on the front
of the list. */
void push(Node** head_ref, int new_data)
{
	/* allocate node */
	Node* new_node = new Node();

	/* put in the data */
	new_node->data = new_data;

	/* link the old list of the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

/* Recursively count number of nodes in linked list */
int getCount(Node* head)
{
	// Base Case
	if (head == NULL) {
		return 0;
	}
	// Count this node plus the rest of the list
	else {
		return 1 + getCount(head->next);
	}
}

/* Driver program to test count function*/
int main()
{
	/* Start with the empty list */
	Node* head = NULL;

	/* Use push() to construct below list
	1->2->1->3->1 */
	push(&head, 1);
	push(&head, 3);
	push(&head, 1);
	push(&head, 2);
	push(&head, 1);

	/* Check the count function */
	cout << "Count of nodes is " << getCount(head);
	return 0;
}
