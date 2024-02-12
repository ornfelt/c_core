// FROM: https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/
// Returning multiple values using Class and Object 

// Modified program using class
#include <stdio.h>

class GreaterSmaller {
public:
	int greater, smaller;
};

GreaterSmaller findGreaterSmaller(int a, int b)
{
	GreaterSmaller s;
	if (a > b) {
		s.greater = a;
		s.smaller = b;
	}
	else {
		s.greater = b;
		s.smaller = a;
	}

	return s;
}

// Driver code
int main()
{
	int x, y;
	GreaterSmaller result;

	printf("Enter two numbers: \n");
	scanf("%d%d", &x, &y);

	// The last two arguments are passed
	// by giving addresses of memory locations
	result = findGreaterSmaller(x, y);
	printf("\nThe greater number is %d and the"
		"smaller number is %d",
		result.greater, result.smaller);

	return 0;
}
