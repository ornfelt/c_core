// From: https://www.geeksforgeeks.org/find-the-missing-number/

/**
Given an array arr[] of size N-1 with integers in the range of [1, N], the task is to find
the missing number from the first N integers. Note: There are no duplicates in the list.

Examples: 
    Input: arr[] = {1, 2, 4, 6, 3, 7, 8}, N = 8
    Output: 5
    Explanation: The missing number between 1 to 8 is 5

    Input: arr[] = {1, 2, 3, 5}, N = 5
    Output: 4
    Explanation: The missing number between 1 to 5 is 4
*/


// Approach 3 (Using binary operations): This method uses the technique of XOR to solve the problem.
/**
	Follow the steps mentioned below to implement the idea:

		Create two variables a = 0 and b = 0
		Run a loop from i = 1 to N:
			For every index, update a as a = a ^ i
		Now traverse the array from i = start to end.
			For every index, update b as b = b ^ arr[i].
		The missing number is a ^ b.

	Below is the implementation of the above approach:
 */

#include <bits/stdc++.h>
using namespace std;
 
// Function to get the missing number
int getMissingNo(int a[], int n)
{
    // For xor of all the elements in array
    int x1 = a[0];
 
    // For xor of all the elements from 1 to n+1
    int x2 = 1;
 
    for (int i = 1; i < n; i++)
        x1 = x1 ^ a[i];
 
    for (int i = 2; i <= n + 1; i++)
        x2 = x2 ^ i;
 
    return (x1 ^ x2);
}
 
// Driver Code
int main()
{
    int arr[] = { 1, 2, 3, 5 };
    int N = sizeof(arr) / sizeof(arr[0]);
   
    // Function call
    int miss = getMissingNo(arr, N);
    cout << miss;
    return 0;
}
