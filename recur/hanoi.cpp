// C++ recursive function to
// solve tower of hanoi puzzle
#include <bits/stdc++.h>
using namespace std;

/**
https://www.geeksforgeeks.org/c-program-for-tower-of-hanoi/

The idea is to use the helper node to reach the destination using recursion. Below is the
pattern for this problem:
	Shift ‘N-1’ disks from ‘A’ to ‘B’, using C.
	Shift last disk from ‘A’ to ‘C’.
	Shift ‘N-1’ disks from ‘B’ to ‘C’, using A.

Time complexity: O(2N), There are two possibilities for every disk. Therefore, 2 * 2 * 2 *
. . . * 2(N times) is 2N.
Auxiliary Space: O(N), Function call stack space.
*/

void towerOfHanoi(int n, char from_rod, char to_rod,
				char aux_rod)
{
	if (n == 0) {
		cout << "return 0" << endl;
		return;
	}
	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
	cout << "Move disk " << n << " from rod " << from_rod
		<< " to rod " << to_rod << endl;
	towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

// Driver code
int main()
{
	int N = 3;

	// A, B and C are names of rods
	towerOfHanoi(N, 'A', 'C', 'B');
	return 0;
}

// This is code is contributed by rathbhupendra
