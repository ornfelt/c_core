#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/

/**
	Write a function to count the number of nodes in a given singly linked list.

	Input: 2->4->1->9->5->3->6
	Output: 7 

	Recursive approach for finding the length of the linked list using constant space:
	To solve the problem follow the below idea:

	The above recursive approach can be modified to make it a tail recursive function and
	thus our auxiliary space will become O(1)

	Time Complexity: O(N), As we are traversing the list only once.
	Auxiliary Space: O(1), As we are using the tail recursive function, no extra space is
	used in the function call stack.
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
// A tail recursive function to count the nodes of a linked
// list
// default value of the count is used as zero
int getCount(Node* head, int count = 0)
{
	// base case
	if (head == NULL)
		return count;
	// move the pointer to next node and increase the count
	return getCount(head->next, count + 1);
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
	cout << "Count of nodes is " << getCount(head);
	return 0;
}
