#ifndef ISHOE_H_
#define ISHOE_H_

#include <iostream>

//using namespace std;

// Test struct
struct structShoe {
	int size;
	std::string name;
};

/**
 * Each distinct product of a product family should have a base interface. All
 * variants of the product must implement this interface.
 */
class shoe {
	public:
		virtual ~shoe(){};
		virtual std::string CreateShoe() const = 0;
		virtual std::string CreateCollabShoe(const shoe &collaborator) const = 0;

		virtual void setData(int newData) {};
		virtual int getData() const = 0;

		virtual structShoe getStructShoe() const = 0;
		virtual structShoe* getStructShoePointer() const = 0;
};

#endif
