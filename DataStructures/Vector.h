#pragma once

template<class T>
//template<typename T>
class Vector
{
public:
	Vector()
	{
		// Allocate 2 elements
		ReAlloc(2);
	}

	~Vector()
	{
		// #BUGFIX 1: Vector destructor will call clear which will go through everything and manually call the destructor
		clear();

		// #BUGFIX 5: Delete without calling destructors. Clear will call the destructors...
		//delete[] m_data;
		::operator delete(m_data, m_capacity * sizeof(T)); // Deleting without calling destructors
	}

	void push_back(const T& value)
	{
		if (m_size >= m_capacity)
			ReAlloc(m_capacity + m_capacity / 2); // Grow by 50 %

		m_data[m_size] = value;
		m_size++;
	}

	void push_back(T&& value) // Takes rvalue reference
	{
		if (m_size >= m_capacity)
			ReAlloc(m_capacity + m_capacity / 2); // Grow by 50 %

		// Instead of assigning m_data, we move the value in there.
		// std::move will cast the value to be a rvalue refrence. 
		// It's technically already a rvalue refrence but there's a 
		// bit of a trick cause as soon as you enter a function 
		// with a parameter like T&&, then it becomes a lvalue. 
		// std::move will make sure that it's handled as an rvalue.

		// #BUGFIX 6: Also need placement new in push_back
		//m_data[m_size] = std::move(value);
		new(&m_data[m_size]) T(std::move(value));
		m_size++;
	}

	// Use variatic templates for emplace_back
	template<typename... Args>
	T& emplace_back(Args&&... args)
	{
		if (m_size >= m_capacity)
			ReAlloc(m_capacity + m_capacity / 2); // Grow by 50 %

		// Construct the Type by forwarding the arguments to the constructor. 
		// The triple dot will unpack the arguments so that the correct constructor is called.
		//m_data[m_size] = T(std::forward<Args>(args)...);
		// push_back vs emplace_back: The line above should be replaced with the following since the push_back and emplace_back basically did the same thing.
		// What we want: we want to construct the object but we want to do it inplace of the memory: m_data[m_size]
		// This is done with placement new where you're providing actual memory for the object to be constructed in. 
		// You grab the memory address of the element where the object is supposed to live, and the forwarded arguments along with the type to be constructed
		new(&m_data[m_size]) T(std::forward<Args>(args)...);
		return m_data[m_size++];
	}

	void PopBack()
	{
		if (m_size > 0)
		{
			m_size--;
			// Explicitly call destructor which will nullify our object and release any resource that it might own
			// At this point you shouldn't have any reference to the popped object
			m_data[m_size].~T();
		}
	}

	void clear()
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i].~T();

		m_size = 0;
	}

	size_t size() const { return m_size; }

	T& operator[] (size_t index)
	{
		//if (index >= m_size)
		//	// assert
		return m_data[index];
	}

	const T& operator[] (size_t index) const
	{
		//if (index >= m_size)
		//	// assert
		return m_data[index];
	}

private:
	void ReAlloc(size_t newCapacity)
	{
		// 1. Allocate a new block of memory. std::vector allows for custom 
		// allocators which can be useful if you're designing software that 
		// needs to perform well and you're giving it an allocator that 
		// won't necessarily hit the heap every time it needs to allocate memory.
		// We will simply use the new operator
		// 2. Copy (move) old elements into new block
		// 3. Delete

		// #BUGFIX 2: We want to change the new and delete operators so that the constructor and destructor aren't called...
		//T* newBlock = new T[newCapacity]; // Can use smart pointer, but you shouldn't if you're this low-level into things...
		// Here we instead just need to malloc enough memory to fill up the newCapacity, we don't actually need to call the constructor.
		// Malloc won't be used since it's C++...
		T* newBlock = (T*)::operator new (newCapacity * sizeof(T)); // (T*) is required since it will return void*
		// We do something similar with delete below.

		// We can't use memcpy instead of the for loop because we need be hitting the copy constructor of all elements.
		// If we only had ints, floats or any kind of primitive type, memcpy is fine, but for complex types like classes 
		// that might have allocations of their own which the copy constructor will then perform a deep copy on - it's 
		// important for us to actually make sure that we're calling that copy constructor, otherwise complex types won't get copied correctly.

		// The for loop below relies on m_size being smaller than the newCapacity. We should therefore add this check to make sure that if we are
		// downsizing, we only copy up to newCapacity size of elements... This might not be the job for ReAlloc, but we'll add it anyways.
		if (newCapacity < m_size)
			m_size = newCapacity;

		for (size_t i = 0; i < m_size; i++)
			// We change this assignment to std::move to cast it to rvalue reference instead,
			// cause if there's no move constructor for the type, it's just going to copy it, so for primitive 
			// types, it's not gonna do anything really.
			// This is preferable since we don't want to copy, but move it. The old m_data is deleted below anyway...
			//newBlock[i] = m_data[i];
			// Last bugfix (other bug...): Since we allocated raw memory above (not calling constructor).
			// This works for primitive types, but for string for example, as a consequence of trying to std::move an existing string into
			// another supposedly existing string (newBlock[i]) it tries to Tidy_deallocate the string in newBlock but nothing exists there (only allocated memory).
			//newBlock[i] = std::move(m_data[i]);
			new (&newBlock[i]) T(std::move(m_data[i])); // Use placement new instead to call the constructor properly and call the move constructor if it exists...

		for (size_t i = 0; i < m_size; i++) // #BUGFIX 4.
			m_data[i].~T();
		// #BUGFIX 3: We want to change the new and delete operators so that the constructor and destructor aren't called...
		//delete[] m_data;
		::operator delete(m_data, m_capacity * sizeof(T)); // Deleting without calling destructors, we however need the destructors to be called in the loop above)

		m_data = newBlock;
		m_capacity = newCapacity;
	}

	T* m_data = nullptr; // nullptr per default
	size_t m_size = 0; // Number of elements inside our vector
	size_t m_capacity = 0; // How much memory we have allocated (how much can we store without having to realloc)
};