#include <iostream>
// Dynamic Memory management library
#include <memory>

using namespace std;

/**
https://www.geeksforgeeks.org/smart-pointers-cpp/

unique_ptr:
unique_ptr stores one pointer only. We can assign a different
object by removing the current object from the pointer. 

C++ program to demonstrate the working of unique_ptr
Here we are showing the unique_pointer is pointing to P1.
But, then we remove P1 and assign P2 so the pointer now
points to P2.
*/

class Rectangle {
	int length;
	int breadth;

public:
	Rectangle(int l, int b)
	{
		length = l;
		breadth = b;
	}

	int area() { return length * breadth; }
};

int main()
{
	// Smart Pointer
	unique_ptr<Rectangle> P1(new Rectangle(10, 5));
	cout << P1->area() << endl; // This'll print 50
	
	// unique_ptr<Rectangle> P2(P1);
	unique_ptr<Rectangle> P2;
	P2 = move(P1);

	// This'll print 50
	cout << P2->area() << endl;
	// cout<<P1->area()<<endl;
	
	return 0;
}
