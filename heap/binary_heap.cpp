#include<iostream>
#include<climits>

using namespace std;

// https://www.geeksforgeeks.org/binary-heap/

/**
	A Binary Heap is a Binary Tree with following properties.
	1) It’s a complete tree (All levels are completely filled except possibly the last
	level and the last level has all keys as left as possible). This property of Binary
	Heap makes them suitable to be stored in an array.

	2) A Binary Heap is either Min Heap or Max Heap. In a Min Binary Heap, the key at root
	must be minimum among all keys present in Binary Heap. The same property must be
	recursively true for all nodes in Binary Tree. Max Binary Heap is similar to MinHeap.

	A Binary Heap is a Complete Binary Tree. A binary heap is typically represented as an
	array. The root element will be at Arr[0].

	Applications of Heaps:
	1) Heap Sort: Heap Sort uses Binary Heap to sort an array in O(nLogn) time.

	2) Priority Queue: Priority queues can be efficiently implemented using Binary Heap
	because it supports insert(), delete() and extractmax(), decreaseKey() operations in
	O(logn) time. Binomial Heap and Fibonacci Heap are variations of Binary Heap. These
	variations perform union also efficiently.

	3) Graph Algorithms: The priority queues are especially used in Graph Algorithms like
	Dijkstra’s Shortest Path and Prim’s Minimum Spanning Tree.

	4) Many problems can be efficiently solved using Heaps. See following for example.
	a) K’th Largest Element in an array.
	b) Sort an almost sorted array/
	c) Merge K Sorted Arrays.

	Operations on Min Heap:
	1) getMini(): It returns the root element of Min Heap. Time Complexity of this
	operation is O(1).

	2) extractMin(): Removes the minimum element from MinHeap. Time Complexity of this
	Operation is O(Logn) as this operation needs to maintain the heap property (by calling
	heapify()) after removing root.

	3) decreaseKey(): Decreases value of key. The time complexity of this operation is
	O(Logn). If the decreases key value of a node is greater than the parent of the node,
	then we don’t need to do anything. Otherwise, we need to traverse up to fix the
	violated heap property.

	4) insert(): Inserting a new key takes O(Logn) time. We add a new key at the end of
	the tree. IF new key is greater than its parent, then we don’t need to do anything.
	Otherwise, we need to traverse up to fix the violated heap property.

	5) delete(): Deleting a key also takes O(Logn) time. We replace the key to be deleted
	with minum infinite by calling decreaseKey(). After decreaseKey(), the minus infinite
	value must reach root, so we call extractMin() to remove the key.

	Why is Binary Heap Preferred over BST for Priority Queue?
	A typical Priority Queue requires following operations to be efficient.
		Get Top Priority Element (Get minimum or maximum)
		Insert an element
		Remove top priority element
		Decrease Key

	A Binary Heap supports above operations with following time complexities:
		O(1)
		O(Logn)
		O(Logn)
		O(Logn)

	A Self Balancing Binary Search Tree like AVL Tree, Red-Black Tree, etc can also
	support above operations with same time complexities.
	Since Binary Heap is implemented using arrays, there is always better locality of
	reference and operations are more cache friendly.

	A Binomial Heap is a collection of Binomial Trees 
	A Binomial Tree of order 0 has 1 node. A Binomial Tree of order k can be constructed
	by taking two binomial trees of order k-1 and making one the leftmost child of the other. 

	Below is the implementation of basic heap operations.
*/

// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A class for Min Heap
class MinHeap
{
	int *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
public:
	// Constructor
	MinHeap(int capacity);

	// to heapify a subtree with the root at given index
	void MinHeapify(int );

	int parent(int i) { return (i-1)/2; }

	// to get index of left child of node at index i
	int left(int i) { return (2*i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2*i + 2); }

	// to extract the root which is the minimum element
	int extractMin();

	// Decreases key value of key at index i to new_val
	void decreaseKey(int i, int new_val);

	// Returns the minimum key (key at root) from min heap
	int getMin() { return harr[0]; }

	// Deletes a key stored at index i
	void deleteKey(int i);

	// Inserts a new key 'k'
	void insertKey(int k);
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	// Fix the min heap property if it is violated
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// Store the minimum value, and remove it from heap
	int root = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	MinHeapify(0);

	return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

// A utility function to swap two elements
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

// Driver program to test above functions
int main()
{
	MinHeap h(11);
	h.insertKey(3);
	h.insertKey(2);
	h.deleteKey(1);
	h.insertKey(15);
	h.insertKey(5);
	h.insertKey(4);
	h.insertKey(45);
	cout << h.extractMin() << " ";
	cout << h.getMin() << " ";
	h.decreaseKey(2, 1);
	cout << h.getMin();
	return 0;
}