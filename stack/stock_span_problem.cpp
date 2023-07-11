#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/the-stock-span-problem/

/**
	The stock span problem is a financial problem where we have a series of N daily price
	quotes for a stock and we need to calculate the span of the stock’s price for all N
	days. The span Si of the stock’s price on a given day i is defined as the maximum
	number of consecutive days just before the given day, for which the price of the stock
	on the current day is less than its price on the given day. 

	Examples:
    Input: N = 7, price[] = [100 80 60 70 60 75 85]
    Output: 1 1 1 2 1 4 6
	Explanation: Traversing the given input span for 100 will be 1, 80 is smaller than 100
	so the span is 1, 60 is smaller than 80 so the span is 1, 70 is greater than 60 so the
	span is 2 and so on. Hence the output will be 1 1 1 2 1 4 6.

    Input: N = 6, price[] = [10 4 5 90 120 80]
    Output:1 1 2 4 5 1
	Explanation: Traversing the given input span for 10 will be 1, 4 is smaller than 10 so
	the span will be 1, 5 is greater than 4 so the span will be 2 and so on. Hence, the
	output will be 1 1 2 4 5 1.

	Naive Approach: To solve the problem follow the below idea:
	Traverse the input price array. For every element being visited, traverse elements on
	the left of it and increment the span value of it while elements on the left side are
	smaller

	Time Complexity: O(N2)
	Auxiliary Space: O(N)
 */

// Fills array S[] with span values
void calculateSpan(int price[], int n, int S[])
{
	// Span value of first day is always 1
	S[0] = 1;

	// Calculate span value of remaining days
	// by linearly checking previous days
	for (int i = 1; i < n; i++) {
		S[i] = 1; // Initialize span value

		// Traverse left while the next element
		// on left is smaller than price[i]
		for (int j = i - 1;
			(j >= 0) && (price[i] >= price[j]); j--)
			S[i]++;
	}
}

// A utility function to print elements of array
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

// Driver code
int main()
{
	int price[] = { 10, 4, 5, 90, 120, 80 };
	int n = sizeof(price) / sizeof(price[0]);
	int S[n];

	// Fill the span values in array S[]
	calculateSpan(price, n, S);

	// print the calculated span values
	printArray(S, n);

	return 0;
}
