#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/

/**
	Write a function to count the number of nodes in a given singly linked list.

	Input: 2->4->1->9->5->3->6
	Output: 7 

	An iterative approach for finding the length of the linked list:

	Follow the given steps to solve the problem:
		Initialize count as 0 
		Initialize a node pointer, current = head.
		Do following while current is not NULL
			current = current -> next
			Increment count by 1.
		Return count 

	Time complexity: O(N), Where N is the size of the linked list
	Auxiliary Space: O(1), As constant extra space is used.
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

/* Counts no. of nodes in linked list */
int getCount(Node* head)
{
	int count = 0; // Initialize count
	Node* current = head; // Initialize current
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

/* Driver code*/
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

	// Function call
	cout << "count of nodes is " << getCount(head);
	return 0;
}
