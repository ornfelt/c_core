// FROM: https://www.geeksforgeeks.org/add-two-numbers-without-using-arithmetic-operators/

/**
	Add two numbers without using arithmetic operators.

	Write a function Add() that returns sum of two integers. The function should not use
	any of the arithmetic operators (+, ++, –, -, .. etc). Sum of two bits can be obtained
	by performing XOR (^) of the two bits. Carry bit can be obtained by performing AND (&)
	of two bits. 

	If x and y don’t have set bits at same position(s), then bitwise XOR (^) of x and y
	gives the sum of x and y. To incorporate common set bits also, bitwise AND (&) is
	used. Bitwise AND of x and y gives all carry bits. We calculate (x & y) << 1 and add
	it to x ^ y to get the required result. 
 */

// C Program to add two numbers without using arithmetic operator
#include<stdio.h>

int Add(int x, int y)
{
	// Iterate till there is no carry
	while (y != 0)
	{
		// carry now contains common
		//set bits of x and y
		unsigned carry = x & y;

		// Sum of bits of x and y where at
		//least one of the bits is not set
		x = x ^ y;

		// Carry is shifted by one so that adding
		// it to x gives the required sum
		y = carry << 1;
	}
	return x;
}

// Recursive version:
int add_recursive(int x, int y)
{
    if (y == 0)
        return x;
    else
        return add_recursive( x ^ y, (unsigned)(x & y) << 1);
}

int main()
{
	printf("%d", Add(15, 32));

	printf("\nRecursive: %d", add_recursive(15, 32));
	return 0;
}
