// FROM: https://stackoverflow.com/questions/5580761/why-use-double-indirection-or-why-use-pointers-to-pointers

// If you want to change the value of the pointer passed to a function as the function argument, to do this you require pointer to a pointer.

// In simple words, Use ** when you want to preserve (OR retain change in) the Memory-Allocation or Assignment even outside of a function call. (So, Pass such function with double pointer arg.)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

void allocate(int **p)
{
    *p = (int *)malloc(sizeof(int));
}

void cant_change(int * x, int * z){
    x = z;
    printf("\n ----> value of 'a' is: %x inside function, same as 'f', BUT will it be the same outside of this function? lets see\n", x);
}

void change(int ** x, int * z){
    *x = z;
    printf("\n ----> value of 'a' is: %x inside function, same as 'f', BUT will it be the same outside of this function? lets see\n", *x);
}

// 1. char *ch - (called character pointer)
// - ch contains the address of a single character.
// - (*ch) will dereference to the value of the character..
// 2. char **ch -
// 'ch' contains the address of an Array of character pointers. (as in 1)
// '*ch' contains the address of a single character. (Note that it's different from 1, due to difference in declaration).
// (**ch) will dereference to the exact value of the character..
// Adding more pointers expand the dimension of a datatype, from character to string, to array of strings, and so on... You can relate it to a 1d, 2d, 3d matrix..
void testing()
{
    char **p;
    p = (char **)malloc(100);
    p[0] = (char *)"Apple";      // or write *p, points to location of 'A'
    p[1] = (char *)"Banana";     // or write *(p+1), points to location of 'B'

    cout << *p << endl;          //Prints the first pointer location until it finds '\0'
    cout << **p << endl;         //Prints the exact character which is being pointed
    *p++;                        //Increments for the next string
    cout << *p;
}


int main()
{
    int *p = NULL;
    allocate(&p);
    *p = 42;
    printf("%d\n", *p);
    free(p);
	
	// Let’s say you have a pointer. Its value is an address.
	// but now you want to change that address. 
	// if you do that within a function, and you want the result to persist after the function:

	int c = 1;
    int d = 2;
    int e = 3;
    int * a = &c;
    int * b = &d;
    int * f = &e;
    int ** pp = &a;  // pointer to pointer 'a'

    printf("\n a's value: %x \n", a);
    printf("\n b's value: %x \n", b);
    printf("\n f's value: %x \n", f);
    printf("\n can we change a?, lets see \n");
    printf("\n a = b \n");
    a = b;
    printf("\n a's value is now: %x, same as 'b'... it seems we can, but can we do it in a function? lets see... \n", a);
    printf("\n cant_change(a, f); \n");
    cant_change(a, f);
    printf("\n a's value is now: %x, Doh! same as 'b'...  that function tricked us. \n", a);

    printf("\n NOW! lets see if a pointer to a pointer solution can help us... remember that 'pp' point to 'a' \n");
     printf("\n change(pp, f); \n");
    change(pp, f);
    printf("\n a's value is now: %x, YEAH! same as 'f'...  that function ROCKS!!!. \n", a);
    return 0;
}