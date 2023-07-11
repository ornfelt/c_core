#include <iostream>
using namespace std;


/**
https://www.geeksforgeeks.org/templates-cpp/

What is the difference between function overloading and templates? 

Both function overloading and templates are examples of polymorphism features of OOP.
Function overloading is used when multiple functions do quite similar (not identical)
operations, templates are used when multiple functions do identical operations.
What happens when there is a static member in a template class/function? 

Each instance of a template contains its own static variable.
Example:

template <typename T>
void fun(const T& x)
{
	static int i = 10;
	cout << ++i;
	return;
}
  
int main()
{    
	fun<int>(1);  // prints 11
	cout << endl;
	fun<int>(2);  // prints 12
	cout << endl;
	fun<double>(1.1); // prints 11
	cout << endl;
	getchar();
	return 0;
}
*/

// One function works for all data types. This would work
// even for user defined types if operator '>' is overloaded
template <typename T> T myMax(T x, T y)
{
	return (x > y) ? x : y;
}

// There can be more than one argument for templates
template <class T, class U> class A {
    T x;
    U y;
 
public:
    A() { cout << "Constructor Called" << endl; }
};

// We can specify a default value for template arguments
template <class T, class U = char> class Z {
public:
    T x;
    U y;
    Z() { cout << "Constructor Called" << endl; }
};


/*
Here is an example to show different data types using a constructor and template. We will
perform a few actions 

* passing character value by creating an object in the main() function.
* passing integer value by creating an object in the main() function.
* passing float value by creating an object in the main() function.
*/
// defining a class template
template <class T> class info {
public:
    // constructor of type template
    info(T A)
    {
        cout << "\n"
             << "A = " << A
             << " size of data in bytes:" << sizeof(A);
    }
    // end of info()
}; // end of class

int main()
{
	// Call myMax for int
	cout << myMax<int>(3, 7) << endl;
	// call myMax for double
	cout << myMax<double>(3.0, 7.0) << endl;
	// call myMax for char
	cout << myMax<char>('g', 'e') << endl;

	// Call more than one arg template
    A<char, char> a;
    A<int, double> b;
    // This will call A<char, char>
    Z<char> z;

    // passing character value by creating an objects
    info<char> p('x');
    // passing integer value by creating an object
    info<int> q(22);
    // passing float value by creating an object
    info<float> r(2.25);

	cout << "\nEnd!" << endl;
	return 0;
}
