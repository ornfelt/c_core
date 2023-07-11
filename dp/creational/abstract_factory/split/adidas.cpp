#include <iostream>
#include "iSportsFactory.h"
#include "iShoe.h"
#include "adidasShoe.cpp"
#include "adidasShirt.cpp"

using namespace std;

/**
 * Each Concrete Factory has a corresponding product variant.
 */
class AdidasFactory : public AbstractFactory {
	public:
		shoe *makeShoe() const override {
			return new AdidasShoe();
		}
		Shirt *makeShirt() const override {
			return new AdidasShirt();
		}
};
