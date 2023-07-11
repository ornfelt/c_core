#include <iostream>
#include <stdio.h>

using namespace std;

class Car {
	public:
	int speed(int maxSpeed);
};

int Car::speed(int maxSpeed) {
	return maxSpeed;
}


void swapnum(int &i, int &j) {
	int temp = i;
	i = j;
	j = temp;
}

int main() {
	int a = 10;
	int b = 20;
	swapnum(a, b);
	printf("A is %d and B is %d\n", a, b);

	Car myObj; // Create an object of Car
	cout << myObj.speed(200); // Call the method with an argument
	return 0;
}
