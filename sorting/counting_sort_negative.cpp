#include <bits/stdc++.h>

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

	Counting Sort for an Array with negative elements:
	To solve the problem follow the below idea:
	The problem with the previous counting sort was that we could not sort the elements if
	we have negative numbers in them. Because there are no negative array indices. 

	So what we do is, find the minimum element and we will store the count of that minimum
	element at the zero index

	Time complexity: O(N), where N is the total number of elements
	Auxiliary Space: O(N)
*/

void countSort(vector<int>& arr)
{
	int max = *max_element(arr.begin(), arr.end());
	int min = *min_element(arr.begin(), arr.end());
	int range = max - min + 1;

	vector<int> count(range), output(arr.size());
	for (int i = 0; i < arr.size(); i++)
		count[arr[i] - min]++;

	for (int i = 1; i < count.size(); i++)
		count[i] += count[i - 1];

	for (int i = arr.size() - 1; i >= 0; i--) {
		output[count[arr[i] - min] - 1] = arr[i];
		count[arr[i] - min]--;
	}

	for (int i = 0; i < arr.size(); i++)
		arr[i] = output[i];
}

void printArray(vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << "\n";
}

// Driver code
int main()
{
	vector<int> arr = { -5, -10, 0, -3, 8, 5, -1, 10 };

	// Function call
	countSort(arr);
	printArray(arr);
	return 0;
}
