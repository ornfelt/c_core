#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/print-unique-rows/

/**
	Given a binary matrix, print all unique rows of the given matrix
	Input:
			{0, 1, 0, 0, 1}
			{1, 0, 1, 1, 0}
			{0, 1, 0, 0, 1}
			{1, 1, 1, 0, 0}
	Output:
		0 1 0 0 1 
		1 0 1 1 0 
		1 1 1 0 0 

	Method 1: This method explains the simple approach towards solving the above problem. 

	Approach: A simple approach would be to check each row with all processed rows. Print
	the first row. Now, starting from the second row, for each row, compare the row with
	already processed rows. If the row matches with any of the processed rows, skip it
	else print it.

    Algorithm: 
        Traverse the matrix row-wise
        For each row check if there is any similar row less than the current index.
        If any two rows are similar then do not print the row.
        Else print the row.

    Time complexity: O( ROW^2 x COL ). 
	So for every row check if there is any other similar row. So the time complexity is O(
	ROW^2 x COL ).
    Auxiliary Space: O(1). As no extra space is required.
*/

#define ROW 4
#define COL 5

// The main function that prints
// all unique rows in a given matrix.
void findUniqueRows(int M[ROW][COL])
{
	//Traverse through the matrix
	for(int i=0; i<ROW; i++)
	{
		int flag=0;
		
		//check if there is similar column
		//is already printed, i.e if i and
		//jth column match.
		for(int j=0; j<i; j++)
		{
			flag=1;
			
			for(int k=0; k<=COL; k++)
			if(M[i][k]!=M[j][k])
				flag=0;
			
			if(flag==1)
			break;
		}
		
		//if no row is similar
		if(flag==0)
		{
			//print the row
			for(int j=0; j<COL; j++)
				cout<<M[i][j]<<" ";
			cout<<endl;
		}
	}
}

// Driver Code
int main()
{
	int M[ROW][COL] = {{0, 1, 0, 0, 1},
					{1, 0, 1, 1, 0},
					{0, 1, 0, 0, 1},
					{1, 0, 1, 0, 0}};

	findUniqueRows(M);

	return 0;
}
