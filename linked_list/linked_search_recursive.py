# https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/

"""
	Given a linked list and a key ‘X‘ in, the task is to check if X is present in the
	linked list or not. 

	Examples:

    Input: 14->21->11->30->10, X = 14
    Output: Yes
    Explanation: 14 is present in the linked list.

    Input: 6->21->17->30->10->8, X = 13
    Output: No

	Search an element in a Linked List (Recursive Approach): 

	Follow the below steps to solve the problem:
		- If the head is NULL, return false.
		- If the head’s key is the same as X, return true;
		- Else recursively search in the next node. 

	Time Complexity: O(N)
	Auxiliary Space: O(N), Stack space used by recursive calls
"""

# Node class
class Node:
	# Function to initialise
	# the node object
	def __init__(self, data):
		self.data = data # Assign data
		self.next = None # Initialize next as null

class LinkedList:
	def __init__(self):
		self.head = None # Initialize head as None

	# This function insert a new node at
	# the beginning of the linked list
	def push(self, new_data):

		# Create a new Node
		new_node = Node(new_data)

		# Make next of new Node as head
		new_node.next = self.head

		# Move the head to
		# point to new Node
		self.head = new_node

	# Checks whether the value key
	# is present in linked list

	def search(self, li, key):

		# Base case
		if(not li):
			return False

		# If key is present in
		# current node, return true
		if(li.data == key):
			return True

		# Recur for remaining list
		return self.search(li.next, key)

# Driver Code
if __name__ == '__main__':

	li = LinkedList()

	li.push(1)
	li.push(2)
	li.push(3)
	li.push(4)

	key = 4

	# Function call
	if li.search(li.head, key):
		print("Yes")
	else:
		print("No")