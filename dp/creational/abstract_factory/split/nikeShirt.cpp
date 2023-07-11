#include <iostream>
#include "iShirt.h"

using namespace std;

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class NikeShirt : public Shirt {
	public:
		std::string CreateShirt() const override {
			return "Created Nike shirt";
		}

		std::string CreateCollabShirt(const Shirt &collaborator) const override {
			const std::string result = collaborator.CreateShirt();
			return "Created Nike Shirt collaborating with ( " + result + " )";
		}
};
