#include <bits/stdc++.h>
#include <inttypes.h>
using namespace std;

// https://www.geeksforgeeks.org/xor-linked-list-reverse-a-linked-list-in-groups-of-given-size/?ref=rp

/**
    Given a XOR linked list and an integer K, the task is to reverse every K nodes in the given XOR linked list.
	
	Input: XLL = 7< – > 6 < – > 8 < – > 11 < – > 3, K = 3 
	Output: 8 < – > 6 < – > 7 < – > 3 < – > 11 
	Explanation: 
	Reversing first K(= 3) nodes modifies the Linked List to 8 < – > 6 < – > 7 < – > 11 < – > 3. 
	Reversing remaining nodes of the Linked List to 8 < – > 6 < – > 7 < – > 3 < – > 11. 
	Therefore, the required output is 8 < – > 6 < – > 7 < – > 3 < – > 11.

	Input: XLL = 7 < – > 6 < – > 8 < –> 11 < – > 3 < – > 1 < – > 2 < – > 0, K = 3 
	Output: 8 < – > 6 < – > 7 < – > 1 < – > 3 < – > 11 < – > 0 < – > 2
	
	Approach: The idea is to recursively reverse every K nodes of the XOR linked list in a group 
	and connect the first node of every group of K nodes to the last node of its previous group of nodes. 
	The recursive function is as follows:
	
	Follow these steps below to solve the problem:
    * Reverse the first K nodes of the XOR linked list and recursively reverse the remaining 
	nodes in a group of size K. If the count of remaining nodes is less than K, then just reverse 
	the remaining nodes.
    * Finally, connect the first node of every group to the last node of its previous group.
	
	Time Complexity: O(N)
	Auxiliary Space: O(N / K)
 */

// Structure of a node
// in XOR linked list
struct Node {

	// Stores data value
	// of a node
	int data;

	// Stores XOR of previous
	// pointer and next pointer
	struct Node* nxp;
};

// Function to find the XOR of address
// of two nodes
struct Node* XOR(struct Node* a, struct Node* b)
{
	return (struct Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// Function to insert a node with
// given value at given position
struct Node* insert(struct Node** head, int value)
{

	// If XOR linked list is empty
	if (*head == NULL) {

		// Initialize a new Node
		struct Node* node = new Node;

		// Stores data value in
		// the node
		node->data = value;

		// Stores XOR of previous
		// and next pointer
		node->nxp = XOR(NULL, NULL);

		// Update pointer of head node
		*head = node;
	}

	// If the XOR linked list
	// is not empty
	else {

		// Stores the address
		// of current node
		struct Node* curr = *head;

		// Stores the address
		// of previous node
		struct Node* prev = NULL;

		// Initialize a new Node
		struct Node* node
			= new Node();

		// Update curr node address
		curr->nxp = XOR(node, XOR(NULL, curr->nxp));

		// Update new node address
		node->nxp = XOR(NULL, curr);

		// Update head
		*head = node;

		// Update data value of
		// current node
		node->data = value;
	}
	return *head;
}

// Function to print elements of
// the XOR Linked List
void printList(struct Node** head)
{

	// Stores XOR pointer
	// in current node
	struct Node* curr = *head;

	// Stores XOR pointer of
	// in previous Node
	struct Node* prev = NULL;

	// Stores XOR pointer of
	// in next node
	struct Node* next;

	// Traverse XOR linked list
	while (curr != NULL) {

		// Print current node
		cout << curr->data << " ";

		// Forward traversal
		next = XOR(prev, curr->nxp);

		// Update prev
		prev = curr;

		// Update curr
		curr = next;
	}
}

// Reverse the linked list in group of K
struct Node* RevInGrp(struct Node** head, int K, int len)
{

	// Stores head node
	struct Node* curr = *head;

	// If the XOR linked
	// list is empty
	if (curr == NULL)
		return NULL;

	// Stores count of nodes
	// reversed in current group
	int count = 0;

	// Stores XOR pointer of
	// in previous Node
	struct Node* prev = NULL;

	// Stores XOR pointer of
	// in next node
	struct Node* next;

	// Reverse nodes in current group
	while (count < K && count < len) {

		// Forward traversal
		next = XOR(prev, curr->nxp);

		// Update prev
		prev = curr;

		// Update curr
		curr = next;

		// Update count
		count++;
	}

	// Disconnect prev node from the next node
	prev->nxp = XOR(NULL, XOR(prev->nxp, curr));

	// Disconnect curr from previous node
	if (curr != NULL)
		curr->nxp = XOR(XOR(curr->nxp, prev), NULL);

	// If the count of remaining
	// nodes is less than K
	if (len < K) {
		return prev;
	}
	else {

		// Update len
		len -= K;

		// Recursively process the next nodes
		struct Node* dummy = RevInGrp(&curr, K, len);

		// Connect the head pointer with the prev
		(*head)->nxp = XOR(XOR(NULL, (*head)->nxp), dummy);

		// Connect prev with the head
		if (dummy != NULL)
			dummy->nxp = XOR(XOR(dummy->nxp, NULL), *head);
		return prev;
	}
}

// Driver Code
int main()
{

	/* Create following XOR Linked List
	head-->7<–>6<–>8<–>11<–>3<–>1<–>2<–>0*/
	struct Node* head = NULL;
	insert(&head, 0);
	insert(&head, 2);
	insert(&head, 1);
	insert(&head, 3);
	insert(&head, 11);
	insert(&head, 8);
	insert(&head, 6);
	insert(&head, 7);

	// Function Call
	head = RevInGrp(&head, 3, 8);

	// Print the reversed list
	printList(&head);

	return (0);
}