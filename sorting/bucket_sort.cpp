#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// https://www.geeksforgeeks.org/bucket-sort-2/

/**
	Bucket sort is mainly useful when input is uniformly distributed over a range. For
	example, consider the following problem. Sort a large set of floating point numbers
	which are in range from 0.0 to 1.0 and are uniformly distributed across the range. How
	do we sort the numbers efficiently? A simple way is to apply a comparison based
	sorting algorithm. The lower bound for Comparison based sorting algorithm (Merge Sort,
	Heap Sort, Quick-Sort .. etc) is Ω(n Log n), i.e., they cannot do better than nLogn. 

	Can we sort the array in linear time? Counting sort can not be applied here as we use
	keys as index in counting sort. Here keys are floating point numbers.  The idea is to
	use bucket sort. Following is bucket algorithm.

	Time Complexity: If we assume that insertion in a bucket takes O(1) time then steps 1
	and 2 of the above algorithm clearly take O(n) time. The O(1) is easily possible if we
	use a linked list to represent a bucket (In the following code, C++ vector is used for
	simplicity). Step 4 also takes O(n) time as there will be n items in all buckets. 
	The main step to analyze is step 3. This step also takes O(n) time on average if all
	numbers are uniformly distributed (please refer CLRS book for more details)
*/

// Function to sort arr[] of
// size n using bucket sort
void bucketSort(float arr[], int n)
{
	
	// 1) Create n empty buckets
	vector<float> b[n];

	// 2) Put array elements
	// in different buckets
	for (int i = 0; i < n; i++) {
		int bi = n * arr[i]; // Index in bucket
		b[bi].push_back(arr[i]);
	}

	// 3) Sort individual buckets
	for (int i = 0; i < n; i++)
		sort(b[i].begin(), b[i].end());

	// 4) Concatenate all buckets into arr[]
	int index = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < b[i].size(); j++)
			arr[index++] = b[i][j];
}

/**
	Bucket Sort for numbers having integer part
	Time Complexity:
	The time complexity of bucket sort is O(n + k), where n is the number of elements and
	k is the number of buckets. 

	Auxiliary Space:
	The Auxiliary Space of bucket sort is O(n + k). This is because we need to create a
	new array of size k to store the buckets and another array of size n to store the
	sorted elements.
*/
void bucketSortV2(vector<double>& arr, int noOfBuckets)
{
  double max_ele = *max_element(arr.begin(), arr.end());
  double min_ele = *min_element(arr.begin(), arr.end());
 
  // range (for buckets)
  double rnge = (max_ele - min_ele) / noOfBuckets;
 
  vector<vector<double> > temp;
 
  // create empty buckets
  for (int i = 0; i < noOfBuckets; i++) {
    temp.push_back(vector<double>());
  }
 
  // scatter the array elements into the correct bucket
  for (int i = 0; i < arr.size(); i++) {
    double diff = (arr[i] - min_ele) / rnge
      - int((arr[i] - min_ele) / rnge);
 
    // append the boundary elements to the lower array
    if (diff == 0 && arr[i] != min_ele) {
      temp[int((arr[i] - min_ele) / rnge) - 1]
        .push_back(arr[i]);
    }
    else {
      temp[int((arr[i] - min_ele) / rnge)].push_back(
        arr[i]);
    }
  }
 
  // Sort each bucket individually
  for (int i = 0; i < temp.size(); i++) {
    if (!temp[i].empty()) {
      sort(temp[i].begin(), temp[i].end());
    }
  }
 
  // Gather sorted elements to the original array
  int k = 0;
  for (vector<double>& lst : temp) {
    if (!lst.empty()) {
      for (double i : lst) {
        arr[k] = i;
        k++;
      }
    }
  }
}

/* Driver program to test above function */
int main()
{
	float arr[] = { 0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434 };
	int n = sizeof(arr) / sizeof(arr[0]);
	bucketSort(arr, n);

	cout << "Sorted array is \n";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";

	// Bucket Sort for numbers having integer part
	vector<double> arrTwo = { 9.8,  0.6, 10.1, 1.9, 3.07,
						3.04, 5.0, 8.0,  4.8, 7.68 };
	int noOfBuckets = 5;
	bucketSortV2(arrTwo, noOfBuckets);
	cout << "\nSorted array: ";
	for (double i : arrTwo) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}
