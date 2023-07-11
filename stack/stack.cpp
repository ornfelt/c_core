#include <iostream>
#include <stack>
using namespace std;

// https://www.geeksforgeeks.org/stack-in-cpp-stl/

/**
	Stack is a linear data structure that follows a particular order in which the
	operations are performed. The order may be LIFO(Last In First Out) or FILO(First In
	Last Out). LIFO implies that the element that is inserted last, comes out first and
	FILO implies that the element that is inserted first, comes out last.

	Usually LIFO.

	The functions associated with stack are: 
	empty() – Returns whether the stack is empty – Time Complexity : O(1) 
	size() – Returns the size of the stack – Time Complexity : O(1) 
	top() – Returns a reference to the top most element of the stack – Time Complexity : O(1) 
	push(g) – Adds the element ‘g’ at the top of the stack – Time Complexity : O(1) 
	pop() – Deletes the most recent entered element of the stack – Time Complexity : O(1) 
 */

int main() {
	stack<int> stack;
	stack.push(21);// The values pushed in the stack should be of the same data which is written during declaration of stack
	stack.push(22);
	stack.push(24);
	stack.push(25);
	int num=0;
	stack.push(num);
	stack.pop();
	stack.pop();
	stack.pop();
	
	while (!stack.empty()) {
		cout << stack.top() <<" ";
		stack.pop();
	}
}
