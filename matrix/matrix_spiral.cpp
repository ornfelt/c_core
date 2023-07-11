#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/

/**
	Given a 2D array, print it in spiral form.

	Print a given matrix in spiral form using the simulation approach:

	Steps:
    Let the array have R rows and C columns
	seen[r] denotes that the cell on the r-th row and c-th column was previously visited.
	Our current position is (r, c), facing direction di, and we want to visit R x C total
	cells.
    As we move through the matrix, our candidate’s next position is (cr, cc). 
	If the candidate is in the bounds of the matrix and unseen, then it becomes our next
	position; otherwise, our next position is the one after performing a clockwise turn

	Time Complexity: O(N), where N is the total number of elements in the input matrix. We
	add every element in the matrix to our final answer
	Auxiliary Space: O(N), the information stored in seen and in ans.
*/

vector<int> spiralOrder(vector<vector<int> >& matrix)
{
	int m = matrix.size(), n = matrix[0].size();
	vector<int> ans;

	if (m == 0)
		return ans;

	vector<vector<bool> > seen(m, vector<bool>(n, false));
	int dr[] = { 0, 1, 0, -1 };
	int dc[] = { 1, 0, -1, 0 };

	int x = 0, y = 0, di = 0;

	// Iterate from 0 to m * n - 1
	for (int i = 0; i < m * n; i++) {
		ans.push_back(matrix[x][y]);
		// on normal geeksforgeeks ui page it is showing
		// 'ans.push_back(matrix[x])' which gets copied as
		// this only and gives error on compilation,
		seen[x][y] = true;
		int newX = x + dr[di];
		int newY = y + dc[di];

		if (0 <= newX && newX < m && 0 <= newY && newY < n
			&& !seen[newX][newY]) {
			x = newX;
			y = newY;
		}
		else {
			di = (di + 1) % 4;
			x += dr[di];
			y += dc[di];
		}
	}
	return ans;
}

// Driver code
int main()
{
	vector<vector<int> > a{ { 1, 2, 3, 4 },
							{ 5, 6, 7, 8 },
							{ 9, 10, 11, 12 },
							{ 13, 14, 15, 16 } };

	// Function call
	for (int x : spiralOrder(a)) {
		cout << x << " ";
	}
	return 0;
}
