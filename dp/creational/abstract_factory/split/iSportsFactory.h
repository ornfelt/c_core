#ifndef ISPORTSFACTORY_H_
#define ISPORTSFACTORY_H_

#include <iostream>
#include "iShirt.h"
#include "iShoe.h"

using namespace std;

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */
class AbstractFactory {
	public:
		virtual shoe *makeShoe() const = 0;
		virtual Shirt *makeShirt() const = 0;
};

#endif
