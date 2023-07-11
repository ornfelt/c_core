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

	Advantages:
    Bubble sort is easy to understand and implement.
    It does not require any additional memory space.
    It’s adaptability to different types of data.

	Disadvantages:
	Bubble sort has a time complexity of O(n^2) which makes it very slow for large data
	sets.
	It is not efficient for large data sets, because it requires multiple passes through
	the data.
	It is not a stable sorting algorithm, meaning that elements with the same key value
	may not maintain their relative order in the sorted output.

	Due to its simplicity, bubble sort is often used to introduce the concept of a sorting
	algorithm. 

	The bubble sort algorithm is stable.
	Bubble sort performs the swapping of adjacent pairs without the use of any major data
	structure. Hence Bubble sort algorithm is an in-place algorithm.

	Optimized Implementation of Bubble Sort: 
	The above function always runs O(N2) time even if the array is sorted. It can be
	optimized by stopping the algorithm if the inner loop didn’t cause any swap. 

	Time Complexity: O(N2)
	Auxiliary Space: O(1)
*/

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
int i, j;
bool swapped;
for (i = 0; i < n-1; i++)
{
	swapped = false;
	for (j = 0; j < n-i-1; j++)
	{
		if (arr[j] > arr[j+1])
		{
		swap(arr[j], arr[j+1]);
		swapped = true;
		}
	}

	// IF no two elements were swapped
	// by inner loop, then break
	if (swapped == false)
		break;
}
}

// Function to print an array
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout <<" "<< arr[i];
}

// Driver program to test above functions
int main()
{
	int arr[] = {64, 34, 25, 12, 22, 11, 90};
	int N = sizeof(arr)/sizeof(arr[0]);
	bubbleSort(arr, N);
	cout <<"Sorted array: \n";
	printArray(arr, N);
	return 0;
}
