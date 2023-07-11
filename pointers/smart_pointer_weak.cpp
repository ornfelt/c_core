#include <iostream>
// Dynamic Memory management library
#include <memory>

using namespace std;

/**
https://www.geeksforgeeks.org/smart-pointers-cpp/
https://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful

weak_ptr:
Weak_ptr is a smart pointer that holds a non-owning 
reference to an object. It’s much more similar to 
shared_ptr except it’ll not maintain a Reference 
Counter. In this case, a pointer will not have a 
stronghold on the object. The reason is if suppose
pointers are holding the object and requesting 
for other objects then they may form a Deadlock.
*/

int main()
{
	// OLD, problem with dangling pointer
	// PROBLEM: ref will point to undefined data!
	int* ptr = new int(10);
	int* ref = ptr;
	delete ptr;

	// NEW SOLUTION: check expired() or lock() to determine if pointer is valid
	// Empty definition
	std::shared_ptr<int> sptr;

	// Takes ownership of pointer
	sptr.reset(new int);
	*sptr = 10;

	// Get pointer to data without taking ownership
	std::weak_ptr<int> weak1 = sptr;

	// Deletes managed object, acquires new pointer
	sptr.reset(new int);
	*sptr = 5;

	// Get pointer to new data without taking ownership
	std::weak_ptr<int> weak2 = sptr;

	// weak1 is expired!
	if(auto tmp = weak1.lock())
		std::cout << "weak1 value is " << *tmp << '\n';
	else
		std::cout << "weak1 is expired\n";

	// weak2 points to new data (5)
	if(auto tmp = weak2.lock())
		std::cout << "weak2 value is " << *tmp << '\n';
	else
		std::cout << "weak2 is expired\n";
}
