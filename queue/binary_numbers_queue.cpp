#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/interesting-method-generate-binary-numbers-1-n/

/**
	Given a number N, write a function that generates and prints all binary numbers with
	decimal values from 1 to N. 

	Examples: 

    Input: n = 2
    Output: 1, 10

    Input: n = 5
    Output: 1, 10, 11, 100, 101

	Naive Method: To solve the problem follow the below idea:
	A simple method is to run a loop from 1 to n, and call decimal to binary inside the
	loop. 

	Generate Binary Numbers from 1 to n using the queue:

	Follow the given steps to solve the problem:

    - Create an empty queue of strings 
    - Enqueue the first binary number “1” to the queue. 
    - Now run a loop for generating and printing n binary numbers. 
        Dequeue and Print the front of queue. 
        Append “0” at the end of front item and enqueue it. 
        Append “1” at the end of front item and enqueue it.

	Time Complexity: O(N) 
	Auxiliary Space: O(N) as extra space is required in this method
*/

// This function uses queue data structure to print binary
// numbers
void generatePrintBinary(int n)
{
	// Create an empty queue of strings
	queue<string> q;

	// Enqueue the first binary number
	q.push("1");

	// This loops is like BFS of a tree with 1 as root
	// 0 as left child and 1 as right child and so on
	while (n--) {
		// print the front of queue
		string s1 = q.front();
		q.pop();
		cout << s1 << "\n";

		string s2 = s1; // Store s1 before changing it

		// Append "0" to s1 and enqueue it
		q.push(s1.append("0"));

		// Append "1" to s2 and enqueue it. Note that s2
		// contains the previous front
		q.push(s2.append("1"));
	}
}

// Driver code
int main()
{
	//int n = 10;
	int n = 1000;

	// Function call
	generatePrintBinary(n);
	return 0;
}
