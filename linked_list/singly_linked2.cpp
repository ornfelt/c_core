#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/insertion-in-linked-list/

/**
	In this post, methods to insert a new node in the linked list are discussed. A node can be added in three ways 
    - At the front of the linked list  
    - After a given node. 
    - At the end of the linked list.

	Method by using a constructor call to reduce memory allocation work and code lines.

	Time Complexity: O(N) 
	Auxiliary Space: O(1)
 */
class node {
public:
	int data;
	node* next;

	// A constructor is called here
	node(int value)
	{

		// It automatically assigns the
		// value to the data
		data = value;

		// Next pointer is pointed to NULL
		next = NULL;
	}
};

// Function to insert an element
// at head position
void insertathead(node*& head, int val)
{
	node* n = new node(val);
	n->next = head;
	head = n;
}

// Function to insert a element
// at a specified position
void insertafter(node* head, int key, int val)
{
	node* n = new node(val);
	if (key == head->data) {
		n->next = head->next;
		head->next = n;
		return;
	}

	node* temp = head;
	while (temp->data != key) {
		temp = temp->next;
		if (temp == NULL) {
			return;
		}
	}
	n->next = temp->next;
	temp->next = n;
}

// Function to insert an
// element at the end
void insertattail(node*& head, int val)
{
	node* n = new node(val);
	if (head == NULL) {
		head = n;
		return;
	}

	node* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = n;
}

// Function to print the
// singly linked list
void print(node*& head)
{
	node* temp = head;

	while (temp != NULL) {
		cout << temp->data << " -> ";
		temp = temp->next;
	}
	cout << "NULL" << endl;
}

// Main function
int main()
{

	// Declaring an empty linked list
	node* head = NULL;

	insertathead(head, 1);
	insertathead(head, 2);
	cout << "After insertion at head: ";
	print(head);
	cout << endl;

	insertattail(head, 4);
	insertattail(head, 5);
	cout << "After insertion at tail: ";
	print(head);
	cout << endl;

	insertafter(head, 1, 2);
	insertafter(head, 5, 6);
	cout << "After insertion at a given position: ";
	print(head);
	cout << endl;

	return 0;
}