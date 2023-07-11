#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/introduction-and-array-implementation-of-queue/

/**
	Priority Queue: This queue is a special type of queue. Its specialty is that it
	arranges the elements in a queue based on some priority. The priority can be something
	where the element with the highest value has the priority so it creates a queue with
	decreasing order of values. The priority can also be such that the element with the
	lowest value gets the highest priority so in turn it creates a queue with increasing
	order of values. In pre-define priority queue, C++ gives priority to highest value
	whereas Java gives priority to lowest value.

	A priority queue is a type of queue that arranges elements based on their priority
	values. Elements with higher priority values are typically retrieved before elements
	with lower priority values.

	So, a priority Queue is an extension of the queue with the following properties:
    - Every item has a priority associated with it.
    - An element with high priority is dequeued before an element with low priority.
    - If two elements have the same priority, they are served according to their order in the queue.

	How to Implement Priority Queue? 
	Priority queue can be implemented using the following data structures: 
		Arrays
		Linked list
		Heap data structure
		Binary search tree

	Implement Priority Queue Using Array: 
	A simple implementation is to use an array of the following structure. 
    struct item {
            int item;
            int priority;
    }

	Time Complexity Arrays 
	enqueue(): O(1)
	dequeue(): O(n)
	peek(): O(n)

	See link for implementing with other data structures...

	Applications of Priority Queue: 
		CPU Scheduling
		Graph algorithms like Dijkstra’s shortest path algorithm, Prim’s Minimum Spanning Tree, etc.
		Stack Implementation
		All queue applications where priority is involved.
		Data compression in Huffman code
		Event-driven simulation such as customers waiting in a queue.
		Finding Kth largest/smallest element.

	Advantages of Priority Queue:
		It helps to access the elements in a faster way. This is because elements in a
		priority queue are ordered by priority, one can easily retrieve the highest
		priority element without having to search through the entire queue.
		The ordering of elements in a Priority Queue is done dynamically. Elements in a
		priority queue can have their priority values updated, which allows the queue to
		dynamically reorder itself as priorities change.
		Efficient algorithms can be implemented. Priority queues are used in many
		algorithms to improve their efficiency, such as Dijkstra’s algorithm for finding
		the shortest path in a graph and the A* search algorithm for pathfinding.
		Included in real-time systems. This is because priority queues allow you to
		quickly retrieve the highest priority element, they are often used in real-time
		systems where time is of the essence.

	Disadvantages of Priority Queue:
		High complexity. Priority queues are more complex than simple data structures like
		arrays and linked lists, and may be more difficult to implement and maintain.
		High consumption of memory. Storing the priority value for each element in a
		priority queue can take up additional memory, which may be a concern in systems
		with limited resources.
		It is not always the most efficient data structure. In some cases, other data
		structures like heaps or binary search trees may be more efficient for certain
		operations, such as finding the minimum or maximum element in the queue.
		At times it is less predictable:. This is because the order of elements in a
		priority queue is determined by their priority values, the order in which elements
		are retrieved may be less predictable than with other data structures like stacks
		or queues, which follow a first-in, first-out (FIFO) or last-in, first-out (LIFO)
		order.
*/

// Structure for the elements in the
// priority queue
struct item {
	int value;
	int priority;
};

// Store the element of a priority queue
item pr[100000];

// Pointer to the last index
int size = -1;

// Function to insert a new element
// into priority queue
void enqueue(int value, int priority)
{
	// Increase the size
	size++;

	// Insert the element
	pr[size].value = value;
	pr[size].priority = priority;
}

// Function to check the top element
int peek()
{
	int highestPriority = INT_MIN;
	int ind = -1;

	// Check for the element with
	// highest priority
	for (int i = 0; i <= size; i++) {

		// If priority is same choose
		// the element with the
		// highest value
		if (highestPriority == pr[i].priority && ind > -1
			&& pr[ind].value < pr[i].value) {
			highestPriority = pr[i].priority;
			ind = i;
		}
		else if (highestPriority < pr[i].priority) {
			highestPriority = pr[i].priority;
			ind = i;
		}
	}

	// Return position of the element
	return ind;
}

// Function to remove the element with
// the highest priority
void dequeue()
{
	// Find the position of the element
	// with highest priority
	int ind = peek();

	// Shift the element one index before
	// from the position of the element
	// with highest priority is found
	for (int i = ind; i < size; i++) {
		pr[i] = pr[i + 1];
	}

	// Decrease the size of the
	// priority queue by one
	size--;
}

// Driver Code
int main()
{
	// Function Call to insert elements
	// as per the priority
	enqueue(10, 2);
	enqueue(14, 4);
	enqueue(16, 4);
	enqueue(12, 3);

	// Stores the top element
	// at the moment
	int ind = peek();

	cout << pr[ind].value << endl;

	// Dequeue the top element
	dequeue();

	// Check the top element
	ind = peek();
	cout << pr[ind].value << endl;

	// Dequeue the top element
	dequeue();

	// Check the top element
	ind = peek();
	cout << pr[ind].value << endl;

	return 0;
}
