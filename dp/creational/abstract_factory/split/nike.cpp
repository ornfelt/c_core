#include <iostream>
#include "iSportsFactory.h"
#include "iShoe.h"
#include "nikeShirt.cpp"
#include "nikeShoe.cpp"

using namespace std;

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 */
class NikeFactory : public AbstractFactory {
	public:
		shoe *makeShoe() const override {
			return new NikeShoe();
		}
		Shirt *makeShirt() const override {
			return new NikeShirt();
		}
};
