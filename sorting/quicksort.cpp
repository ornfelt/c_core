#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/quick-sort/

/**
	Like Merge Sort, QuickSort is a Divide and Conquer algorithm. It picks an element as a
	pivot and partitions the given array around the picked pivot. There are many different
	versions of quickSort that pick pivot in different ways. 

    - Always pick the first element as a pivot.
    - Always pick the last element as a pivot (implemented below)
    - Pick a random element as a pivot.
    - Pick median as the pivot.

	The key process in quickSort is a partition(). The target of partitions is, given an
	array and an element x of an array as the pivot, put x at its correct position in a
	sorted array and put all smaller elements (smaller than x) before x, and put all
	greater elements (greater than x) after x. All this should be done in linear time.

	Advantages of Quick Sort:
    It is a divide-and-conquer algorithm that makes it easier to solve problems.
    It is efficient on large data sets.
    It has a low overhead, as it only requires a small amount of memory to function.

	Disadvantages of Quick Sort:
    It has a worst-case time complexity of O(n^2), which occurs when the pivot is chosen poorly.
    It is not a good choice for small data sets.
    It can be sensitive to the choice of pivot.
    It is not cache-efficient.
	It is not stable sort, meaning that if two elements have the same key, their relative
	order will not be preserved in the sorted output in case of quick sort, because here
	we swapping of elements according to pivot’s position (without considering their
	original positions).

	The default implementation is not stable. 
	Is QuickSort In-place? 
	As per the broad definition of in-place algorithm it qualifies as an in-place sorting
	algorithm as it uses extra space only for storing recursive function calls but not for
	manipulating the input. 

	Average Case: 
	To do average case analysis, we need to consider all possible permutation of array and
	calculate time taken by every permutation which doesn’t look easy. We can get an idea
	of average case by considering the case when partition puts O(n/9) elements in one set
	and O(9n/10) elements in other set. Following is recurrence for this case.  
    T(n) = T(n/9) + T(9n/10) + \theta (n)

	The solution of above recurrence is also O(nLogn):

	However, it also has some drawbacks such as worst case time complexity of O(n^2) which
	occurs when the pivot is chosen poorly.
*/

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates
	// the right position of pivot found so far

	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than the pivot
		if (arr[j] < pivot) {
			i++; // increment index of smaller element
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// Driver Code
int main()
{
	int arr[] = { 10, 7, 8, 9, 1, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, 0, n - 1);
	cout << "Sorted array: \n";
	printArray(arr, n);
	return 0;
}
