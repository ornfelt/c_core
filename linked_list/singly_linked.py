# https://www.geeksforgeeks.org/what-is-linked-list/

"""
    Search is O(n) because as data is not stored in contiguous memory locations so we have to traverse one by one.
    Insertion and Deletion are O(1) because we have to just link new nodes for Insertion with the previous 
	and next node and dislink exist nodes for deletion from the previous and next nodes without any traversal.

	Auxiliary Space: O(N) [To store dynamic memory]

	Applications of Linked Lists
		- Linked Lists can be used to implement useful data structures like stacks and queues. 
		- Linked Lists can be used to implement hash tables, each bucket of the hash table can be a linked list. 
		- Linked Lists can be used to implement graphs (Adjacency List representation of graph). 
		- Linked Lists can be used in a refined way in implementing different file systems in one form or another.
"""

# Node class
class Node:

	# Function to initialise the node object
	def __init__(self, data):
		self.data = data # Assign data
		self.next = None # Initialize next as null


# Linked List class contains a Node object
class LinkedList:

	# Function to initialize head
	def __init__(self):
		self.head = None

	# This function prints contents of linked list
	# starting from head
	def printList(self):
		temp = self.head
		while (temp):
			print(temp.data)
			temp = temp.next


# Code execution starts here
if __name__ == '__main__':

	# Start with the empty list
	llist = LinkedList()

	llist.head = Node(1)
	second = Node(2)
	third = Node(3)

	llist.head.next = second # Link first node with second
	second.next = third # Link second node with the third node

	llist.printList()
