#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/find-common-element-rows-row-wise-sorted-matrix/

/**
	Given a matrix where every row is sorted in increasing order. Write a function that
	finds and returns a common element in all rows. If there is no common element, then
	returns -1. 

	Example: 
	Input: mat[4][5] = { {1, 2, 3, 4, 5},
						{2, 4, 5, 8, 10},
						{3, 5, 7, 9, 11},
						{1, 3, 5, 7, 9},
					};
	Output: 5

	We can solve this problem in O(mn) time using the approach similar to merge of Merge
	Sort. The idea is to start from the last column of every row. If elements at all last
	columns are same, then we found the common element. Otherwise we find the minimum of
	all last columns. Once we find a minimum element, we know that all other elements in
	last columns cannot be a common element, so we reduce last column index for all rows
	except for the row which has minimum value. We keep repeating these steps till either
	all elements at current last column don’t become same, or a last column index reaches
	0.
	Below is the implementation of above idea.

	Time complexity: O(M x N).
	Auxiliary Space: O(M)
*/

// Specify number of rows and columns
#define M 4
#define N 5

// Returns common element in all rows of mat[M][N]. If there is no
// common element, then -1 is returned
int findCommon(int mat[M][N])
{
	// An array to store indexes of current last column
	int column[M];
	int min_row; // To store index of row whose current
	// last element is minimum

	// Initialize current last element of all rows
	int i;
	for (i = 0; i < M; i++)
		column[i] = N - 1;

	min_row = 0; // Initialize min_row as first row

	// Keep finding min_row in current last column, till either
	// all elements of last column become same or we hit first column.
	while (column[min_row] >= 0) {
		// Find minimum in current last column
		for (i = 0; i < M; i++) {
			if (mat[i][column[i]] < mat[min_row][column[min_row]])
				min_row = i;
		}

		// eq_count is count of elements equal to minimum in current last
		// column.
		int eq_count = 0;

		// Traverse current last column elements again to update it
		for (i = 0; i < M; i++) {
			// Decrease last column index of a row whose value is more
			// than minimum.
			if (mat[i][column[i]] > mat[min_row][column[min_row]]) {
				if (column[i] == 0)
					return -1;

				column[i] -= 1; // Reduce last column index by 1
			}
			else
				eq_count++;
		}

		// If equal count becomes M, return the value
		if (eq_count == M)
			return mat[min_row][column[min_row]];
	}
	return -1;
}

// Driver Code
int main()
{
	int mat[M][N] = {
		{ 1, 2, 3, 4, 5 },
		{ 2, 4, 5, 8, 10 },
		{ 3, 5, 7, 9, 11 },
		{ 1, 3, 5, 7, 9 },
	};
	int result = findCommon(mat);
	if (result == -1)
		cout << "No common element";
	else
		cout << "Common element is " << result;
	return 0;
}
