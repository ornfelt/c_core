// FROM: https://www.youtube.com/watch?v=2Ti5yvumFTU
// Not complete yet

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct {
	char name[MAX_NAME];
	int age;
	// And more stuff...
}person;

// Use pointer for the hash table since we can save space (we just need space for some addresses)
// Also use pointers since we can then easily tell when a spot is empty by setting the pointer to NULL
person * hash_table[TABLE_SIZE];

// This function can be used to get an "id" based on a name. It will be based oin the table_size (i.e. will only produce 10 different id's).
// This function is not perfect since the name "Bill" will produce the same id for two different "Bill"s...
unsigned int hash (char* name){
	int length = strnlen(name, MAX_NAME);
	unsigned int hash_value = 0;

	for(int i = 0; i <length ; i++){
		hash_value += name[i];
		/* hash_value = hash_value * name[i]; */
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
	}
	return hash_value;
}

// Set empty hash table
bool init_hash_table(){
	for(int i = 0; i < TABLE_SIZE; i++){
		hash_table[i] = NULL;
	}
	// Table is empty
}

// Print hash table
void print_table(){
	printf("Start\n");
	for(int i = 0; i < TABLE_SIZE; i++){
		if(hash_table[i] == NULL){
			printf("\t%i}t---", i);
		}else{
			printf("\t%i\t%s\n", i, hash_table[i]->name);
		}
	}
	printf("End\n");
}

// Insert to hash table
bool hash_table_insert(person *p){
	if (p == NULL) return false;
	int index = hash(p->name);
	// If collision
	if (hash_table[index] != NULL){
		return false;
	}
	hash_table[index] = p;
	return true;
}

// Returns pointer to a person if the person is in the table
person *hash_table_lookup(char *name){
	int index = hash(name);
	// Check if index is null and then check if the name match with stringcompare
	if(hash_table[index] != NULL && strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0){
		return hash_table[index];
	}else{
		return NULL;
	}
}

// Remove person from hash table
person *hash_table_delete(char *name){
	int index = hash(name);
	if(hash_table[index] != NULL && strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0){
		person *tmp = hash_table[index];
		hash_table[index] == NULL;
		return tmp;
	}else{
		return NULL;
	}
}

int main() {
	init_hash_table();
	print_table();

	person jacob = {.name = "Jacob", .age=256};
	person kate = {.name = "Kate", .age=27};
	person mpho = {.name = "Mpho", .age=14};

	hash_table_insert(&jacob);
	hash_table_insert(&kate);
	hash_table_insert(&mpho);
	print_table();

	person *tmp = hash_table_lookup("Mpho");
	if(tmp == NULL){
		printf("Not found");
	}else{
		printf("Found %s.\n", tmp->name);
	}

	tmp = hash_table_lookup("George");
	if(tmp == NULL){
		printf("Not found");
	}else{
		printf("Found %s.\n", tmp->name);
	}

	hash_table_delete("Mpho");
	tmp = hash_table_lookup("Mpho");
	if(tmp == NULL){
		printf("Not found");
	}else{
		printf("Found %s.\n", tmp->name);
	}

	print_table();

	/* printf("Jacob -> %u\n", hash("Jacob")); */
	/* printf("Natalie -> %u\n", hash("Natalie")); */
	/* printf("Sara -> %u\n", hash("Sara")); */
}

