/** From: https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
* The bitwise XOR operator is the most useful operator from a technical interview perspective. It is used in many problems. A *simple example could be “Given a set of numbers where all elements occur even a number of times except one number, find the odd *occurring number” This problem can be efficiently solved by just doing XOR of all numbers. 
*/ 

#include <iostream>
using namespace std;
 
// Function to return the only odd
// occurring element
int findOdd(int arr[], int n)
{
    int res = 0, i;
    for (i = 0; i < n; i++){
        res ^= arr[i];
		printf("res: %d, and arr[i]: %d\n", res, arr[i]);

	}
		/* if() */
    return res;
}
 
// Driver Method
int main(void)
{
    int arr[] = { 12, 12, 14, 90, 14, 14, 14 };
    /* int arr[] = {4, 4, 2 }; */

    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "The odd occurring element is  "<< findOdd(arr, n);
    return 0;
}


