// FROM: https://www.geeksforgeeks.org/swap-two-numbers-without-using-temporary-variable/

#include <stdio.h>

// Method 1 (Using Arithmetic Operators)
void swap_arithmetic(int x, int y)
{
	printf("\nSwap with artihmetic:\n");
 
    // Code to swap 'x' and 'y'
    x = x + y; // x now becomes 15
    y = x - y; // y becomes 10
    x = x - y; // x becomes 5
 
    printf("After Swapping: x = %d, y = %d\n", x, y);
}


// Method 2 (Using Bitwise XOR) 
/**
	The bitwise XOR operator can be used to swap two variables. The XOR of two numbers x
	and y returns a number that has all the bits as 1 wherever bits of x and y differ. For
	example, XOR of 10 (In Binary 1010) and 5 (In Binary 0101) is 1111, and XOR of 7
	(0111) and 5 (0101) is (0010). 
 */

// C code to swap using XOR
void swap_xor_1 (int x, int y)
{
	printf("\nSwap with xor_1:\n");
 
    // Code to swap 'x' (1010) and 'y' (0101)
    x = x ^ y; // x now becomes 15 (1111)
    y = x ^ y; // y becomes 10 (1010)
    x = x ^ y; // x becomes 5 (0101)
 
    printf("After Swapping: x = %d, y = %d\n", x, y);

	// Method 4 (One Line Expression) 
    x = (x * y) / (y = x);
    printf("After Swapping: x = %d, y = %d\n", x, y);
}

/**
	Problems with the above methods...
	1) The multiplication and division-based approach doesn’t work if one of the numbers
	is 0 as the product becomes 0 irrespective of the other number.
	2) Both Arithmetic solutions may cause an arithmetic overflow. If x and y are too
	large, addition and multiplication may go out of the integer range.
	3) When we use pointers to variable and make a function swap, all the above methods
	fail when both pointers point to the same variable. Let’s take a look at what will
	happen in this case if both are pointing to the same variable.

	// Bitwise XOR based method 
	x = x ^ x; // x becomes 0 
	x = x ^ x; // x remains 0 
	x = x ^ x; // x remains 0
	// Arithmetic based method 
	x = x + x; // x becomes 2x 
	x = x – x; // x becomes 0 
	x = x – x; // x remains 0

	Let us see the following program:
 */

void swap(int* xp, int* yp)
{
	*xp = *xp ^ *yp;
	*yp = *xp ^ *yp;
	*xp = *xp ^ *yp;
}

int main()
{
	swap_arithmetic(10, 5);
	swap_xor_1(10, 5);

	// This is better:
	int x = 10;
	int y = 0;
	swap(&x, &y);
	printf("\nx = 10, y = 0, After swap(&x, &x): x = %d", x);

	x = 10;
	y = 5;
	printf("\nx = 10, y = 5, After swap(&x, &y): x = %d", x);

	return 0;
}
