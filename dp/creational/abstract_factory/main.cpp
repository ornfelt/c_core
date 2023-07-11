#include <iostream>

using namespace std;

/**
	Testing abstract factory using a NikeFactory and AdidasFactory.
*/

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
