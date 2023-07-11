#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static void test_pointers();
static void test_pointers2();
static int isManualInput;

int main (int argc, char* argv[]) {

    if(argc==1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
	if (argc >= 2)
		isManualInput = 1;

   int  var = 20;   /* actual variable declaration */
   int  *ip;        /* pointer variable declaration */

   ip = &var;  /* store address of var in pointer variable*/

   printf("Address of var variable: %x\n", &var  );

   /* address stored in pointer variable */
   printf("Address stored in ip variable: %x\n", ip );

   /* access the value using the pointer */
   printf("Value of *ip variable: %d\n", *ip );
   
   printf("\n");
   test_pointers();
   printf("\n");
   test_pointers2();

   return 0;
}

/**
	>>>
	Address of var variable: bffd8b3c
	Address stored in ip variable: bffd8b3c
	Value of *ip variable: 20
*/

char* charToLower(char* p) {
  for(; *p; p++) *p=tolower(*p);
  return p;
}

void test_pointers()
{
    float *p, sum = 0;
    int i, n;

    printf("Enter the number of students: ");
	// Use scanf for manual input
	if (isManualInput)
		scanf("%d", &n);
	else
		n = 2;

    // allocate memory to store n variables of type float
    p = (float*)malloc(n*sizeof(float));

    // if dynamic allocation failed exit the program
    if(p==NULL)
    {
        printf("Memory allocation failed");
        exit(1); // exit the program
    }

    // ask the student to enter marks
    for(i = 0; i < n; i++)
    {
        printf("Enter marks for %d student: ", i+1);
		// Use scanf for manual input
		if (isManualInput)
			scanf("%f", p+i);
		else
			*(p+i) = i + 1;
    }

    // calculate sum
    for(i = 0; i < n; i++)
    {
        sum += *(p+i);
    }

    printf("\nAverage marks = %.2f\n", sum/n);
	
	// -------------------------------------------
	char word[] = "HeLLo";
	
	printf("\nword: %s", word);
	//for ( ; *p; ++p) *p = tolower(*p);
	charToLower(word);
	printf("\nword2: %s\n", word);
	
	// Change string to lowercase with char pointers (C++)
	/**
	char word[] = "HeLlo";
	for (auto it = word; *it != '\0'; ++it) {
		*it = tolower(static_cast<unsigned char>(*it));
	}
	*/
	
    // signal to operating system program ran fine
    //return 0;
}

// Another function, from: https://www.youtube.com/watch?v=mw1qsMieK5c
void test_pointers2 ()
{
	int somenumbers[5];
	int *ptr = somenumbers; // same as &somenumbers[0]
	int v = 2;
	
	// Pointer is already pointing to the beginning of the array so we don't need to init anything (i)
	for (; ptr < &somenumbers[5]; ptr++) {
		// Fill array with 2, 4, 8, 16, 32
		// ptr++ will make sure that the pointer moves to the next element in the array
		*ptr = v;
		v *= 2;
	}
	
	// Do a regular loop to verify that the numbers are in the array
	for (int i = 0; i<5; i++) {
		printf("%d\n", somenumbers[i]);
	}
}

/** 
https://beginnersbook.com/2015/02/simple-c-programs/

https://overiq.com/c-programming-101/string-basics-in-c/

Use malloc() if you are going to set everything that you use in the allocated space. Use calloc() if you're going to leave parts of the data uninitialized - and it would be beneficial to have the unset parts zeroed.

https://www.programiz.com/c-programming/c-dynamic-memory-allocation
https://beginnersbook.com/2019/02/c-program-to-find-the-largest-of-three-numbers-using-pointers/
https://beginnersbook.com/2019/02/c-program-to-print-string-using-pointer/
https://overiq.com/c-programming-101/string-basics-in-c/
https://overiq.com/c-programming-101/the-malloc-function-in-c/
https://www.programiz.com/c-programming/c-dynamic-memory-allocation
https://www.programiz.com/cpp-programming/object-class
https://www.geeksforgeeks.org/array-strings-c-3-different-ways-create/
https://stackoverflow.com/questions/7527356/return-string-array-in-c-function
https://www.delftstack.com/howto/cpp/return-string-from-function-cpp/
https://stackoverflow.com/questions/2308751/what-is-a-memory-heap


Bash:https://www.youtube.com/watch?v=Gl4DKyicKKg
https://www.zalando.se/lloyd-miller-snoerskor-schwarzanthrazit-ll112a0ak-q12.html

A few reasons one uses pointers to pointers:
    - The name of an array usually yields the address of its first element. So if the array contains elements of type t, a reference to the array has type t *. Now consider an array of arrays of type t: naturally a reference to this 2D array will have type (t *)* = t **, and is hence a pointer to a pointer.
    - Even though an array of strings sounds one-dimensional, it is in fact two-dimensional, since strings are character arrays. Hence: char **.
    - A function f will need to accept an argument of type t ** if it is to alter a variable of type t *.
https://stackoverflow.com/questions/897366/how-do-pointer-to-pointers-work-in-c-and-when-might-you-use-them

https://stackoverflow.com/questions/5580761/why-use-double-indirection-or-why-use-pointers-to-pointers

https://beginnersbook.com/2014/01/c-passing-pointers-to-functions/

gcc .\pointer.c; .\a.exe

*/
