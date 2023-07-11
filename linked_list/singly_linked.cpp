#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/what-is-linked-list/

/**
    Search is O(n) because as data is not stored in contiguous memory locations so we have to traverse one by one.
    Insertion and Deletion are O(1) because we have to just link new nodes for Insertion with the previous 
	and next node and dislink exist nodes for deletion from the previous and next nodes without any traversal.

	Auxiliary Space: O(N) [To store dynamic memory]

	Applications of Linked Lists
		- Linked Lists can be used to implement useful data structures like stacks and queues. 
		- Linked Lists can be used to implement hash tables, each bucket of the hash table can be a linked list. 
		- Linked Lists can be used to implement graphs (Adjacency List representation of graph). 
		- Linked Lists can be used in a refined way in implementing different file systems in one form or another.
 */

class Node {
public:
	int data;
	Node* next;
};

// This function prints contents of linked list
// starting from the given node
void printList(Node* n)
{
	cout << "List:" << endl;
	while (n != NULL) {
		cout << n->data << " ";
		n = n->next;
	}
	cout << endl;
}


void deleteStart(Node** head){
    Node* temp = *head;
  
    // If head is NULL it means Singly Linked List is empty
    if(*head == NULL){
        printf("Impossible to delete from empty Singly Linked List");
        return;
    }
    
    // move head to next node
    *head = (*head)->next;
    printf("Deleted: %d\n", temp->data);
    free(temp);
}

void insertStart(Node** head, int data){
    
    // dynamically create memory for this newNode
    Node* newNode = (Node*) malloc(sizeof(Node));
    
    // assign data value
    newNode->data = data;
    // change the next node of this newNode 
    // to current head of Linked List
    newNode->next = *head;

    //re-assign head to this newNode
    *head = newNode;
    printf("Inserted %d\n",newNode->data);
}

void display(Node* node){
    printf("\nLinked List: ");
    // as linked list will end when Node is Null
    while(node!=NULL){
        printf("%d ",node->data);
        node = node->next;
    }
    printf("\n");
}

//From: https://wordaligned.org/articles/two-star-programming
void remove_if( Node **head, int rm_data)
{
    for (Node **curr = head; *curr; )
    {
        Node *entry = *curr;
        //if (rm_fn(entry))
		if(entry->data == rm_data)
        {
			printf("Removed: %d\n", entry->data);
            *curr = entry->next;
            free(entry);
        }
        else
            curr = &entry->next;
    }
}

// Driver's code
int main()
{
	Node* head = NULL;
	//Node* second = NULL;
	//Node* third = NULL;
	//Node* fourth = NULL;
	//Node* fifth = NULL;
	//// allocate 5 nodes in the heap
	//head = new Node();
	//second = new Node();
	//third = new Node();
	//fourth = new Node();
	//fifth = new Node();

	//head->data = 1; // assign data in first node
	//head->next = second; // Link first node with second
	//second->data = 2; // assign data to second node
	//second->next = third;
	//third->data = 3; // assign data to third node
	////third->next = NULL;

	//// new nodes
	//third->next = fourth;
	//fourth->data = 4;
	//fourth->next = fifth;
	//fifth->data = 5;
	//fifth->next = NULL;

    // Need '&' i.e. address as we need to change head
    insertStart(&head,5);
    insertStart(&head,4);
    insertStart(&head,3);
    insertStart(&head,2);
    insertStart(&head,1);

	// Print list
	printList(head);

	deleteStart(&head);
	deleteStart(&head);
	// Print list
	printList(head);

	remove_if(&head, 4);
	printList(head);
	remove_if(&head, 5);
	printList(head);

	return 0;
}
