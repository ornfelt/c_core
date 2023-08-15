#include <iostream>
#include <array>

// Creating a stack allocated array

// Custom Array class
template<typename T, size_t S>
class Array
{
public:
	//Array(int size) // Use this for alloca
	//{
		// Dynamically allocate memory on stack with alloca (use int* m_data; below)
		//m_data = (int*)alloca(size * sizeof(int)); // Alloca takes size in bytes
	//}

	constexpr size_t size() const { return S; }

	// Index operator
	// Simple version where T is returned by value.
	// This is a problem if we have an array of strings for example, 
	// where the string would be copied every time we use the operator.
	// Also, we can't modify the value (myData[i] = 2 for example)
	//T operator[](size_t index) { return m_data[index]; }

	// Return reference instead. This however present the problem of:
	// if the our array variable happens to be const for whatever reason (maybe we're using a const reference for example):
	// Array<int, 5> myData;
	// const auto& arrayRef = myData;
	// We can't do this since we're then trying to modify the const ref:
	// arrayRef[0] = 2;
	// However, we also can't access it which is a problem since const applies that it's readonly:
	// std::cout << arrayRef[0] << std::endl;
	T& operator[](size_t index) { return m_data[index]; }

	// We fix this by adding another version of the function marked as const
	// The second const means that we can call the function if the instance of Array is const (like arrayRef above)
	const T& operator[](size_t index) const { return m_data[index]; }

	// The std version includes a preprocessor statement:
	// #if _CONTAINER_DEBUG_LEVEL > 0
	// _STL_VERIFY(_Pos < _Size, "array subscript out of range");
	// #endif // _CONTAINER_DEBUG_LEVEL > 0
	// return _Elems[_Pos];
	// We can do something similar if we want:
	//T& operator[](size_t index) 
	//{ 
	//	//if (!(index < S))
	//	//	_debugbreak(); // MSVC way of breaking compiler at this line
	//	return m_data[index]; 
	//}
	// The above isn't usually included in release mode however, since it should be caught in debug mode

	// Finally, we need to be able to access the data within the Array
	T* data() { return m_data; }
	const T* data() const { return m_data; }
	// This enables us to set the data using memset for example:
	// Set all the ints in the Array to 0 via setting all their memories to 0
	//memset(myData.data(), 0, myData.size() * sizeof(int));
	// You can also do this version size the stack allocated Array is contiguous in memory
	//memset(&myData[0], 0, myData.size() * sizeof(int));

private:
	//int* m_data;
	T m_data[S]; // Dynamic size with template argument
};

//int main()
int mainArr()
{
	// Without any custom class / helper functions 
	int stackArray[5]; // Stack allocated
	// With the heap allocated array we can dynamically set the size:
	int size = 5;
	int* heapArray = new int[size]; // Heap allocated
	delete[] heapArray; // stackArray gets deleted automatically when stack frame is popped

	// Standard array from C++ 11 (required #include <array>)
	// Templated class. You can right click #include <array> -> Go to document to see implementation
	std::array<int, 10> stdArray;
	// Iterating over std::array
	//for (int i : stdArray)
	for (int i = 0; i < stdArray.size(); i++)
		std::cout << stdArray[i] << std::endl;

	// Custom Array class
	// Array data(size); // This works with alloca version
	Array<int, 5> myData;
	memset(myData.data(), 0, myData.size() * sizeof(int));
	myData[3] = 5;

	// Static assert is evaluated at compile time. Requires size() to be constexpr so that it can be evaluated at compile time
	static_assert(myData.size() < 10, "Size is too large!");

	// Printing data via [] operator
	for (size_t i = 0; i < myData.size(); i++)
		std::cout << myData[i] << std::endl;
	// We can also add iterators, fill, swap, etc in the future...

	return 0;
}