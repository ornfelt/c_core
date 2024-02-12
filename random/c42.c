// FROM: https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/
// Modified program using array
#include <stdio.h>

// Store the greater element at 0th index
void findGreaterSmaller(int a, int b, int arr[])
{

	// Store the greater element at
	// 0th index of the array
	if (a > b) {
		arr[0] = a;
		arr[1] = b;
	}
	else {
		arr[0] = b;
		arr[1] = a;
	}
}

// Driver code
int main()
{
	int x, y;
	int arr[2];

	printf("Enter two numbers: \n");
	scanf("%d%d", &x, &y);

	findGreaterSmaller(x, y, arr);

	printf("\nThe greater number is %d and the "
		"smaller number is %d",
		arr[0], arr[1]);

	return 0;
}
