#include <stdio.h>

// Usage of pointers
// From: https://beginnersbook.com/2014/01/c-passing-pointers-to-functions/

// This technique is known as call by reference in C.
void salaryhike(int *var, int b)
{
    *var = *var+b;
}

// This is one of the most popular example that shows how to swap numbers using call by reference.
void swapnum(int *num1, int *num2)
{
   int tempnum;

   tempnum = *num1;
   *num1 = *num2;
   *num2 = tempnum;
}

int main()
{
    int salary=0, bonus=0;
    printf("Enter the employee current salary:"); 
    scanf("%d", &salary);
    printf("\nEnter bonus:");
    scanf("%d", &bonus);
    salaryhike(&salary, bonus);
    printf("\nFinal salary: %d", salary);
	
	// Example 2:
	
	int v1 = 11, v2 = 77;
	printf("\n\nBefore swapping:");
	printf("\nValue of v1 is: %d", v1);
	printf("\nValue of v2 is: %d", v2);

	/*calling swap function*/
	swapnum( &v1, &v2 );

	printf("\nAfter swapping:");
	printf("\nValue of v1 is: %d", v1);
	printf("\nValue of v2 is: %d\n\n", v2);
	
	/**
	A pointer-to-a-pointer is used when a reference to a pointer is required. For example, when you wish to modify the value (address pointed to) of a pointer variable declared in a calling function's scope inside a called function.

	If you pass a single pointer in as an argument, you will be modifying local copies of the pointer, not the original pointer in the calling scope. With a pointer to a pointer, you modify the latter.
	*/
	
	// Pointer to pointer example:
	
	const int num = 10;
	const int *ptr1;
	const int **ptr2;

	// Take the address of var 
	ptr1 = &num;

	// Take the address of ptr1 using address of operator &
	ptr2 = &ptr1;

	// Print the values
	printf("Value of num = %d\n", num );
	printf("Value available at *ptr1 = %d\n", *ptr1 );
	printf("Value available at **ptr2 = %d\n", **ptr2);
	
	
	// Pointer to pointer example 2:
	
	// defines c to be a pointer to the (read-only) string "hello", and thus contains the of first char "h". c must itself be stored somewhere: in the example above at location 58. Of course we can not only point to characters, but also to other pointers.
	const char *c = "hello";
	printf("\nValue of *c = %c\n", *(c));
	printf("Value of *(c+1) = %c\n", *(c+1));
	printf("Value of *(c+2) = %c\n", *(c+2));
	printf("Value of *(c+3) = %c\n", *(c+3));
	printf("Value of *(c+4) = %c\n", *(c+4));
	printf("Value of c[0] = %c\n", c[0]);
	printf("Value of c[1] = %c\n", c[1]);
	
	// Now cp points to c, that is, it contains the address of c
	const char **cp = &c;
	// Now cpp stores the address of cp
	const char ***cpp = &cp;
	printf("Value available at **cp = %c\n", **cp);
	printf("Value available at ***cpp = %c\n", ***cpp);
	
    return 0;
}
