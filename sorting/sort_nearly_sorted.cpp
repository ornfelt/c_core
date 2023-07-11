#include <bits/stdc++.h>

using namespace std;

// https://www.geeksforgeeks.org/nearly-sorted-algorithm/

/**
	Given an array of N elements, where each element is at most K away from its target
	position, devise an algorithm that sorts in O(N log K) time.

	Sort a nearly sorted (or K sorted) array using Quick-Sort:

	To solve the problem follow the below idea:

    The algorithm uses quick sort but changes the partition function in 2 ways.
	1. Selects the pivot element as the middle element instead of the first or last
	element.
	2. Scans the array from max(low, mid – k) to min(mid + k, high) instead of low to
	high.

	The middle element is chosen as the pivot for diving the array into almost 2 halves
	for logarithmic time complexity
	
	Time Complexity: O(N * Log N) 
	Auxiliary Space: O(Log N)
*/

int sort(vector<int>& array, int l, int h, int k)
{
	int mid
		= l + (h - l) / 2; // Choose middle element as pivot
	int i = max(l, mid - k), j = i,
		end = min(mid + k, h); // Set appropriate range
	swap(array[mid],
		array[end]); // Swap middle and last element to
					// avoid extra complications
	while (j < end) {
		if (array[j] < array[end]) {
			swap(array[i++], array[j]);
		}
		j = j + 1;
	}
	swap(array[end], array[i]);
	return i;
}

void ksorter(vector<int>& array, int l, int h, int k)
{
	if (l < h) {
		int q = sort(array, l, h, k);
		ksorter(array, l, q - 1, k);
		ksorter(array, q + 1, h, k);
	}
}

// Driver code
int main()
{
	vector<int> array(
		{ 3, 3, 2, 1, 6, 4, 4, 5, 9, 7, 8, 11, 12 });
	int k = 3;
	cout << "Array before K sort\n";
	for (int& num : array)
		cout << num << ' ';
	cout << endl;

	// Function call
	ksorter(array, 0, array.size() - 1, k);
	cout << "Array after K sort\n";
	for (int& num : array)
		cout << num << ' ';
	return 0;
}
