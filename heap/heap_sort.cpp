#include <iostream>

using namespace std;

// https://www.geeksforgeeks.org/heap-sort/

/**
	Heap sort is a comparison-based sorting technique based on Binary Heap data structure.
	It is similar to the selection sort where we first find the minimum element and place
	the minimum element at the beginning. Repeat the same process for the remaining
	elements.

    Heap sort is an in-place algorithm. 
    - Its typical implementation is not stable, but can be made stable (See link below)
	https://www.geeksforgeeks.org/stable-and-unstable-sorting-algorithms/

	- Typically 2-3 times slower than well-implemented QuickSort.  The reason for slowness
	is a lack of locality of reference.

	Advantages of heapsort:
	Efficiency –  The time required to perform Heap sort increases logarithmically while
	other algorithms may grow exponentially slower as the number of items to sort
	increases. This sorting algorithm is very efficient.
	Memory Usage – Memory usage is minimal because apart from what is necessary to hold
	the initial list of items to be sorted, it needs no additional memory space to work
	Simplicity –  It is simpler to understand than other equally efficient sorting
	algorithms because it does not use advanced computer science concepts such as
	recursion.

	Disadvantages of Heap Sort:
    Costly: Heap sort is costly.
    Unstable: Heap sort is unstable. It might rearrange the relative order.
    Efficient: Heap Sort are not very efficient when working with highly complex data. 

	Applications of HeapSort:
    Heapsort is mainly used in hybrid algorithms like the IntroSort.
    Sort a nearly sorted (or K sorted) array 
    k largest(or smallest) elements in an array 

	Heapify is the process of creating a heap data structure from a binary tree
	represented using an array. It is used to create Min-Heap or Max-heap. Start from the
	last index of the non-leaf node whose index is given by n/2 – 1. Heapify uses
	recursion.

	First convert the array into heap data structure using heapify, then one by one delete
	the root node of the Max-heap and replace it with the last node in the heap and then
	heapify the root of the heap. Repeat this process until size of heap is greater than
	1.

	Steps:
    - Build a max heap from the input data. 
	- At this point, the maximum element is stored at the root of the heap. Replace it
	with the last item of the heap followed by reducing the size of the heap by 1.
	Finally, heapify the root of the tree. 
    - Repeat step 2 while the size of the heap is greater than 1.

	* This algorithm is not stable because the operations that are performed in a heap can
	change the relative ordering of the equivalent keys.

	* Heap sort is NOT at all a Divide and Conquer algorithm. It uses a heap data structure
	to efficiently sort its element and not a “divide and conquer approach” to sort the
	elements.

	* The two phases of Heap sort:
	The heap sort algorithm consists of two phases. In the first phase the array is
	converted into a max heap. And in the second phase the highest element is removed
	(i.e., the one at the tree root) and the remaining elements are used to create a new
	max heap.

	Time Complexity: O(N log N)
	Auxiliary Space: O(1)
*/

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int arr[], int N, int i)
{

	// Initialize largest as root
	int largest = i;

	// left = 2*i + 1
	int l = 2 * i + 1;

	// right = 2*i + 2
	int r = 2 * i + 2;

	// If left child is larger than root
	if (l < N && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest
	// so far
	if (r < N && arr[r] > arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i) {
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected
		// sub-tree
		heapify(arr, N, largest);
	}
}

// Main function to do heap sort
void heapSort(int arr[], int N)
{

	// Build heap (rearrange array)
	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(arr, N, i);

	// One by one extract an element
	// from heap
	for (int i = N - 1; i > 0; i--) {

		// Move current root to end
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

// A utility function to print array of size n
void printArray(int arr[], int N)
{
	for (int i = 0; i < N; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

// Driver's code
int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	int N = sizeof(arr) / sizeof(arr[0]);

	// Function call
	heapSort(arr, N);

	cout << "Sorted array is \n";
	printArray(arr, N);
}
