#include <iostream>
#include "iShoe.h"

using namespace std;

/**
	Testing abstract factory using a NikeFactory and AdidasFactory.
*/

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class NikeShoe : public shoe {
	private:
		int data = 0;

	public:
		std::string CreateShoe() const override {
			return "Created Nike shoe.";
		}

	std::string CreateCollabShoe(const shoe &collaborator) const override {
		const std::string result = collaborator.CreateShoe();
		return "Created Nike shoe collaborating with ( " + result + " )";
	}

	void setData(int newData) override {
		data = newData;
	}

	int getData() const override { return data; }

	structShoe getStructShoe() const override { 
		structShoe newShoe;
		newShoe.name = "Nike shoe x";
		newShoe.size = 32;
		return newShoe;
	};

	structShoe* getStructShoePointer() const override { 
		structShoe* newShoe = new structShoe;
		newShoe->name = "Nike shoe x";
		newShoe->size = 22;
		return newShoe;
	};

};
