#include<stdlib.h>
#include<stdio.h>

// https://prepinsta.com/c-program/singly-linked-list/
// https://wordaligned.org/articles/two-star-programming

struct Node{
    int data;
    struct Node *next;
};

void deleteStart(struct Node** head){
    struct Node* temp = *head;
  
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

void insertStart(struct Node** head, int data){
    
    // dynamically create memory for this newNode
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    
    // assign data value
    newNode->data = data;
    // change the next node of this newNode 
    // to current head of Linked List
    newNode->next = *head;

    //re-assign head to this newNode
    *head = newNode;
    printf("Inserted %d\n",newNode->data);
}

void display(struct Node* node){
    printf("\nLinked List: ");
    // as linked list will end when Node is Null
    while(node!=NULL){
        printf("%d ",node->data);
        node = node->next;
    }
    printf("\n");
}

//From: https://wordaligned.org/articles/two-star-programming
void remove_if(struct Node **head, int rm_data)
{
    for (struct Node **curr = head; *curr; )
    {
        struct Node *entry = *curr;
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

int main()
{
    struct Node* head = NULL;

    // Need '&' i.e. address as we need to change head
    insertStart(&head,100);
    insertStart(&head,80);
    insertStart(&head,60);
    insertStart(&head,40);
    insertStart(&head,20);
    
    // No Need for '&' as not changing head in display operation
    display(head);
    
    deleteStart(&head);
    deleteStart(&head);
    display(head);
	
	remove_if(&head, 60);
	display(head);
	remove_if(&head, 100);
	display(head);
    
    return 0; 
}
