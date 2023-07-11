#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/

/**
	Given a 2D array, print it in spiral form.

	The problem can be solved by dividing the matrix into loops or squares or boundaries.
	It can be seen that the elements of the outer loop are printed first in a clockwise
	manner then the elements of the inner loop are printed. So printing the elements of a
	loop can be solved using four loops that print all the elements. Every ‘for’ loop
	defines a single-direction movement along with the matrix. The first for loop
	represents the movement from left to right, whereas the second crawl represents the
	movement from top to bottom, the third represents the movement from the right to left,
	and the fourth represents the movement from bottom to up

	Time Complexity: O(M*N). To traverse the matrix O(M*M) time is required.
	Auxiliary Space: O(1). No extra space is required.
*/

#define R 4
#define C 4

void spiralPrint(int m, int n, int a[R][C])
{
	int i, k = 0, l = 0;

	/* k - starting row index
		m - ending row index
		l - starting column index
		n - ending column index
		i - iterator
	*/

	while (k < m && l < n) {
		/* Print the first row from
			the remaining rows */
		for (i = l; i < n; ++i) {
			cout << a[k][i] << " ";
		}
		k++;

		/* Print the last column
		from the remaining columns */
		for (i = k; i < m; ++i) {
			cout << a[i][n - 1] << " ";
		}
		n--;

		/* Print the last row from
				the remaining rows */
		if (k < m) {
			for (i = n - 1; i >= l; --i) {
				cout << a[m - 1][i] << " ";
			}
			m--;
		}

		/* Print the first column from
				the remaining columns */
		if (l < n) {
			for (i = m - 1; i >= k; --i) {
				cout << a[i][l] << " ";
			}
			l++;
		}
	}
}

/* Driver Code */
int main()
{
	int a[R][C] = { { 1, 2, 3, 4 },
					{ 5, 6, 7, 8 },
					{ 9, 10, 11, 12 },
					{ 13, 14, 15, 16 } };

	// Function Call
	spiralPrint(R, C, a);
	return 0;
}
