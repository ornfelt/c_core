#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/circular-linked-list/

/**
	The circular linked list is a linked list where all nodes are connected to form a
	circle. In a circular linked list, the first node and the last node are connected to
	each other which forms a circle. There is no NULL at the end.

	Advantages of Circular Linked Lists: 

	- Any node can be a starting point. We can traverse the whole list by starting from any
	point. We just need to stop when the first visited node is visited again.
	- Useful for implementation of a queue. Unlike this implementation, we don’t need to
	maintain two pointers for front and rear if we use a circular linked list. We can
	maintain a pointer to the last inserted node and the front can always be obtained as
	next of last.

	- Circular lists are useful in applications to repeatedly go around the list. For
	example, when multiple applications are running on a PC, it is common for the
	operating system to put the running applications on a list and then cycle through
	them, giving each of them a slice of time to execute, and then making them wait while
	the CPU is given to another application. It is convenient for the operating system to
	use a circular list so that when it reaches the end of the list it can cycle around to
	the front of the list. 
	- Circular Doubly Linked Lists are used for the implementation of advanced data
	structures like the Fibonacci Heap.

	Disadvantages of circular linked list:

    - Compared to singly linked lists, circular lists are more complex.
	- Reversing a circular list is more complicated than singly or doubly reversing a
	circular list.
	- It is possible for the code to go into an infinite loop if it is not handled
	carefully.
    - It is harder to find the end of the list and control the loop.

	Applications of circular linked lists:

	- Multiplayer games use this to give each player a chance to play.
	- A circular linked list can be used to organize multiple running applications on an
	operating system. These applications are iterated over by the OS.

	Why circular linked list?
	A node always points to another node, so NULL assignment is not necessary.
    Any node can be set as the starting point.
    Nodes are traversed quickly from the first to the last.

	Time Complexity: O(N), Worst case occurs when the element to be deleted is the last
	element and we need to move through the whole list.
	Auxiliary Space: O(1), As constant extra space is used.
 */

// Structure for a node
class Node {
public:
	int data;
	Node* next;
};

// Function to insert a node at the
// beginning of a Circular linked list
void push(Node** head_ref, int data)
{

	// Create a new node and make head
	// as next of it.
	Node* ptr1 = new Node();
	ptr1->data = data;
	ptr1->next = *head_ref;

	// If linked list is not NULL then
	// set the next of last node
	if (*head_ref != NULL) {

		// Find the node before head and
		// update next of it.
		Node* temp = *head_ref;
		while (temp->next != *head_ref)
			temp = temp->next;
		temp->next = ptr1;
	}
	else

		// For the first node
		ptr1->next = ptr1;

	*head_ref = ptr1;
}

// Function to print nodes in a given
// circular linked list
void printList(Node* head)
{
	Node* temp = head;
	if (head != NULL) {
		do {
			cout << temp->data << " ";
			temp = temp->next;
		} while (temp != head);
	}

	cout << endl;
}

// Function to delete a given node
// from the list
void deleteNode(Node** head, int key)
{

	// If linked list is empty
	if (*head == NULL)
		return;

	// If the list contains only a
	// single node
	if ((*head)->data == key && (*head)->next == *head) {
		free(*head);
		*head = NULL;
		return;
	}

	Node *last = *head, *d;

	// If head is to be deleted
	if ((*head)->data == key) {

		// Find the last node of the list
		while (last->next != *head)
			last = last->next;

		// Point last node to the next of
		// head i.e. the second node
		// of the list
		last->next = (*head)->next;
		free(*head);
		*head = last->next;
		return;
	}

	// Either the node to be deleted is
	// not found or the end of list
	// is not reached
	while (last->next != *head && last->next->data != key) {
		last = last->next;
	}

	// If node to be deleted was found
	if (last->next->data == key) {
		d = last->next;
		last->next = d->next;
		free(d);
	}
	else
		cout << "Given node is not found in the list!!!\n";
}

// Driver code
int main()
{
	// Initialize lists as empty
	Node* head = NULL;

	// Created linked list will be
	// 2->5->7->8->10
	push(&head, 2);
	push(&head, 5);
	push(&head, 7);
	push(&head, 8);
	push(&head, 10);

	cout << "List Before Deletion: ";
	printList(head);

	deleteNode(&head, 7);

	cout << "List After Deletion: ";
	printList(head);

	return 0;
}
