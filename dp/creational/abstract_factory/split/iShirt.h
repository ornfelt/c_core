#ifndef ISHIRT_H_
#define ISHIRT_H_

#include <iostream>

using namespace std;

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 */
class Shirt {
	/**
	 * Product B is able to do its own thing...
	 */
	public:
		virtual ~Shirt(){};
		virtual std::string CreateShirt() const = 0;
		/**
		 * ...but it also can collaborate with the ProductA.
		 *
		 * The Abstract Factory makes sure that all products it creates are of the
		 * same variant and thus, compatible.
		 */
		virtual std::string CreateCollabShirt(const Shirt &collaborator) const = 0;
};

#endif
