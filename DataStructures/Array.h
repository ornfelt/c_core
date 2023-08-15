#pragma once

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