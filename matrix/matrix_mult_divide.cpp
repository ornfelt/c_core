#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/strassens-matrix-multiplication/

/**
  Divide and Conquer:
	Following is simple Divide and Conquer method to multiply two square matrices. 

    Divide matrices A and B in 4 sub-matrices of size N/2 x N/2 as shown in the below diagram. 
    Calculate following values recursively. ae + bg, af + bh, ce + dg and cf + dh. 

	In the above method, we do 8 multiplications for matrices of size N/2 x N/2 and 4
	additions. Addition of two matrices takes O(N2) time. So the time complexity can be
	written as 
	T(N) = 8T(N/2) + O(N2)  

	From Master's Theorem, time complexity of above method is O(N3) which is unfortunately
	same as the above naive method.

	Simple Divide and Conquer also leads to O(N3), can there be a better way? 

	In the above divide and conquer method, the main component for high time complexity is
	8 recursive calls. The idea of Strassen’s method is to reduce the number of recursive
	calls to 7. Strassen’s method is similar to above simple divide and conquer method in
	the sense that this method also divide matrices to sub-matrices of size N/2 x N/2 as
	shown in the above diagram, but in Strassen’s method, the four sub-matrices of result
	are calculated using following formulae.

	See Strassens method...
*/

#define ROW_1 4
#define COL_1 4

#define ROW_2 4
#define COL_2 4

void print(string display, vector<vector<int> > matrix,
		int start_row, int start_column, int end_row,
		int end_column)
{
	cout << endl << display << " =>" << endl;
	for (int i = start_row; i <= end_row; i++) {
		for (int j = start_column; j <= end_column; j++) {
			cout << setw(10);
			cout << matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
	return;
}

void add_matrix(vector<vector<int> > matrix_A,
				vector<vector<int> > matrix_B,
				vector<vector<int> >& matrix_C,
				int split_index)
{
	for (auto i = 0; i < split_index; i++)
		for (auto j = 0; j < split_index; j++)
			matrix_C[i][j]
				= matrix_A[i][j] + matrix_B[i][j];
}

vector<vector<int> >
multiply_matrix(vector<vector<int> > matrix_A,
				vector<vector<int> > matrix_B)
{
	int col_1 = matrix_A[0].size();
	int row_1 = matrix_A.size();
	int col_2 = matrix_B[0].size();
	int row_2 = matrix_B.size();

	if (col_1 != row_2) {
		cout << "\nError: The number of columns in Matrix "
				"A must be equal to the number of rows in "
				"Matrix B\n";
		return {};
	}

	vector<int> result_matrix_row(col_2, 0);
	vector<vector<int> > result_matrix(row_1,
									result_matrix_row);

	if (col_1 == 1)
		result_matrix[0][0]
			= matrix_A[0][0] * matrix_B[0][0];
	else {
		int split_index = col_1 / 2;

		vector<int> row_vector(split_index, 0);
		vector<vector<int> > result_matrix_00(split_index,
											row_vector);
		vector<vector<int> > result_matrix_01(split_index,
											row_vector);
		vector<vector<int> > result_matrix_10(split_index,
											row_vector);
		vector<vector<int> > result_matrix_11(split_index,
											row_vector);

		vector<vector<int> > a00(split_index, row_vector);
		vector<vector<int> > a01(split_index, row_vector);
		vector<vector<int> > a10(split_index, row_vector);
		vector<vector<int> > a11(split_index, row_vector);
		vector<vector<int> > b00(split_index, row_vector);
		vector<vector<int> > b01(split_index, row_vector);
		vector<vector<int> > b10(split_index, row_vector);
		vector<vector<int> > b11(split_index, row_vector);

		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				a00[i][j] = matrix_A[i][j];
				a01[i][j] = matrix_A[i][j + split_index];
				a10[i][j] = matrix_A[split_index + i][j];
				a11[i][j] = matrix_A[i + split_index]
									[j + split_index];
				b00[i][j] = matrix_B[i][j];
				b01[i][j] = matrix_B[i][j + split_index];
				b10[i][j] = matrix_B[split_index + i][j];
				b11[i][j] = matrix_B[i + split_index]
									[j + split_index];
			}

		add_matrix(multiply_matrix(a00, b00),
				multiply_matrix(a01, b10),
				result_matrix_00, split_index);
		add_matrix(multiply_matrix(a00, b01),
				multiply_matrix(a01, b11),
				result_matrix_01, split_index);
		add_matrix(multiply_matrix(a10, b00),
				multiply_matrix(a11, b10),
				result_matrix_10, split_index);
		add_matrix(multiply_matrix(a10, b01),
				multiply_matrix(a11, b11),
				result_matrix_11, split_index);

		for (auto i = 0; i < split_index; i++)
			for (auto j = 0; j < split_index; j++) {
				result_matrix[i][j]
					= result_matrix_00[i][j];
				result_matrix[i][j + split_index]
					= result_matrix_01[i][j];
				result_matrix[split_index + i][j]
					= result_matrix_10[i][j];
				result_matrix[i + split_index]
							[j + split_index]
					= result_matrix_11[i][j];
			}

		result_matrix_00.clear();
		result_matrix_01.clear();
		result_matrix_10.clear();
		result_matrix_11.clear();
		a00.clear();
		a01.clear();
		a10.clear();
		a11.clear();
		b00.clear();
		b01.clear();
		b10.clear();
		b11.clear();
	}
	return result_matrix;
}

int main()
{
	vector<vector<int> > matrix_A = { { 1, 1, 1, 1 },
									{ 2, 2, 2, 2 },
									{ 3, 3, 3, 3 },
									{ 2, 2, 2, 2 } };

	print("Array A", matrix_A, 0, 0, ROW_1 - 1, COL_1 - 1);

	vector<vector<int> > matrix_B = { { 1, 1, 1, 1 },
									{ 2, 2, 2, 2 },
									{ 3, 3, 3, 3 },
									{ 2, 2, 2, 2 } };

	print("Array B", matrix_B, 0, 0, ROW_2 - 1, COL_2 - 1);

	vector<vector<int> > result_matrix(
		multiply_matrix(matrix_A, matrix_B));

	print("Result Array", result_matrix, 0, 0, ROW_1 - 1,
		COL_2 - 1);
}
