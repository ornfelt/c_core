#include <iostream>
#include "adidas.cpp"
#include "nike.cpp"
#include "iShirt.h"
#include "iShoe.h"

using namespace std;

/**
	Testing abstract factory using a NikeFactory and AdidasFactory.
*/

/**
 * The client code works with factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */
void ClientCode(const AbstractFactory &nikeFactory, const AbstractFactory &adidasFactory) {
	shoe *nikeShoeProduct = nikeFactory.makeShoe();
	Shirt *nikeShirtProduct = nikeFactory.makeShirt();
	shoe *adidasShoeProduct = adidasFactory.makeShoe();
	Shirt *adidasShirtProduct = adidasFactory.makeShirt();

	std::cout << "Testing NikeFactory" << std::endl;
	std::cout << nikeShoeProduct->CreateShoe() << "\n";
	std::cout << nikeShirtProduct->CreateShirt() << "\n";
	std::cout << nikeShoeProduct->CreateCollabShoe(*adidasShoeProduct) << "\n";
	nikeShoeProduct->setData(42);
	std::cout << nikeShoeProduct->getData() << "\n";

	structShoe nikeStructShoe = nikeShoeProduct->getStructShoe();
	std::cout << nikeStructShoe.name << "\n";
	std::cout << nikeStructShoe.size << "\n";

	std::cout << std::endl;
	std::cout << "Testing AdidasFactory" << std::endl;
	std::cout << adidasShoeProduct->CreateShoe() << "\n";
	std::cout << adidasShirtProduct->CreateShirt() << "\n";
	std::cout << adidasShirtProduct->CreateCollabShirt(*nikeShirtProduct) << "\n";
	adidasShoeProduct->setData(43);
	std::cout << adidasShoeProduct->getData() << "\n";

	structShoe adidasStructShoe = adidasShoeProduct->getStructShoe();
	std::cout << adidasStructShoe.name << "\n";
	std::cout << adidasStructShoe.size << "\n";

	std::cout << "\nTesting structshoepointers" << std::endl;
	structShoe* nikeStructShoePointer = nikeShoeProduct->getStructShoePointer();
	std::cout << nikeStructShoePointer->name << "\n";
	std::cout << nikeStructShoePointer->size << "\n";

	structShoe* adidasStructShoePointer = adidasShoeProduct->getStructShoePointer();
	std::cout << adidasStructShoePointer->name << "\n";
	std::cout << adidasStructShoePointer->size << "\n";

	delete nikeStructShoePointer;
	delete adidasStructShoePointer;

	delete nikeShoeProduct;
	delete nikeShirtProduct;
	delete adidasShoeProduct;
	delete adidasShirtProduct;
}

int main() {
	std::cout << "Client: Testing client code:\n";
	NikeFactory *f1 = new NikeFactory();
	AdidasFactory *f2 = new AdidasFactory();
	ClientCode(*f1, *f2);

	delete f1;
	delete f2;
	return 0;
}
