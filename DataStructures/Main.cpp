#include <iostream>

#include "Array.h"
#include "Vector.h"

// Struct used for testing. Mathematical 3-component vector
struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_memoryBlock = nullptr;

	Vector3()
	{
		m_memoryBlock = new int[5];
	}
	Vector3(float scalar) : x(scalar), y(scalar), z(scalar)
	{
		m_memoryBlock = new int[5];
	}
	Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{
		m_memoryBlock = new int[5];
	}

	// Copy constructor
	//Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z)
	//{
	//	// m_memoryBlock should be copied here aswell, but this isn't used currently
	//	std::cout << "Copy\n";
	//}
	// To demonstrate that the copy constructor isn't used, you can delete it:
	Vector3(const Vector3& other) = delete;

	// Move constructor
	Vector3(Vector3&& other) : x(other.x), y(other.y), z(other.z)
	{
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
		std::cout << "Move\n";
	}

	// Destructor
	~Vector3()
	{
		std::cout << "Destroy\n";
		delete[] m_memoryBlock;
	}

	// Assignment operator
	//Vector3& operator=(const Vector3& other)
	//{
	//	std::cout << "Copy\n";
	//	x = other.x;
	//	y = other.y;
	//	z = other.z;
	//	return *this;
	//}
	// To demonstrate that the copy assignment operator isn't used, you can delete it:
	Vector3& operator=(const Vector3& other) = delete;

	// Move operator
	Vector3& operator=(Vector3&& other)
	{
		m_memoryBlock = other.m_memoryBlock;
		other.m_memoryBlock = nullptr;
		std::cout << "Move\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

template<typename T>
void PrintVector(const Vector<T>& vec)
{
	std::cout << "------------------------------" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
	std::cout << "------------------------------" << std::endl;
}

void PrintVector(const Vector<Vector3>& vec)
{
	std::cout << "------------------------------" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i].x << ", " << vec[i].y << ", " << vec[i].z << std::endl;
	std::cout << "------------------------------" << std::endl;
}

int main()
//int mainVec()
{
	// Test cases
	Array<std::string, 2> arrData;
	arrData[0] = "Cherno";
	arrData[1] = "C++";

	for (size_t i = 0; i < arrData.size(); i++)
		std::cout << arrData[i] << std::endl;

	Vector<std::string> vecData;
	vecData.push_back("Cherno");
	vecData.push_back("C++");
	vecData.push_back("Vector");
	vecData.push_back("Vector");
	vecData.push_back("Vector");
	vecData.push_back("Vector");
	vecData.push_back("Vector");
	vecData.push_back("Vector");
	vecData.push_back("Vector");
	PrintVector(vecData);

	Vector<Vector3> vecDataComplex;
	vecDataComplex.push_back({Vector3(1.0f)}); // Scalar
	vecDataComplex.push_back({Vector3(2, 3, 4)}); // x,y,z
	vecDataComplex.push_back({Vector3()}); // Default constructor
	// The pushbacks will lead to these prints: copy, destroy, copy, copy, destroy, destroy, copy, destroy
	// We will now try to reduce the copys and destroys...
	// If we're using just three floats like in Vector3 (12 bytes), it won't be worth (noticeable) optimizing it, 
	// but think of Vector3 as potentially a string or something stored on the heap. Then we have to reallocate the heap allocation 
	// somehwere else and then free the old one when copying (not good for performance).
	// To improve on this, we add a new push_back function (see Vector.h):
	// void push_back(T&& value) // Takes rvalue reference
	// The above pushbacks will use the new push_back function since they are rvalues.
	// Now we will have no copys!
	PrintVector(vecDataComplex);

	std::cout << "\n";
	// We should also add emplace_back that, instead of constructing the Vector3 instance above in the stack frame of main and 
	// moving it into the data storage of the vector, emplace_back takes the arguments necessary for constructing the instance 
	// and does it emplace in the data block.
	// With emplace_back we take the arguments required only:
	// #BUGFIX
	// There's a bug where the heap allocated memoryblock in Vector3 will be deleted twice. It's deleted in ~Vector3, but then also in ~Vector
	// To fix the bug, we change the way we allocate and deallocate memory, see #BUGFIX in vector.h
	// Surround in scope to demonstrate deletion of the Vector:
	{
		Vector<Vector3> vecDataEmplace;
		// See emplace_back in Vector.h
		vecDataEmplace.emplace_back(1.0f);
		vecDataEmplace.emplace_back(2, 3, 4);
		vecDataEmplace.emplace_back(1, 3, 4);
		vecDataEmplace.emplace_back();
		PrintVector(vecDataEmplace);
		vecDataEmplace.PopBack();
		vecDataEmplace.PopBack();
		PrintVector(vecDataEmplace);
		vecDataEmplace.emplace_back(5, 2, 0);
		vecDataEmplace.emplace_back(1, 7, 9);
		PrintVector(vecDataEmplace);

		vecDataEmplace.clear();
		PrintVector(vecDataEmplace);
		vecDataEmplace.emplace_back(5, 2, 0);
		vecDataEmplace.emplace_back(1, 7, 9);
		PrintVector(vecDataEmplace);
		// See push_back vs emplace_back in Vector.h
	}

	std::cout << "\n";
	// If you have pointers in your Vector, then you need to delete them also...
	//Vector<Vector3*> vecDataPointer;
	//Vector<std::unique_ptr<Vector3>> vecDataPointer;
	//vecDataPointer.emplace_back(std::make_unique<Vector3>(1.0f));
	//vecDataPointer.emplace_back(std::make_unique<Vector3>(2, 3, 4));
	//vecDataPointer.emplace_back(std::make_unique<Vector3>(1, 3, 4));
	//vecDataPointer.emplace_back(std::make_unique<Vector3>());
	//PrintVector(vecDataPointer);

	// Test with primitive types:
	Vector<int> intVector;
	intVector.push_back(5);
	intVector.emplace_back(2);
	intVector.emplace_back(2);
	intVector.emplace_back(2);
	intVector.emplace_back(2);
	PrintVector(intVector);
	intVector.PopBack();
	PrintVector(intVector);
	intVector.clear();

	// TODO: erasing elements, pushing into the middle of the vector (not recommended with vector), iterators, etc...

	std::cin.get();

	return 0;
}
