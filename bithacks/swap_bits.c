// FROM: https://www.geeksforgeeks.org/swap-bits-in-a-given-number/

/**
	Given a number x and two positions (from the right side) in the binary representation
	of x, write a function that swaps n bits at the given two positions and returns the
	result. It is also given that the two sets of bits do not overlap.
 */

// C Program to swap bits in a given number
#include <stdio.h>

int swapBits(unsigned int x, unsigned int p1, unsigned int p2, unsigned int n)
{
    /* xor contains xor of two sets */
    unsigned int xor = ((x >> p1) ^ (x >> p2)) & ((1U << n) - 1);
 
    /* To swap two sets, we need to again XOR the xor with original sets */
    return x ^ ( (xor << p1) | (xor << p2));
}

/* Driver program to test above function*/
int main()
{
    int res = swapBits(28, 0, 3, 2);
    printf("\nResult = %d ", res);
    return 0;
}
