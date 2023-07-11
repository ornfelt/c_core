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

	Reverse a linked list using Recursion:
	
	The idea is to reach the last node of the linked list using recursion then 
	start reversing the linked list.
	
	Time Complexity: O(N), Visiting over every node one time 
	Auxiliary Space: O(N), Function call stack space
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

	Node* reverse(Node* head)
	{
		if (head == NULL || head->next == NULL)
			return head;

		/* reverse the rest list and put
		the first element at the end */
		Node* rest = reverse(head->next);
		head->next->next = head;

		/* tricky step -- see the diagram */
		head->next = NULL;

		/* fix the head pointer */
		return rest;
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

/* Driver program to test above function*/
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

	ll.head = ll.reverse(ll.head);

	cout << "\nReversed linked list \n";
	ll.print();
	return 0;
}
