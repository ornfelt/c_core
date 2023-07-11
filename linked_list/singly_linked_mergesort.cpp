#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/merge-sort-for-linked-list/

/**
	Merge sort is often preferred for sorting a linked list. The slow random-access
	performance of a linked list makes some other algorithms (such as quicksort) perform
	poorly, and others (such as heapsort) completely impossible. 

	Let the head be the first node of the linked list to be sorted and headRef be the
	pointer to head. Note that we need a reference to head in MergeSort() as the below
	implementation changes next links to sort the linked lists (not data at the nodes), so
	the head node has to be changed if the data at the original head is not the smallest
	value in the linked list. 

	mergeSort():
    - If the size of the linked list is 1 then return the head
    - Find mid using The Tortoise and The Hare Approach
    - Store the next of mid in head2 i.e. the right sub-linked list.
    - Now Make the next midpoint null.
	- Recursively call mergeSort() on both left and right sub-linked list and store the
	new head of the left and right linked list.
	- Call merge() given the arguments new heads of left and right sub-linked lists and
	store the final head returned after merging.
    - Return the final head of the merged linkedlist.

	merge(head1, head2):
	- Take a pointer say merged to store the merged list in it and store a dummy node in
	it.
    - Take a pointer temp and assign merge to it.
	- If the data of head1 is less than the data of head2, then, store head1 in next of
	temp & move head1 to the next of head1.
    - Else store head2 in next of temp & move head2 to the next of head2.
    - Move temp to the next of temp.
	- Repeat steps 3, 4 & 5 until head1 is not equal to null and head2 is not equal to
	null.
	- Now add any remaining nodes of the first or the second linked list to the merged
	linked list.
	- Return the next of merged(that will ignore the dummy and return the head of the
	final merged linked list)

	Time Complexity: O(n*log n)
	Auxiliary Space: O(log n)
*/

// Node structure
struct Node {
	int data;
	Node* next;
};

// function to insert in list
void insert(int x, Node** head)
{
	if (*head == NULL) {
		*head = new Node;
		(*head)->data = x;
		(*head)->next = NULL;
		return;
	}
	Node* temp = new Node;
	temp->data = (*head)->data;
	temp->next = (*head)->next;
	(*head)->data = x;
	(*head)->next = temp;
}

// function to print the list
void print(Node* head)
{
	Node* temp = head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
}

Node* merge(Node* firstNode, Node* secondNode)
{
	Node* merged = new Node;
	Node* temp = new Node;

	// merged is equal to temp so in the end we have the top
	// Node.
	merged = temp;

	// while either firstNode or secondNode becomes NULL
	while (firstNode != NULL && secondNode != NULL) {

		if (firstNode->data <= secondNode->data) {
			temp->next = firstNode;
			firstNode = firstNode->next;
		}

		else {
			temp->next = secondNode;
			secondNode = secondNode->next;
		}
		temp = temp->next;
	}

	// any remaining Node in firstNode or secondNode gets
	// inserted in the temp List
	while (firstNode != NULL) {
		temp->next = firstNode;
		firstNode = firstNode->next;
		temp = temp->next;
	}

	while (secondNode != NULL) {
		temp->next = secondNode;
		secondNode = secondNode->next;
		temp = temp->next;
	}
	// return the head of the sorted list
	return merged->next;
}

// function to calculate the middle Element
Node* middle(Node* head)
{
	Node* slow = head;
	Node* fast = head->next;

	while (!slow->next && (!fast && !fast->next)) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

// function to sort the given list
Node* sort(Node* head)
{

	if (head->next == NULL) {
		return head;
	}

	Node* mid = new Node;
	Node* head2 = new Node;
	mid = middle(head);
	head2 = mid->next;
	mid->next = NULL;
	// recursive call to sort() hence diving our problem,
	// and then merging the solution
	Node* finalhead = merge(sort(head), sort(head2));
	return finalhead;
}
int main(void)
{
	Node* head = NULL;
	int n[] = { 7, 10, 5, 20, 3, 2 };
	for (int i = 0; i < 6; i++) {
		insert(n[i], &head); // inserting in the list
	}
	cout << "Sorted Linked List is: \n";
	print(sort(head)); // printing the sorted list returned
					// by sort()
	return 0;
}
