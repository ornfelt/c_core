#include <iostream>
using namespace std;

int main()
{
	struct sSomeObject
	{
		// These ints are used to easier track memory in Visual Studio
		int x = 0xA3A2A1A0;
		int y = 0xB3B2B1B0;
		
		sSomeObject()
		{
			x = 0xC3C2C1C0;
			y = 0xD3D2D1D0;
		}
	};
	
	// Stack allocation (compile time) - works especially if we know how many objects there should be.
	//sSomeObject pSomeObject[10];
	
	// Heap (run time)
	// The pointer pSomeObject points to 0th ele of array of objects (new keyword will return a pointer).
	//sSomeObject *pSomeObject = new sSomeObject[10];
	
	// Create array of pointers allocated at run time. Create pointer to the start of an array of pointers...
	// See pointers_poly.cpp to see why the this is needed somtimes.
	sSomeObject **pSomeObject = new sSomeObject*[10] { 0 };

	for (int i = 0; i < 10; i++)
		pSomeObject[i] = new sSomeObject();
	
	for (int i = 0; i < 10; i++)
		delete pSomeObject[i];
	
	delete[] pSomeObject;
	
	// Something to be vary about:
	char someString[] = "hello!";
	char *pSomeString = someString;
	cout << "pSomeString = " << pSomeString << endl;
	char *pLocation3 = &someString[3];
	char *pLocation0 = &someString[0];
	
	cout << "pLocation3 = " << (int)pLocation3 << endl; // Print memory address
	cout << "pLocation0 = " << (int)pLocation0 << endl; // Print memory address
	cout << "Diff = " << pLocation3 - pLocation0 << endl;
	
	// If we take the (int) casts out, then we instead see "lo!" and hello!
	cout << "pLocation3 = " << pLocation3 << endl; // Print memory address
	cout << "pLocation0 = " << pLocation0 << endl; // Print memory address
	// This is beacuse when you see chars and pointers of chars, it's common that you're actually inferring a string. So many operators for C and C++ that expects to see pointers of type char representing strings, so they do string specific things... That's why pLocation3 (char*) above is treated as a string, that's why we don't see the value of the address unless we cast into (int).
	
	
	cout << endl; system("pause");	return 0;
}