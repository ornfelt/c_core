#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/search-in-row-wise-and-column-wise-sorted-matrix/

/**
	Given an n x n matrix and an integer x, find the position of x in the matrix if it is
	present. Otherwise, print “Element not found”. Every row and column of the matrix is
	sorted in increasing order. The designed algorithm should have linear time complexity

	Input: mat[4][4] = { {10, 20, 30, 40},  x = 29
                               {15, 25, 35, 45},
                               {27, 29, 37, 48},
                             {32, 33, 39, 50}}
 
	Output: Found at (2, 1)

	Follow the given steps to solve the problem:
    Let the given element be x, create two variable i = 0, j = n-1 as index of row and column.
    Run a loop until i < n.
		Check if the current element is greater than x then decrease the count of j.
		Exclude the current column.
		Check if the current element is less than x then increase the count of i. Exclude
		the current row.
        If the element is equal, then print the position and end.
    Print the Element is not found

	Time Complexity: O(N), Only one traversal is needed, i.e, i from 0 to n and j from n-1
	to 0 with at most 2*N steps. The above approach will also work for the M x N matrix
	(not only for N x N). Complexity would be O(M + N)

	Auxiliary Space: O(1), No extra space is required
*/

/* Searches the element x in mat[][]. If the
element is found, then prints its position
and returns true, otherwise prints "not found"
and returns false */
int search(int mat[4][4], int n, int x)
{
	if (n == 0)
		return -1;

	int smallest = mat[0][0], largest = mat[n - 1][n - 1];
	if (x < smallest || x > largest)
		return -1;

	// set indexes for top right element
	int i = 0, j = n - 1;
	while (i < n && j >= 0) {
		if (mat[i][j] == x) {
			cout << "Element found at " << i << ", " << j;
			return 1;
		}
		if (mat[i][j] > x)
			j--;

		// Check if mat[i][j] < x
		else
			i++;
	}

	cout << "n Element not found";
	return 0;
}

// Driver code
int main()
{
	int mat[4][4] = { { 10, 20, 30, 40 },
					{ 15, 25, 35, 45 },
					{ 27, 29, 37, 48 },
					{ 32, 33, 39, 50 } };

	// Function call
	search(mat, 4, 29);

	return 0;
}
