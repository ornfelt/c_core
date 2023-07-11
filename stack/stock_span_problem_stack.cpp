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

	We see that S[i] on the day i can be easily computed if we know the closest day
	preceding i, such that the price is greater than on that day than the price on the day
	i. If such a day exists, let’s call it h(i), otherwise, we define h(i) = -1
	The span is now computed as S[i] = i – h(i). See the following diagram

	To implement this logic, we use a stack as an abstract data type to store the days i,
	h(i), h(h(i)), and so on. When we go from day i-1 to i, we pop the days when the price
	of the stock was less than or equal to price[i] and then push the value of day i back
	into the stack.

	Time Complexity: O(N). It seems more than O(N) at first look. If we take a closer
	look, we can observe that every element of the array is added and removed from the
	stack at most once.

	Auxiliary Space: O(N) in the worst case when all elements are sorted in decreasing order.
 */

// A stack based efficient method to calculate
// stock span values
void calculateSpan(int price[], int n, int S[])
{
	// Create a stack and push index of first
	// element to it
	stack<int> st;
	st.push(0);

	// Span value of first element is always 1
	S[0] = 1;

	// Calculate span values for rest of the elements
	for (int i = 1; i < n; i++) {
		// Pop elements from stack while stack is not
		// empty and top of stack is smaller than
		// price[i]
		while (!st.empty() && price[st.top()] <= price[i])
			st.pop();

		// If stack becomes empty, then price[i] is
		// greater than all elements on left of it,
		// i.e., price[0], price[1], ..price[i-1]. Else
		// price[i] is greater than elements after
		// top of stack
		S[i] = (st.empty()) ? (i + 1) : (i - st.top());

		// Push this element to stack
		st.push(i);
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
