// FROM: https://www.youtube.com/watch?v=VOpjAHCee7c

#include <stdlib.h>
#include <stdio.h>

struct node {
	int value;
	// Next pointer (points to next node in list)
	struct node* next;
}

// Create definition so that we don't have to type struct every time
typedef struct node node_t;

void printList (node_t *head){
	node_t *temporary = head;
	
	while (temporary != NULL){
		printf("%d -- ", temporary->value);
		temporary = temporary->next;
	}
	printf("\n");
}

// Function that creates new nodes
// The pointers are used to keep track of all nodes without having variables for each of them, because they are all linked together indirectly through pointer links
node_t *create_new_node(int value){
	node_t *result = malloc(sizeof(node_t));
	result->value = value;
	result->next = NULL;
	return result
}

// Use pointer to pointer to update head inside of function, instead of assigning it 
node_t *insert_at_head(node_t **head, node_t *node_to_insert){
	node_to_insert->next = *head;
	// update inside of function
	*head = node_to_insert;
	return node_to_insert;
}

// Search for node and when it is found, return pointer to that node
node_t *find_node(node_t *head, int value) {
	node_t *tmp = head;
	while (tmp != NULL){
		if (tmp->value == value) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

node_t *insert_after_node(node_t *node_to_insert_after, node_t *new_node){
	// Set new nodes next pointer to point to whatever previous nodes next pointer points to
	new_node->next = node_to_insert_after->next;
	// Then set that nodes next pointer to point to the new node
	node_to_insert_after->next = newnode;
}

int main () {
	/* Statically allocated nodes version: */
	node_t n1, n2, n3;
	node_t = *head;
	
	n1.value = 45;
	n2.value = 8;
	n3.value = 32;
	
	// Link them up
	// Make head point to the address of n3
	head = &n3;
	n3.next = NULL;
	n2.next = &n3;
	n1.next = &n2;
	
	printList(head);
	
	// Add new node and insert in middle
	node_t n4;
	n4.value = 13;
	n4.next = &n3;
	n2.next = &n4;
	
	// Remove first node by moving head pointer down a link
	head = head->next;
	
	
	
	/* Dynamically allocate nodes on the heap by using malloc: */
	// Use function to create nodes
	node_t *head = NULL;
	node_t *tmp;
	
	for (int i = 0; i < 25; i++){
		tmp = create_node_node(i);
		insert_at_head(&head, tmp);
	}
	
	tmp = find_node(head, 13);
	printf("Found node with value %d\n", tmp->value);
	
	insert_after_node(tmp, create_new_node(75));
	printList(head);
	
	return 0
}
