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

	Method 4: This method uses HashSet data structure to solve the above problem. The
	HashSet class implements the Set interface, backed by a hash table which is actually a
	HashMap instance. No guarantee is made as to the iteration order of the set which
	means that the class does not guarantee the constant order of elements over time. This
	class permits the null element. The class offers constant time performance for the
	basic operations like add, remove, contains and size assuming the hash function
	disperses the elements properly among the buckets. 

	Approach: In this method convert the whole row into a single String and then if check
	it is already present in the HashSet or not. If the row is present then we will leave
	it otherwise we will print unique row and add it to HashSet.

    Algorithm: 
        Create a HashSet where rows can be stored as a String.
        Traverse through the matrix and insert the row as String into the HashSet.
        HashSet cannot store duplicate entries so the duplicates will be removed
        Traverse the HashSet and print the rows.

	Time complexity: O( ROW x COL ). 
	To traverse the matrix and insert in the HashSet the time complexity is O( ROW x COL)
    Auxiliary Space: O( ROW ). 
    To store the HashSet O(ROW x COL) space complexity is needed.
*/

void printArray(int arr[][5], int row,
							int col)
{
	unordered_set<string> uset;
	
	for(int i = 0; i < row; i++)
	{
		string s = "";
		
		for(int j = 0; j < col; j++)
			s += to_string(arr[i][j]);
		
		if(uset.count(s) == 0)
		{
			uset.insert(s);
			cout << s << endl;
			
		}
	}
}

// Driver code
int main()
{
	int arr[][5] = {{0, 1, 0, 0, 1},
					{1, 0, 1, 1, 0},
					{0, 1, 0, 0, 1},
					{1, 1, 1, 0, 0}};
	
	printArray(arr, 4, 5);
}
