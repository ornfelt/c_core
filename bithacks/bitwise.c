// FROM: https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
// C Program to demonstrate use of bitwise operators

#include <stdio.h>
#include <stdio.h>
 
// Function to return the only odd
// occurring element
int findOdd(int arr[], int n)
{
    int res = 0, i;
    for (i = 0; i < n; i++)
	{
		printf("\nres: %d", res);
        res ^= arr[i];
	}
    return res;
}

// Main
int main()
{
    // a = 5(00000101), b = 9(00001001)
    unsigned char a = 5, b = 9;
 
	// The & (bitwise AND) in C or C++ takes two numbers as operands and does AND on every
	// bit of two numbers. The result of AND is 1 only if both bits are 1.  
    // The result is 00000001
    printf("a = %d, b = %d\n", a, b);
    printf("a&b = %d\n", a & b);
 

	// The | (bitwise OR) in C or C++ takes two numbers as operands and does OR on every
	// bit of two numbers. The result of OR is 1 if any of the two bits is 1. 
    // The result is 00001101
    printf("a|b = %d\n", a | b);


	// The ^ (bitwise XOR) in C or C++ takes two numbers as operands and does XOR on every
	// bit of two numbers. The result of XOR is 1 if the two bits are different. 
    // The result is 00001100
    printf("a^b = %d\n", a ^ b);
 

	// The ~ (bitwise NOT) in C or C++ takes one number and inverts all bits of it. 
    // The result is 11111010
    printf("~a = %d\n", a = ~a);

 
	//The << (left shift) in C or C++ takes two numbers, left shifts the bits of the first
	//operand, the second operand decides the number of places to shift. 
    // The result is 00010010
    printf("b<<1 = %d\n", b << 1);
 
	// The >> (right shift) in C or C++ takes two numbers, right shifts the bits of the
	// first operand, the second operand decides the number of places to shift. 
    // The result is 00000100
    printf("b>>1 = %d\n", b >> 1);
	

	// 1. FIND ODD
	printf("\narr[] = { 12, 12, 14, 90, 14, 14, 14 } Find odd element:");
	int arr[] = { 12, 12, 14, 90, 14, 14, 14 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("\nThe odd occurring element is %d ",
           findOdd(arr, n));


	// 2. The left-shift and right-shift operators are equivalent to multiplication and
	// division by 2 respectively. It only works if numbers are positive.
    int x = 19;
    printf("\n\nx << 1 = %d\n", x << 1);
    printf("x >> 1 = %d\n\n", x >> 1);


	// 3. The & operator can be used to quickly check if a number is odd or even. The
	// value of expression (x & 1) would be non-zero only if x is odd, otherwise the value
	// would be zero. 
    x = 19;
    (x & 1) ? printf("Odd") : printf("Even");


	/**
	Note:
	The ~ operator should be used carefully. The result of ~ operator on a small number
	can be a big number if the result is stored in an unsigned variable. And the result
	may be a negative number if the result is stored in a signed variable (assuming that
	the negative numbers are stored in 2’s complement form where the leftmost bit is the
	sign bit) 
	*/
    unsigned int unsigned_x = 1;
    printf("\n\nSigned Result %d \n", ~unsigned_x);
    printf("Unsigned Result %ud \n", ~unsigned_x);


/**
	Interesting facts about bitwise operators:

	The left shift and right shift operators should not be used for negative numbers. If
	the second operand(which decides the number of shifts) is a negative number, it
	results in undefined behaviour in C. For example results of both 1 <<- 1 and 1 >> -1
	is undefined. Also, if the number is shifted more than the size of the integer, the
	behaviour is undefined. For example, 1 << 33 is undefined if integers are stored using
	32 bits. Another thing is, NO shift operation is performed if
	additive-expression(operand that decides no of shifts) is 0. See this for more
	details. 

	Note: In C++, this behavior is well-defined. Interestingly!! The bitwise OR of two
	numbers is just the sum of those two numbers if there is no carry involved, otherwise
	you just add their bitwise AND. Let’s say, we have a=5(101) and b=2(010), since there
	is no carry involved, their sum is just a|b. Now, if we change ‘a’ to 6 which is 110
	in binary, their sum would change to a|b + a&b since there is a carry involved. 

	The bitwise XOR operator is the most useful operator from a technical interview
	perspective. It is used in many problems. A simple example could be “Given a set of
	numbers where all elements occur an even number of times except one number, find the
	odd occurring number” This problem can be efficiently solved by just doing XOR to all
	numbers. 
*/

    return 0;
}
