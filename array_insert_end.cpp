#include <iostream>

using namespace std;

// https://www.geeksforgeeks.org/search-insert-and-delete-in-an-unsorted-array/

/**
	How to insert in an unsorted array:

	Insert at the end:
	In an unsorted array, the insert operation is faster as compared to a sorted array
	because we don’t have to care about the position at which the element is to be placed.

	Time Complexity: O(1) 
	Auxiliary Space: O(1)
*/

// Inserts a key in arr[] of given capacity.
// n is current size of arr[]. This
// function returns n + 1 if insertion
// is successful, else n.
int insertSorted(int arr[], int n, int key, int capacity)
{

	// Cannot insert more elements if n is
	// already more than or equal to capacity
	if (n >= capacity)
		return n;

	arr[n] = key;

	return (n + 1);
}

// Driver Code
int main()
{
	int arr[20] = { 12, 16, 20, 40, 50, 70 };
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int n = 6;
	int i, key = 26;

	cout << "\n Before Insertion: ";
	for (i = 0; i < n; i++)
		cout << arr[i] << " ";

	// Inserting key
	n = insertSorted(arr, n, key, capacity);

	cout << "\n After Insertion: ";
	for (i = 0; i < n; i++)
		cout << arr[i] << " ";

	return 0;
}
