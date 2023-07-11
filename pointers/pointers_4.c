#include <stdio.h>
#include <stdlib.h>

void allocate(int **p)
{
    *p = (int *)malloc(sizeof(int));
}

// Pretty much same as above...
void alloc2(int** p) {
    *p = (int*)malloc(sizeof(int));
    **p = 10;
}

void alloc1(int* p) {
    p = (int*)malloc(sizeof(int));
    *p = 10;
}

int main(){
	// First example:
	int *p = NULL;
    allocate(&p);
    *p = 42;
    printf("p: %d\n", *p); // will print 42
    free(p);
	
	// 2nd example (almost same as first): 
	/**
	Adding to Asha's response, if you use single pointer to the example bellow (e.g. alloc1() ) you will lose the reference to the memory allocated inside the function.
	The reason it occurs like this is that in alloc1 the pointer is passed in by value. So, when it is reassigned to the result of the malloc call inside of alloc1, the change does not pertain to code in a different scope.
	*/
    int *new_p = NULL;
    alloc1(new_p);
    //printf("%d ",*p); //undefined
	
    alloc2(&new_p);
    printf("new_p: %d ",*new_p); // will print 10
    free(new_p);
    return 0;
}