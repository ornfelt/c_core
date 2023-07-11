#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/a-boolean-matrix-question/

/**
	Given a boolean matrix mat[M][N] of size M X N, modify it such that if a matrix cell
	mat[i][j] is 1 (or true) then make all the cells of ith row and jth column as 1. 

	Examples:
	Input: {{1, 0},
			{0, 0}}
	Output: {{1, 1}
				{1, 0}}
	Input: {{0, 0, 0},
				{0, 0, 1}}
	Output: {{0, 0, 1},
				{1, 1, 1}}

	Input: {{1, 0, 0, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 0}}
	Output: {{1, 1, 1, 1},
				{1, 1, 1, 1},
				{1, 0, 1, 1}}


	This method is a space-optimized version of above method. This method uses the first
	row and first column of the input matrix in place of the auxiliary arrays row[] and
	col[] of above method. First take care of the first row and column and store the info
	about these two in two flag variables rowFlag and colFlag. Once we have this info, we
	can use the first row and first column as auxiliary arrays and apply method 1 for
	submatrix (matrix excluding first row and first column) of size (M-1)*(N-1).

	Steps:
	Scan the first row and set a variable rowFlag to indicate whether we need to set all
	1s in the first row or not. 
	Scan the first column and set a variable colFlag to indicate whether we need to set
	all 1s in the first column or not. 
	Use the first row and first column as the auxiliary arrays row[] and col[]
	respectively, consider the matrix as a submatrix starting from the second row and
	second column, and apply above method.
    Finally, using rowFlag and colFlag, update the first row and first column if needed.

	Time Complexity: O(M*N), Traversing over the matrix two times.
	Auxiliary Space: O(1)
*/

#define R 3
#define C 4

void modifyMatrix(int mat[R][C])
{
	// variables to check if there are any 1
	// in first row and column
	bool row_flag = false;
	bool col_flag = false;

	// updating the first row and col if 1
	// is encountered
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (i == 0 && mat[i][j] == 1)
				row_flag = true;

			if (j == 0 && mat[i][j] == 1)
				col_flag = true;

			if (mat[i][j] == 1) {

				mat[0][j] = 1;
				mat[i][0] = 1;
			}
		}
	}

	// Modify the input matrix mat[] using the
	// first row and first column of Matrix mat
	for (int i = 1; i < R; i++)
		for (int j = 1; j < C; j++)
			if (mat[0][j] == 1 || mat[i][0] == 1)
				mat[i][j] = 1;

	// modify first row if there was any 1
	if (row_flag == true)
		for (int i = 0; i < C; i++)
			mat[0][i] = 1;

	// modify first col if there was any 1
	if (col_flag == true)
		for (int i = 0; i < R; i++)
			mat[i][0] = 1;
}

/* A utility function to print a 2D matrix */
void printMatrix(int mat[R][C])
{
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++)
			cout << mat[i][j] << " ";
		cout << "\n";
	}
}

// Driver function to test the above function
int main()
{

	int mat[R][C] = { { 1, 0, 0, 1 },
					{ 0, 0, 1, 0 },
					{ 0, 0, 0, 0 } };

	cout << "Input Matrix :\n";
	printMatrix(mat);
	modifyMatrix(mat);
	cout << "Matrix After Modification :\n";
	printMatrix(mat);
	return 0;
}
