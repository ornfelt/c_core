// FROM: https://stackoverflow.com/questions/5580761/why-use-double-indirection-or-why-use-pointers-to-pointers
// AND https://wordaligned.org/articles/two-star-programming


#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Imagine you have a structure for nodes in a linked list, which probably is

typedef struct node
{
    struct node * next;
	struct node * prev;
    struct node * head;
	struct node * curr;
	// ....
} node;

bool rm(node *n)
{
	return true;
}

// Now you want to implement a remove_if function, which accepts a removal criterion rm as one of the arguments and traverses the linked list: if an entry satisfies the criterion (something like rm(entry)==true), its node will be removed from the list. In the end, remove_if returns the head (which may be different from the original head) of the linked list. You may write...

void remove_if()
{
	node *head;
	
	for (node * prev = NULL, * curr = head; curr != NULL; )
	{
		node * const next = curr->next;
		if (rm(curr))
		{
			if (prev)  // the node to be removed is not the head
				prev->next = next;
			else       // remove the head
				head = next;
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

// as your for loop. The message is, without double pointers, you have to maintain a prev variable to re-organize the pointers, and handle the two different cases.

// But with double pointers, you can actually write:

void remove_if_better()
{
	node **head;
	// now head is a double pointer
	for (node** curr = head; *curr; )
	{
		node * entry = *curr;
		if (rm(entry))
		{
			*curr = entry->next;
			free(entry);
		}
		else
			curr = &entry->next;
	}
}

// You don't need a prev now because you can directly modify what prev->next pointed to.

// To make things clearer, let's follow the code a little bit. During the removal:
// if entry == *head: it will be *head (==*curr) = *head->next -- head now points to the pointer of the new heading node. You do this by directly changing head's content to a new pointer.

// if entry != *head: similarly, *curr is what prev->next pointed to, and now points to entry->next.

int main()
{
	printf("Helloooo");
    return 0;
}

