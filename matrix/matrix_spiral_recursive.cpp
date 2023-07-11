#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/

/**
	Given a 2D array, print it in spiral form.

	The above problem can be solved by printing the boundary of the Matrix recursively. In
	each recursive call, we decrease the dimensions of the matrix. The idea of printing
	the boundary or loops is the same

	Time Complexity: O(M*N). To traverse the matrix O(m*n) time is required.
	Auxiliary Space: O(1). No extra space is required.
*/

#define R 4
#define C 4

// Function for printing matrix in spiral
// form i, j: Start index of matrix, row
// and column respectively m, n: End index
// of matrix row and column respectively
void print(int arr[R][C], int i, int j, int m, int n)
{
	// If i or j lies outside the matrix
	if (i >= m or j >= n)
		return;

	// Print First Row
	for (int p = j; p < n; p++)
		cout << arr[i][p] << " ";

	// Print Last Column
	for (int p = i + 1; p < m; p++)
		cout << arr[p][n - 1] << " ";

	// Print Last Row, if Last and
	// First Row are not same
	if ((m - 1) != i)
		for (int p = n - 2; p >= j; p--)
			cout << arr[m - 1][p] << " ";

	// Print First Column, if Last and
	// First Column are not same
	if ((n - 1) != j)
		for (int p = m - 2; p > i; p--)
			cout << arr[p][j] << " ";

	print(arr, i + 1, j + 1, m - 1, n - 1);
}

// Driver Code
int main()
{
	int a[R][C] = { { 1, 2, 3, 4 },
					{ 5, 6, 7, 8 },
					{ 9, 10, 11, 12 },
					{ 13, 14, 15, 16 } };

	// Function Call
	print(a, 0, 0, R, C);
	return 0;
}
