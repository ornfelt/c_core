#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/reverse-a-linked-list/

/**
	Given a pointer to the head node of a linked list, the task is to reverse the linked
	list. We need to reverse the list by changing the links between nodes.

	Examples: 
    Input: Head of following linked list 
    1->2->3->4->NULL 
    Output: Linked list should be changed to, 
    4->3->2->1->NULL

    Input: Head of following linked list 
    1->2->3->4->5->NULL 
    Output: Linked list should be changed to, 
    5->4->3->2->1->NULL

	Reverse a linked list by Iterative Method:
	The idea is to use three pointers curr, prev, and next to keep track of nodes to
	update reverse links.

	Time Complexity: O(N), Traversing over the linked list of size N. 
	Auxiliary Space: O(1)
 */

/* Link list node */
struct Node {
	int data;
	struct Node* next;
	Node(int data)
	{
		this->data = data;
		next = NULL;
	}
};

struct LinkedList {
	Node* head;
	LinkedList() { head = NULL; }

	/* Function to reverse the linked list */
	void reverse()
	{
		// Initialize current, previous and next pointers
		Node* current = head;
		Node *prev = NULL, *next = NULL;

		while (current != NULL) {
			// Store next
			next = current->next;
			// Reverse current node's pointer
			current->next = prev;
			// Move pointers one position ahead.
			prev = current;
			current = next;
		}
		head = prev;
	}

	/* Function to print linked list */
	void print()
	{
		struct Node* temp = head;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
	}

	void push(int data)
	{
		Node* temp = new Node(data);
		temp->next = head;
		head = temp;
	}
};

/* Driver code*/
int main()
{
	/* Start with the empty list */
	LinkedList ll;
	ll.push(20);
	ll.push(4);
	ll.push(15);
	ll.push(85);

	cout << "Given linked list\n";
	ll.print();

	ll.reverse();

	cout << "\nReversed linked list \n";
	ll.print();
	return 0;
}
