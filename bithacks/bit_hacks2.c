#include <stdio.h>

/**
	In competitive programming or in general, some problems seem difficult but can be
	solved very easily with little concepts of bit magic.
	https://www.geeksforgeeks.org/bit-tricks-competitive-programming/
*/

// 7) Count set bits in integer 
int countSetBits(int x)
{
    int count = 0;
    while (x)
    {
        x &= (x-1);
        count++;
    }
    return count;
}

// 8) Find log base 2 of 32 bit integer
int customlog2(int x)
{
    int res = 0;
    while (x >>= 1)
        res++;
    return res;
}

// 9) Checking if given 32 bit integer is power of 2 
int isPowerof2(int x)
{
    return (x && !(x & x-1));
}

// 10) Find the last set bit
int lastSetBit(int n){
    return customlog2(n & -n)+1;
}

int main() {

	// 1) Clear all bits from LSB to ith bit 
	int mask = 1, x = 0, i = 1;
	printf("mask: %d\n", mask);
	printf("x: %d\n", x);
	printf("i: %d\n", i);
	
	mask = ~((1 << i+1 ) - 1);
	x &= mask;
	
	printf("mask: %d\n", mask);
	printf("x: %d\n", x);
	printf("i: %d\n", i);
	
	/**
		Logic: To clear all bits from LSB to i-th bit, we have to AND x with mask having
		LSB to i-th bit 0. To obtain such mask, first left shift 1 i times. Now if we
		minus 1 from that, all the bits from 0 to i-1 become 1 and remaining bits become
		0. Now we can simply take the complement of mask to get all first i bits to 0 and
		remaining to 1. 
		
		Example- 
		x = 29 (00011101) and we want to clear LSB to 3rd bit, total 4 bits 
		mask -> 1 << 4 -> 16(00010000) 
		mask -> 16 – 1 -> 15(00001111) 
		mask -> ~mask -> 11110000 
		x & mask -> 16 (00010000)
	*/
	
	// 2) Clearing all bits from MSB to i-th bit
	mask = (1 << i) - 1;
	x &= mask;
	
	// 3) Divide by 2
	x = 50;
	printf("\nDivide by 2:\nx: %d\n", x);
	x >>= 1;
	printf("x: %d\n", x);
	
	// 4) Multiplying by 2 
	printf("\nMultiplying by 2:\nx: %d\n", x);
	x <<= 1;
	printf("x: %d\n", x);
	
	// 5) Upper case English alphabet to lower case 
	char ch = 'A';
	printf("\nUpper case English alphabet to lower case:\nch: %c\n", ch);
	ch |= ' ';
	printf("ch: %c\n", ch);

	// 6) Lower case English alphabet to upper case 
	printf("\nLower case English alphabet to upper case:\nch: %c\n", ch);
	ch &= '_' ;
	printf("ch: %c\n", ch);
	
	// 7) Count set bits in integer
	x = 5;
	printf("\nCountsetbits(x), x = 5: %d\n", countSetBits(x));
	
	// Logic: This is Brian Kernighan’s algorithm.
	
	// 8) Find log base 2 of 32 bit integer
	x = 10;
	printf("\ncustomlog2(x), x = 10: %d\n", customlog2(x));
	// Logic: We right shift x repeatedly until it becomes 0, meanwhile we keep count on
	// the shift operation. This count value is the log2(x).
	
	// 9) Checking if given 32 bit integer is power of 2
	x = 8;
	printf("\nisPowerof2(x), x = 8: %d\n", isPowerof2(x));
	printf("isPowerof2(x), x = 9: %d\n", isPowerof2(9));
	
	/**
		Logic: All the power of 2 have only single bit set e.g. 16 (00010000). If we minus
		1 from this, all the bits from LSB to set bit get toggled, i.e., 16-1 = 15
		(00001111). Now if we AND x with (x-1) and the result is 0 then we can say that x
		is power of 2 otherwise not. We have to take extra care when x = 0.
		Example 
		x = 16(00010000) 
		x – 1 = 15(00001111) 
		x & (x-1) = 0 
		so 16 is power of 2
	*/
	
	// 10) Find the last set bit
	x = 9;
	printf("\nlastSetBit(x), x = 9: %d\n", lastSetBit(x));
	// The logarithmic value of AND of x and -x to the base 2 gives the index of the last
	// set bit(for 0-based indexing)
	
	printf("\nEnd");
}
