#include <iostream>
// Dynamic Memory management library
#include <memory>

using namespace std;

/**
https://www.geeksforgeeks.org/smart-pointers-cpp/

shared_ptr:
By using shared_ptr more than one pointer can point to 
this one object at a time and it’ll maintain a Reference 
Counter using the use_count() method.

C++ program to demonstrate the working of shared_ptr
Here both smart pointer P1 and P2 are pointing to the
object Adddition to which they both maintain a reference
of the object
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
	shared_ptr<Rectangle> P1(new Rectangle(10, 5));
	// This'll print 50
	cout << P1->area() << endl;

	shared_ptr<Rectangle> P2;
	P2 = P1;

	// This'll print 50
	cout << P2->area() << endl;

	// This'll now NOT give an error,
	cout << P1->area() << endl;

	// This'll print 2 as Reference Counter is 2
	cout << P1.use_count() << endl;
	
	return 0;
}
