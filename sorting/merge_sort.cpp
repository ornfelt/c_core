#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// https://www.geeksforgeeks.org/merge-sort/

/**
	Merge sort is a sorting algorithm that works by dividing an array into smaller
	subarrays, sorting each subarray, and then merging the sorted subarrays back together
	to form the final sorted array.

	In simple terms, we can say that the process of merge sort is to divide the array into
	two halves, sort each half, and then merge the sorted halves back together. This
	process is repeated until the entire array is sorted.

	One thing that you might wonder is what is the specialty of this algorithm. We already
	have a number of sorting algorithms then why do we need this algorithm? One of the
	main advantages of merge sort is that it has a time complexity of O(n log n), which
	means it can sort large arrays relatively quickly. It is also a stable sort, which
	means that the order of elements with equal values is preserved during the sort.

	Merge sort is a popular choice for sorting large datasets because it is relatively
	efficient and easy to implement. It is often used in conjunction with other
	algorithms, such as quicksort, to improve the overall performance of a sorting
	routine.

	Applications of Merge Sort: 
	Merge Sort is useful for sorting linked lists in O(N log N) time. In the case of
	linked lists, the case is different mainly due to the difference in memory allocation
	of arrays and linked lists. Unlike arrays, linked list nodes may not be adjacent in
	memory. Unlike an array, in the linked list, we can insert items in the middle in O(1)
	extra space and O(1) time. Therefore, the merge operation of merge sort can be
	implemented without extra space for linked lists.
	In arrays, we can do random access as elements are contiguous in memory. Let us say we
	have an integer (4-byte) array A and let the address of A[0] be x then to access A[i],
	we can directly access the memory at (x + i*4). Unlike arrays, we can not do random
	access in the linked list. Quick Sort requires a lot of this kind of access. In a
	linked list to access i’th index, we have to travel each and every node from the head
	to i’th node as we don’t have a contiguous block of memory. Therefore, the overhead
	increases for quicksort. Merge sort accesses data sequentially and the need of random
	access is low.
    Inversion Count Problem
    Used in External Sorting

	Advantages of Merge Sort:
	Merge sort has a time complexity of O(n log n), which means it is relatively efficient
	for sorting large datasets.
	Merge sort is a stable sort, which means that the order of elements with equal values
	is preserved during the sort.

	Drawbacks of Merge Sort:
	Slower compared to the other sort algorithms for smaller tasks. Although effecient for
	large datasets its not the best choice for small datasets.
	The merge sort algorithm requires an additional memory space of 0(n) for the temporary
	array. This is to store the subarrays that are used during the sorting process.
    It goes through the whole process even if the array is sorted.

	Merge sort is stable. 
	Is Merge sort In Place?
	No, In merge sort the merging step requires extra space to store the elements.

	Time Complexity: O(N log(N)),  Sorting arrays on different machines. Merge Sort is a
	recursive algorithm and time complexity can be expressed as following recurrence
	relation. 

    T(n) = 2T(n/2) + θ(n)

	The above recurrence can be solved either using the Recurrence Tree method or the
	Master method. It falls in case II of the Master Method and the solution of the
	recurrence is θ(Nlog(N)). The time complexity of Merge Sort isθ(Nlog(N)) in all 3
	cases (worst, average, and best) as merge sort always divides the array into two
	halves and takes linear time to merge two halves.
	Auxiliary Space: O(n), In merge sort all elements are copied into an auxiliary array.

	So N auxiliary space is required for merge sort.
*/

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid,
		int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne
		= 0, // Initial index of first sub-array
		indexOfSubArrayTwo
		= 0; // Initial index of second sub-array
	int indexOfMergedArray
		= left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size)
{
	for (auto i = 0; i < size; i++)
		cout << A[i] << " ";
}

// Driver code
int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	auto arr_size = sizeof(arr) / sizeof(arr[0]);

	cout << "Given array is \n";
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	cout << "\nSorted array is \n";
	printArray(arr, arr_size);
	return 0;
}
