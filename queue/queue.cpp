#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/introduction-and-array-implementation-of-queue/

/**
	Similar to Stack, Queue is a linear data structure that follows a particular order in
	which the operations are performed for storing data. The order is First In First Out
	(FIFO).

	Types of Queues: 

	Simple Queue: Simple queue also known as a linear queue is the most basic version of a
	queue. Here, insertion of an element i.e. the Enqueue operation takes place at the
	rear end and removal of an element i.e. the Dequeue operation takes place at the front
	end. Here problem is that if we pop some item from front and then rear reach to the
	capacity of the queue and although there are empty spaces before front means the stack
	is not full but as per condition in isFull() function, it will show that the stack is
	full then. To solve this problem we use circular queue.

	Circular Queue:  In a circular queue, the element of the queue act as a circular ring.
	The working of a circular queue is similar to the linear queue except for the fact
	that the last element is connected to the first element. Its advantage is that the
	memory is utilized in a better way. This is because if there is an empty space i.e. if
	no element is present at a certain position in the queue, then an element can be
	easily added at that position using modulo capacity(%n).

	Priority Queue: This queue is a special type of queue. Its specialty is that it
	arranges the elements in a queue based on some priority. The priority can be something
	where the element with the highest value has the priority so it creates a queue with
	decreasing order of values. The priority can also be such that the element with the
	lowest value gets the highest priority so in turn it creates a queue with increasing
	order of values. In pre-define priority queue, C++ gives priority to highest value
	whereas Java gives priority to lowest value.

	Dequeue: Dequeue is also known as Double Ended Queue. As the name suggests double
	ended, it means that an element can be inserted or removed from both ends of the
	queue, unlike the other queues in which it can be done only from one end. Because of
	this property, it may not obey the First In First Out property. 

	Applications of Queue: 
	Queue is used when things don’t have to be processed immediately, but have to be
	processed in First In First Out order like Breadth First Search. This property of
	Queue makes it also useful in following kind of scenarios:
	- When a resource is shared among multiple consumers. Examples include CPU scheduling,
	Disk Scheduling. 
	- When data is transferred asynchronously (data not necessarily received at same rate
	as sent) between two processes. Examples include IO Buffers, pipes, file IO, etc. 
	- Queue can be used as an essential component in various other data structures.

	Advantages of Array Implementation:  
		- Easy to implement.
		- A large amount of data can be managed efficiently with ease.
		- Operations such as insertion and deletion can be performed with ease as it
		follows the first in first out rule.

	Disadvantages of Array Implementation:  
		- Static Data Structure, fixed size.
		- If the queue has a large number of enqueue and dequeue operations, at some point
		(in case of linear increment of front and rear indexes) we may not be able to
		insert elements in the queue even if the queue is empty (this problem is avoided
		by using circular queue).
		- Maximum size of a queue must be defined prior.

    Time Complexity
	Operations  	Complexity
	Enqueue(insertion) 	O(1)
	Deque(deletion)   	O(1)
	Front(Get front)   	O(1)
	Rear(Get Rear)	O(1)
	IsFull(Check queue is full or not)	O(1)
	IsEmpty(Check queue is empty or not)	O(1)

	Auxiliary Space: 
	O(N) where N is the size of the array for storing elements.
*/

// A structure to represent a queue
class Queue {
public:
	int front, rear, size;
	unsigned capacity;
	int* array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
Queue* createQueue(unsigned capacity)
{
	Queue* queue = new Queue();
	queue->capacity = capacity;
	queue->front = queue->size = 0;

	// This is important, see the enqueue
	queue->rear = capacity - 1;
	queue->array = new int[queue->capacity];
	return queue;
}

// Queue is full when size
// becomes equal to the capacity
int isFull(Queue* queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(Queue* queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(Queue* queue, int item)
{
	if (isFull(queue))
		return;
	queue->rear = (queue->rear + 1)
				% queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
	cout << item << " enqueued to queue\n";
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1)
				% queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

// Function to get front of queue
int front(Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->front];
}

// Function to get rear of queue
int rear(Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->rear];
}

// Driver code
int main()
{
	Queue* queue = createQueue(1000);

	enqueue(queue, 10);
	enqueue(queue, 20);
	enqueue(queue, 30);
	enqueue(queue, 40);

	cout << dequeue(queue)
		<< " dequeued from queue\n";

	cout << "Front item is "
		<< front(queue) << endl;
	cout << "Rear item is "
		<< rear(queue) << endl;

	return 0;
}
