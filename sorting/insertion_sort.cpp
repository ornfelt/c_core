#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/insertion-sort/

/**
	Insertion sort is a simple sorting algorithm that works similar to the way you sort
	playing cards in your hands. The array is virtually split into a sorted and an
	unsorted part. Values from the unsorted part are picked and placed at the correct
	position in the sorted part.

	Characteristics of Insertion Sort:
    This algorithm is one of the simplest algorithm with simple implementation
    Basically, Insertion sort is efficient for small data values
	Insertion sort is adaptive in nature, i.e. it is appropriate for data sets which are
	already partially sorted.

	Insertion sort is a stable sorting algorithm.
	Insertion sort is an in-place sorting algorithm.

	Insertion sort is used when number of elements is small. It can also be useful when
	input array is almost sorted, only few elements are misplaced in complete big array.

	We can use binary search to reduce the number of comparisons in normal insertion sort.

	Insertion sort takes maximum time to sort if elements are sorted in reverse order. And
	it takes minimum time (Order of n) when elements are already sorted.

	Time Complexity: O(N^2) 
	Auxiliary Space: O(1)
*/

// Function to sort an array using
// insertion sort
void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		// Move elements of arr[0..i-1],
		// that are greater than key, to one
		// position ahead of their
		// current position
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

// A utility function to print an array
// of size n
void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// Driver code
int main()
{
	int arr[] = { 12, 11, 13, 5, 6 };
	int N = sizeof(arr) / sizeof(arr[0]);

	insertionSort(arr, N);
	printArray(arr, N);

	return 0;
}
