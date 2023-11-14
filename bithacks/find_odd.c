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

int main()
{
    // a = 5(00000101), b = 9(00001001)
    unsigned char a = 5, b = 9;
 
    // The result is 00000001
    printf("a = %d, b = %d\n", a, b);
    printf("a&b = %d\n", a & b);
 
    // The result is 00001101
    printf("a|b = %d\n", a | b);
 
    // The result is 00001100
    printf("a^b = %d\n", a ^ b);
 
    // The result is 11111010
    printf("~a = %d\n", a = ~a);
 
    // The result is 00010010
    printf("b<<1 = %d\n", b << 1);
 
    // The result is 00000100
    printf("b>>1 = %d\n", b >> 1);
	
	// FIND ODD
	int arr[] = { 12, 12, 14, 90, 14, 14, 14 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("\nThe odd occurring element is %d ",
           findOdd(arr, n));
 
    return 0;
   
}