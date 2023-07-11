#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/bubble-sort/

/**
	Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping the
	adjacent elements if they are in the wrong order. This algorithm is not suitable for
	large data sets as its average and worst-case time complexity is quite high.

	Steps:
	Run a nested for loop to traverse the input array using two variables i and j, such
	that 0 ≤ i < n-1 and 0 ≤ j < n-i-1
	If arr[j] is greater than arr[j+1] then swap these adjacent elements, else move on
    Print the sorted array

	Time Complexity: O(N2)
	Auxiliary Space: O(1) 
	Also see optimized implementation...
*/

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		// Last i elements are already
		// in place
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}

// Function to print an array
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// Driver code
int main()
{
	int arr[] = { 5, 1, 4, 2, 8};
	int N = sizeof(arr) / sizeof(arr[0]);
	bubbleSort(arr, N);
	cout << "Sorted array: \n";
	printArray(arr, N);
	return 0;
}
