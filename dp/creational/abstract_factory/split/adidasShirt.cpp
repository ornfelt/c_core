#include <iostream>
#include "iShirt.h"

using namespace std;


class AdidasShirt : public Shirt {
	public:
		std::string CreateShirt() const override {
			return "Created Adidas Shirt";
		}

		std::string CreateCollabShirt(const Shirt &collaborator) const override {
			const std::string result = collaborator.CreateShirt();
			return "Created Adidas Shirt collaborating with ( " + result + " )";
		}
};
