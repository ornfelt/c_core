# https://www.geeksforgeeks.org/insertion-in-linked-list/

"""
	In this post, methods to insert a new node in the linked list are discussed. A node can be added in three ways 
    - At the front of the linked list  
    - After a given node. 
    - At the end of the linked list.

	Method by using a constructor call to reduce memory allocation work and code lines.

	Time Complexity: O(N) 
	Auxiliary Space: O(1)
"""

# Node class
class Node:

	# A constructor is called here
	def __init__(self, data):
		self.data = data # Automatically assign data
		self.next = None # Initialize next pointer as null


# Linked List class contains a Node object
class LinkedList:

	# Function to initialize head
	def __init__(self):
		self.head = None

	'''This function is in LinkedList class.
	It inserts a new node at the beginning'''
	def insertAtHead(self, new_data):

		# 1 & 2: Allocate the Node &
		#	 Put in the data
		new_node = Node(new_data)

		# 3. Make next of new Node as head
		new_node.next = self.head

		# 4. Move the head to point to new Node
		self.head = new_node

	'''This function is in LinkedList class. It inserts a
	new node after the given prev_data. This method is
	defined inside LinkedList class shown above'''
	def insertAfter(self, prev_data, new_data):

		# 1. check if the Linked List is empty or not
		if self.head is None:
			return

		# 2. Create new node & Put in the data
		new_node = Node(new_data)

		# 3. If prev_data is at the first position
		if (prev_data == self.head.data):
			new_node.next = self.head.next
			self.head.next = new_node
			return

		# 4. check if the given prev_data exists
		head = self.head
		while (head.data != prev_data):
			head = head.next
			if head == None:
				return
		new_node.next = head.next
		head.next = new_node

	'''This function is defined in Linked List class
	Appends a new node at the end. This method is
	defined inside LinkedList class shown above'''
	def insertattail(self, new_data):

		# 1. Create a new node
		# 2. Put in the data
		# 3. Set next as None
		new_node = Node(new_data)

		# 4. If the Linked List is empty, then make the
		# new node as head
		if self.head is None:
			self.head = new_node
			return

		# 5. Else traverse till the last node
		last = self.head
		while (last.next):
			last = last.next

		# 6. Change the next of last node
		last.next = new_node

	# Utility function to print the linked list
	def printList(self):
		temp = self.head
		while (temp):
			print(temp.data, end=" -> ")
			temp = temp.next
		print("NULL")


# Code execution starts here
if __name__ == '__main__':

	# Start with the empty list
	llist = LinkedList()

	llist.insertAtHead(1)
	llist.insertAtHead(2)
	print("After insertion at head:", end=" ")
	llist.printList()
	print()

	llist.insertattail(4)
	llist.insertattail(5)
	print("After insertion at tail:", end=" ")
	llist.printList()
	print()

	llist.insertAfter(1, 2)
	llist.insertAfter(5, 6)
	print("After insertion at a given position:", end=" ")
	llist.printList()
