#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void add_member(char *name, char *race, int age);
bool remove_member(char *name);
bool remove_member_v2(char *name);

typedef struct member_data MEMBER_DATA;

MEMBER_DATA *head_member = NULL;

struct member_data
{
	char *name;
	char *race;
	int age;
	MEMBER_DATA *next;
};

int main (void)
{
	char name[20] = {};
	char race[20] = {};
	char cmd[20] = {};
	int age = 0;
	MEMBER_DATA *p = NULL, *p_next = NULL;
	
	for (;;) {
		printf("To add a member to the Fellowship of the Ring, type 'add'.\n");
		printf("To remove a member from the Fellowship of the Ring, type 'remove'.\n");
		printf("To see a list of the members, type 'list'.\n");
		printf("If you are done creating the Fellowship, type 'done'.\n");
		scanf("%s", cmd);

		if (!strcmp(cmd, "done")){
			printf("The Fellowship of the Ring is complete! The adventure can begin...\n");
			break;
		} else if (!strcmp(cmd, "list") || !strcmp(cmd, "ls")) {
			int count = 0;
			if (!head_member){
				printf("Empty...\n\n");
			} else{
				printf("\n");
				for (p = head_member; p; p = p->next){
					printf("[%d] %s, %s, %d\n", ++count, p->name, p->race, p->age);
				}
				printf("\n");
			}
		} else if (!strcmp(cmd, "remove")){
			printf("Who is leaving the Fellowship?");
			scanf("%s", name);
			//if (remove_member(name)){
			if (remove_member_v2(name)){
				printf("\n%s has left the Fellowship.\n\n", name);
			}
		} else if (!strcmp(cmd, "add")){
			printf("Who is joining the Fellowship?");
			scanf("%s", name);
			printf("What race is %s?", name);
			scanf("%s", race);
			printf("How old is %s?", name);
			scanf("%d", &age);

			printf("\n%s (race %s, age %d) has joined the Fellowship!\n\n", name, race, age);
			add_member(name, race , age);
		} else {
			printf("\n%s is not a valid command.\n\n", cmd);
			continue;
		}
	}

	// Remove members when exiting
	printf("\nRemoving all members from memory...");
    while (head_member != NULL) {
        remove_member_v2(head_member->name);
    }
	
	return 0;
}

MEMBER_DATA *new_node()
{
	MEMBER_DATA *node = NULL, node_zero = {0};

	if ((node = (MEMBER_DATA *)malloc(sizeof(MEMBER_DATA))) == NULL){
		// Error
		return NULL;
	}
	*node = node_zero;
	return node;
}

void add_member(char *name, char *race, int age)
{
	MEMBER_DATA *newNode = NULL, *p = NULL;

	if ((newNode = new_node()) == NULL)
		return;

	// strdup: returns a pointer to a null-terminated byte string, which is a duplicate of the string pointed to by str1.
	// The returned pointer must be passed to free to avoid a memory leak.
	// If an error occurs, a null pointer is returned.
	newNode->name = strdup(name);
	newNode->race = strdup(race);
	newNode->age = age;

	if (head_member == NULL){
		head_member = newNode;
	} else {
		// Add node to the end of list
		for (p = head_member; p; p = p->next){
			if (p->next == NULL) {
				p->next = newNode;
				break;
			}
		}
	}
}

bool remove_member(char *name)
{
	MEMBER_DATA *p = NULL, *temp = NULL;

	printf("\nRemoving %s\n", name);
	if (head_member == NULL){
		printf("\nThere are no members to remove.\n\n");
		return false;
	}

	if(!strcmp(head_member->name, name)) {
		temp = head_member;
		head_member = head_member->next;
		free(temp->name);
		free(temp->race);
		free(temp);
		temp = NULL;
		return true;
	}

	for(p = head_member; p; p = p->next){
		//if (p->next){
		if (p->next != NULL){
			if(!strcmp(p->next->name, name)) {
				temp = p->next;
				p->next = p->next->next;
				free(temp->name);
				free(temp->race);
				free(temp);
				temp = NULL;
				return true;
			}
		}
	}

	printf("\n There is no member named %s.\n\n", name);
	return false;
}

// Uses double pointers (MEMBER_DATA **curr). Treats all nodes uniformly,
// including the head node, by using a double pointer that can point to
// head_member or the next pointer of any node in the list. Simplifies the
// logic by removing the special case handling for the head node.
bool remove_member_v2(char *name)
{
    printf("\nRemoving %s\n", name);
	
    if (head_member == NULL) {
        printf("\nThere are no members to remove.\n\n");
        return false;
    }

    for (MEMBER_DATA **curr = &head_member; *curr; ) {
        MEMBER_DATA *entry = *curr;
        if (!strcmp(entry->name, name)) {
            *curr = entry->next;
            free(entry->name);
            free(entry->race);
            free(entry);
			printf("%s has been removed from the Fellowship.\n", name);
            return true;
        }
        curr = &entry->next; // Advance to next node
    }

    printf("There is no member named %s in the Fellowship.\n", name);
    return false;
}
