#include <iostream>
#include "iShoe.h"

using namespace std;

class AdidasShoe : public shoe {
	private:
		int data = 0;

	std::string CreateShoe() const override {
		return "Created Adidas shoe.";
	}

	std::string CreateCollabShoe(const shoe &collaborator) const override {
		const std::string result = collaborator.CreateShoe();
		return "Created Adidas shoe collaborating with ( " + result + " )";
	}

	void setData(int newData) override {
		data = newData;
	}

	int getData() const override { return data; }

	structShoe getStructShoe() const override { 
		structShoe newShoe;
		newShoe.name = "Adidas shoe x";
		newShoe.size = 33;
		return newShoe;
	};

	structShoe* getStructShoePointer() const override { 
		structShoe* newShoe = new structShoe;
		newShoe->name = "Adidas shoe x";
		newShoe->size = 23;
		return newShoe;
	};
};
