#include <bits/stdc++.h>
#include <string.h>

using namespace std;

// https://www.geeksforgeeks.org/counting-sort/

/**
	Counting sort is a sorting technique based on keys between a specific range. It works
	by counting the number of objects having distinct key values (a kind of hashing). Then
	do some arithmetic operations to calculate the position of each object in the output
	sequence. 

	Characteristics of counting sort:
	Counting sort makes assumptions about the data, for example, it assumes that values
	are going to be in the range of 0 to 10 or 10 – 99, etc, Some other assumption
	counting sort makes is input data will be all real numbers.
	Like other algorithms this sorting algorithm is not a comparison-based algorithm, it
	hashes the value in a temporary count array and uses them for sorting.
    It uses a temporary array making it a non-In Place algorithm.

	Time Complexity: O(N + K) where N is the number of elements in the input array and K
	is the range of input. 
	Auxiliary Space: O(N + K)
*/

#define RANGE 255

// The main function that sort
// the given string arr[] in
// alphabetical order
void countSort(char arr[])
{
	// The output character array
	// that will have sorted arr
	char output[strlen(arr)];

	// Create a count array to store count of individual
	// characters and initialize count array as 0
	int count[RANGE + 1], i;
	memset(count, 0, sizeof(count));

	// Store count of each character
	for (i = 0; arr[i]; ++i)
		++count[arr[i]];

	// Change count[i] so that count[i] now contains actual
	// position of this character in output array
	for (i = 1; i <= RANGE; ++i)
		count[i] += count[i - 1];

	// Build the output character array
	for (i = 0; arr[i]; ++i) {
		output[count[arr[i]] - 1] = arr[i];
		--count[arr[i]];
	}

	/*
	For Stable algorithm
	for (i = sizeof(arr)-1; i>=0; --i)
	{
		output[count[arr[i]]-1] = arr[i];
		--count[arr[i]];
	}

	For Logic : See implementation
	*/

	// Copy the output array to arr, so that arr now
	// contains sorted characters
	for (i = 0; arr[i]; ++i)
		arr[i] = output[i];
}

// Driver code
int main()
{
	char arr[] = "geeksforgeeks";

	// Function call
	countSort(arr);

	cout << "Sorted character array is " << arr;
	return 0;
}
