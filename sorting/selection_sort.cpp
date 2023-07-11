#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/selection-sort/

/**
	Selection sort is a simple and efficient sorting algorithm that works by repeatedly
	selecting the smallest (or largest) element from the unsorted portion of the list and
	moving it to the sorted portion of the list. The algorithm repeatedly selects the
	smallest (or largest) element from the unsorted portion of the list and swaps it with
	the first element of the unsorted portion. This process is repeated for the remaining
	unsorted portion of the list until the entire list is sorted. One variation of
	selection sort is called “Bidirectional selection sort” that goes through the list of
	elements by alternating between the smallest and largest element, this way the
	algorithm can be faster in some cases.

	The algorithm maintains two subarrays in a given array.
    - The subarray which already sorted. 
    - The remaining subarray was unsorted.

	In every iteration of the selection sort, the minimum element (considering ascending
	order) from the unsorted subarray is picked and moved to the beginning of unsorted
	subarray. 

	After every iteration sorted subarray size increase by one and unsorted subarray size
	decrease by one.

	Advantages of Selection Sort Algorithm:
    Simple and easy to understand.
    Preserves the relative order of items with equal keys which means it is stable.
    Works well with small datasets.
    It is adaptable to various types of data types.
	Selection sort is an in-place sorting algorithm, which means it does not require any
	additional memory to sort the list.
	It has a best-case and average-case time complexity of O(n^2), making it efficient for
	small data sets.
    It is easy to modify to sort in ascending or descending order.

	Disadvantages of Selection Sort Algorithm:
    Selection sort has a time complexity of O(n^2) in the worst and average case.
    Does not works well on large datasets.
	Selection sort algorithm needs to iterate over the list multiple times, thus it can
	lead to an unbalanced branch.
    Selection sort has poor cache performance and hence it is not cache friendly. 
	Not adaptive, meaning it doesn’t take advantage of the fact that the list may already
	be sorted or partially sorted

	The default implementation is not stable.
	Is Selection Sort Algorithm in place?
	Yes, it does not require extra space.

	Time Complexity: The time complexity of Selection Sort is O(N2) as there are two
	nested loops:
    One loop to select an element of Array one by one = O(N)
    Another loop to compare that element with every other Array element = O(N)

	Therefore overall complexity = O(N) * O(N) = O(N*N) = O(N2)

	Auxiliary Space: O(1) as the only extra memory used is for temporary variables while
	swapping two values in Array. The selection sort never makes more than O(N) swaps and
	can be useful when memory write is a costly operation. 
*/

//Swap function
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
	// One by one move boundary of
	// unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in
		// unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
		{
		if (arr[j] < arr[min_idx])
			min_idx = j;
		}
		// Swap the found minimum element
		// with the first element
		if (min_idx!=i)
			swap(&arr[min_idx], &arr[i]);
	}
}

//Function to print an array
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
	{
	cout << arr[i] << " ";
	cout << endl;
	}
}

// Driver program to test above functions
int main()
{
	int arr[] = {64, 25, 12, 22, 11};
	int n = sizeof(arr)/sizeof(arr[0]);
	selectionSort(arr, n);
	cout << "Sorted array: \n";
	printArray(arr, n);
	return 0;
}
