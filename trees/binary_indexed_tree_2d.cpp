#include <iostream>
#include<bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/two-dimensional-binary-indexed-tree-or-fenwick-tree/

/**
	Binary Indexed Tree or Fenwick Tree:
	Let us consider the following problem to understand Binary Indexed Tree.
	We have an array arr[0 . . . n-1]. We would like to 
	1 Compute the sum of the first i elements. 
	2 Modify the value of a specified element of the array arr[i] = x where 0 <= i <= n-1.
	A simple solution is to run a loop from 0 to i-1 and calculate the sum of the
	elements. To update a value, simply do arr[i] = x. The first operation takes O(n) time
	and the second operation takes O(1) time. Another simple solution is to create an
	extra array and store the sum of the first i-th elements at the i-th index in this new
	array. The sum of a given range can now be calculated in O(1) time, but the update
	operation takes O(n) time now. This works well if there are a large number of query
	operations but a very few number of update operations.

	Could we perform both the query and update operations in O(log n) time? 
	One efficient solution is to use Segment Tree that performs both operations in O(Logn)
	time.
	An alternative solution is Binary Indexed Tree, which also achieves O(Logn) time
	complexity for both operations. Compared with Segment Tree, Binary Indexed Tree
	requires less space and is easier to implement..

	Representation:
	Binary Indexed Tree is represented as an array. Let the array be BITree[]. Each node
	of the Binary Indexed Tree stores the sum of some elements of the input array. The
	size of the Binary Indexed Tree is equal to the size of the input array, denoted as n.
	In the code below, we use a size of n+1 for ease of implementation.

	Construction:
	We initialize all the values in BITree[] as 0. Then we call update() for all the
	indexes, the update() operation is discussed below.

	How does Binary Indexed Tree work? 
	The idea is based on the fact that all positive integers can be represented as the sum
	of powers of 2. For example 19 can be represented as 16 + 2 + 1. Every node of the
	BITree stores the sum of n elements where n is a power of 2. For example, in the first
	diagram above (the diagram for getSum()), the sum of the first 12 elements can be
	obtained by the sum of the last 4 elements (from 9 to 12) plus the sum of 8 elements
	(from 1 to 8). The number of set bits in the binary representation of a number n is
	O(Logn). Therefore, we traverse at-most O(Logn) nodes in both getSum() and update()
	operations. The time complexity of the construction is O(nLogn) as it calls update()
	for all n elements. 

	Two Dimensional Binary Indexed Tree or Fenwick Tree:
	We know that to answer range sum queries on a 1-D array efficiently, binary indexed
	tree (or Fenwick Tree) is the best choice (even better than segment tree due to less
	memory requirements and a little faster than segment tree).
	Can we answer sub-matrix sum queries efficiently using Binary Indexed Tree ?
	The answer is yes. This is possible using a 2D BIT which is nothing but an array of 1D BIT. 
	Algorithm:
	We consider the below example. Suppose we have to find the sum of all numbers inside
	the highlighted area- 

	Time Complexity: 
    Both updateBIT(x, y, val) function and getSum(x, y) function takes O(log(NM)) time.
    Building the 2D BIT takes O(NM log(NM)).
	Since in each of the queries we are calling getSum(x, y) function so answering all the
	Q queries takes O(Q.log(NM)) time.

	Auxiliary Space: O(NM) to store the BIT and the auxiliary array
*/


/* C++ program to implement 2D Binary Indexed Tree

2D BIT is basically a BIT where each element is another BIT.
Updating by adding v on (x, y) means it's effect will be found
throughout the rectangle [(x, y), (max_x, max_y)],
and query for (x, y) gives you the result of the rectangle
[(0, 0), (x, y)], assuming the total rectangle is
[(0, 0), (max_x, max_y)]. So when you query and update on
this BIT,you have to be careful about how many times you are
subtracting a rectangle and adding it. Simple set union formula
works here.

So if you want to get the result of a specific rectangle
[(x1, y1), (x2, y2)], the following steps are necessary:

Query(x1,y1,x2,y2) = getSum(x2, y2)-getSum(x2, y1-1) -
					getSum(x1-1, y2)+getSum(x1-1, y1-1)

Here 'Query(x1,y1,x2,y2)' means the sum of elements enclosed
in the rectangle with bottom-left corner's co-ordinates
(x1, y1) and top-right corner's co-ordinates - (x2, y2)

Constraints -> x1<=x2 and y1<=y2

	/\
y |
	|		 --------(x2,y2)
	|		 |	 |
	|		 |	 |
	|		 |	 |
	|		 ---------
	|	 (x1,y1)
	|
	|___________________________
(0, 0)				 x-->

In this program we have assumed a square matrix. The
program can be easily extended to a rectangular one. */

#define N 4 // N-->max_x and max_y

// A structure to hold the queries
struct Query
{
	int x1, y1; // x and y co-ordinates of bottom left
	int x2, y2; // x and y co-ordinates of top right
};

// A function to update the 2D BIT
void updateBIT(int BIT[][N+1], int x, int y, int val)
{
	for (; x <= N; x += (x & -x))
	{
		// This loop update all the 1D BIT inside the
		// array of 1D BIT = BIT[x]
		for (int yy=y; yy <= N; yy += (yy & -yy))
			BIT[x][yy] += val;
	}
	return;
}

// A function to get sum from (0, 0) to (x, y)
int getSum(int BIT[][N+1], int x, int y)
{
	int sum = 0;

	for(; x > 0; x -= x&-x)
	{
		// This loop sum through all the 1D BIT
		// inside the array of 1D BIT = BIT[x]
		for(int yy=y; yy > 0; yy -= yy&-yy)
		{
			sum += BIT[x][yy];
		}
	}
	return sum;
}

// A function to create an auxiliary matrix
// from the given input matrix
void constructAux(int mat[][N], int aux[][N+1])
{
	// Initialise Auxiliary array to 0
	for (int i=0; i<=N; i++)
		for (int j=0; j<=N; j++)
			aux[i][j] = 0;

	// Construct the Auxiliary Matrix
	for (int j=1; j<=N; j++)
		for (int i=1; i<=N; i++)
			aux[i][j] = mat[N-j][i-1];

	return;
}

// A function to construct a 2D BIT
void construct2DBIT(int mat[][N], int BIT[][N+1])
{
	// Create an auxiliary matrix
	int aux[N+1][N+1];
	constructAux(mat, aux);

	// Initialise the BIT to 0
	for (int i=1; i<=N; i++)
		for (int j=1; j<=N; j++)
			BIT[i][j] = 0;

	for (int j=1; j<=N; j++)
	{
		for (int i=1; i<=N; i++)
		{
			// Creating a 2D-BIT using update function
			// everytime we/ encounter a value in the
			// input 2D-array
			int v1 = getSum(BIT, i, j);
			int v2 = getSum(BIT, i, j-1);
			int v3 = getSum(BIT, i-1, j-1);
			int v4 = getSum(BIT, i-1, j);

			// Assigning a value to a particular element
			// of 2D BIT
			updateBIT(BIT, i, j, aux[i][j]-(v1-v2-v4+v3));
		}
	}

	return;
}

// A function to answer the queries
void answerQueries(Query q[], int m, int BIT[][N+1])
{
	for (int i=0; i<m; i++)
	{
		int x1 = q[i].x1 + 1;
		int y1 = q[i].y1 + 1;
		int x2 = q[i].x2 + 1;
		int y2 = q[i].y2 + 1;

		int ans = getSum(BIT, x2, y2)-getSum(BIT, x2, y1-1)-
				getSum(BIT, x1-1, y2)+getSum(BIT, x1-1, y1-1);

		printf ("Query(%d, %d, %d, %d) = %d\n",
				q[i].x1, q[i].y1, q[i].x2, q[i].y2, ans);
	}
	return;
}

// Driver program
int main()
{
	int mat[N][N] = {{1, 2, 3, 4},
					{5, 3, 8, 1},
					{4, 6, 7, 5},
					{2, 4, 8, 9}};

	// Create a 2D Binary Indexed Tree
	int BIT[N+1][N+1];
	construct2DBIT(mat, BIT);

	/* Queries of the form - x1, y1, x2, y2
	For example the query- {1, 1, 3, 2} means the sub-matrix-
	y
	/\
3 |	 1 2 3 4	 Sub-matrix
2 |	 5 3 8 1	 {1,1,3,2}	 --->	 3 8 1
1 |	 4 6 7 5								 6 7 5
0 |	 2 4 8 9
	|
--|------ 0 1 2 3 ----> x
	|

	Hence sum of the sub-matrix = 3+8+1+6+7+5 = 30

	*/

	Query q[] = {{1, 1, 3, 2}, {2, 3, 3, 3}, {1, 1, 1, 1}};
	int m = sizeof(q)/sizeof(q[0]);

	answerQueries(q, m, BIT);

	return(0);
}
