// FROM: https://stackoverflow.com/questions/162941/why-use-pointers
// 

#include <iostream>
using namespace std;

void doSomethingElse(int* i)
{
    cout << *i << endl;
}

void doSomething()
{
    int i = 10;
    doSomethingElse(&i);
}

void test()
{
	char* a = "Hello";
	//char a[] = "Hello";
	
	printf("Second char is: %c", a[1]);
	printf("Second char is: %c", *(a+1));
	
	//  if you don't assign a string value to the char array / pointer when you declare it, you MUST allocate sufficient amount of memory to it before giving it a value. Using malloc, calloc or similar.
	
	char* x;
	/* Allocate 6 bytes of memory for me and point x to the first of them. */
	x = (char*) malloc(6);
	x[0] = 'H';
	x[1] = 'e';
	x[2] = 'l';
	x[3] = 'l';
	x[4] = 'o';
	x[5] = '\0';
	printf("String \"%s\" at address: %d\n", x, x);
	/* Delete the allocation (reservation) of the memory. */
	/* The char pointer x is still pointing to this address in memory though! */
	free(x);
	
	/* Same as malloc but here the allocated space is filled with null characters!*/
	x = (char *) calloc(6, sizeof(x));
	x[0] = 'H';
	x[1] = 'e';
	x[2] = 'l';
	x[3] = 'l';
	x[4] = 'o';
	x[5] = '\0';
	printf("String \"%s\" at address: %d\n", x, x);
	/* And delete the allocation again... */
	free(x);
	
	/* We can set the size at declaration time as well */
	char xx[6];
	xx[0] = 'H';
	xx[1] = 'e';
	xx[2] = 'l';
	xx[3] = 'l';
	xx[4] = 'o';
	xx[5] = '\0';
	printf("String \"%s\" at address: %d\n", xx, xx);
	
	// One reason to use pointers is so that a variable or an object can be modified in a called function.
	// In C++ it is a better practice to use references than pointers. Though references are essentially pointers.
	doSomething();
	
	char hello[] = "hello";
	char *p = hello;

	while (*p)
	{
		*p += 1; // increase the character by one

		p += 1; // move to the next spot
	}
	// prints ifmmp
	printf(hello);
}


// Driver code
int main()
{
	test();

	return 0;
}
