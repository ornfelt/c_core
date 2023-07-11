#include <iostream>

using namespace std;

// https://www.geeksforgeeks.org/given-n-x-n-square-matrix-find-sum-sub-squares-size-k-x-k/

/**
	Given an n x n square matrix, find sum of all sub-squares of size k x k where k is
	smaller than or equal to n. 

	Input:
	n = 5, k = 3
	arr[][] = { {1, 1, 1, 1, 1},
				{2, 2, 2, 2, 2},
				{3, 3, 3, 3, 3},
				{4, 4, 4, 4, 4},
				{5, 5, 5, 5, 5},
			};
	Output:
		18  18  18
		27  27  27
		36  36  36

	We can solve this problem in O(n2) time using a Tricky Solution. 

	The idea is to preprocess the given square matrix. In the preprocessing step,
	calculate sum of all vertical strips of size k x 1 in a temporary square matrix
	stripSum[][]. Once we have sum of all vertical strips, we can calculate sum of first
	sub-square in a row as sum of first k strips in that row, and for remaining
	sub-squares, we can calculate sum in O(1) time by removing the leftmost strip of
	previous subsquare and adding the rightmost strip of new square. 

	Time complexity: O(n2).
	Auxiliary Space: O(n2).
*/

// Size of given matrix
#define n 5

// A O(n^2) function to find sum of all sub-squares of size
// k x k in a given square matrix of size n x n
void printSumTricky(int mat[][n], int k)
{
	// k must be smaller than or equal to n
	if (k > n)
		return;

	// 1: PREPROCESSING
	// To store sums of all strips of size k x 1
	int stripSum[n][n];

	// Go column by column
	for (int j = 0; j < n; j++) {
		// Calculate sum of first k x 1 rectangle in this
		// column
		int sum = 0;
		for (int i = 0; i < k; i++)
			sum += mat[i][j];
		stripSum[0][j] = sum;

		// Calculate sum of remaining rectangles
		for (int i = 1; i < n - k + 1; i++) {
			sum += (mat[i + k - 1][j] - mat[i - 1][j]);
			stripSum[i][j] = sum;
		}
	}

	// 2: CALCULATE SUM of Sub-Squares using stripSum[][]
	for (int i = 0; i < n - k + 1; i++) {
		// Calculate and print sum of first subsquare in
		// this row
		int sum = 0;
		for (int j = 0; j < k; j++)
			sum += stripSum[i][j];
		cout << sum << " ";

		// Calculate sum of remaining squares in current row
		// by removing the leftmost strip of previous
		// sub-square and adding a new strip
		for (int j = 1; j < n - k + 1; j++) {
			sum += (stripSum[i][j + k - 1]
					- stripSum[i][j - 1]);
			cout << sum << " ";
		}

		cout << endl;
	}
}

// Driver program to test above function
int main()
{
	int mat[n][n] = {
		{ 1, 1, 1, 1, 1 }, { 2, 2, 2, 2, 2 },
		{ 3, 3, 3, 3, 3 }, { 4, 4, 4, 4, 4 },
		{ 5, 5, 5, 5, 5 },
	};
	int k = 3;
	printSumTricky(mat, k);
	return 0;
}
