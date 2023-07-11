// C++ program to implement
// the above approach
#include <bits/stdc++.h>
using namespace std;

// Stored lambda expression
auto cmp = [](int& a, int& b) {
	return a > b;
};

// Driver code
int main()
{
	int arr[] = { 5, 2, 3, 1, 4 };
	sort(arr, arr + 5, cmp);

	for (int i = 0; i < 5; i++)
		cout << arr[i] << " ";

	return 0;
}
