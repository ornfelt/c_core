#include <iostream>
#include <list>
#include <string>

/**
 * The Abstract Class defines a template method that contains a skeleton of some
 * algorithm, composed of calls to (usually) abstract primitive operations.
 *
 * Concrete subclasses should implement these operations, but leave the template
 * method itself intact.
 */
class DataAccessor {
	/**
	 * The template method defines the skeleton of an algorithm.
	 */
	public:
		void TemplateMethod() {
			this->Connect();
			this->Select();
			this->Hook1();
			this->Process();
			this->Disconnect();
			this->Hook2();
		}
		/**
		 * These operations already have implementations.
		 */
	protected:
		//void Connect() const {
		//	std::cout << "DataAccessor says: I am doing the bulk of the work\n But I let subclasses override some operations...\n";
		//}

		/**
		 * These operations have to be implemented in subclasses.
		 */
		virtual void Connect() const = 0;
		virtual void Select() = 0;
		virtual void Process() = 0;
		virtual void Disconnect() = 0;
		/**
		 * These are "hooks." Subclasses may override them, but it's not mandatory
		 * since the hooks already have default (but empty) implementation. Hooks
		 * provide additional extension points in some crucial places of the
		 * algorithm.
		 */
		virtual void Hook1() const {}
		virtual void Hook2() const {}
};

/**
 * Concrete classes have to implement all abstract operations of the base class.
 * They can also override some operations with a default implementation.
 */
class Categories : public DataAccessor {
	protected:
		std::list<std::string> categories;

		void Connect() const override {
			std::cout << "Categories says: Connected. Initiliazing stuff...\n";
		}

		void Select() override {
			categories.push_back("Red");
            categories.push_back("Green");
            categories.push_back("Blue");
            categories.push_back("Yellow");
            categories.push_back("Purple");
            categories.push_back("White");
            categories.push_back("Black");
		}

		void Hook1() const override {
			std::cout << "Categories says: Overridden Hook1\n";
		}

		void Process() override {
			std::cout << "Processing categories:" << std::endl;
			std::list<std::string>::iterator it = categories.begin();
			while (it != categories.end()) {
				std::cout << "categories: " << (*it) << std::endl;
				++it;
			}
		}

		void Disconnect() override {
			std::cout << "Clearing categories";
			categories.clear();
		}
};
/**
 * Usually, concrete classes override only a fraction of base class' operations.
 */
class Products : public DataAccessor {
	protected:
		std::list<std::string> products;

		void Connect() const override {
			std::cout << "Products says: Connected. Initiliazing stuff...\n";
		}

		void Select() override {
            products.push_back("Car");
            products.push_back("Bike");
            products.push_back("Boat");
            products.push_back("Truck");
            products.push_back("Moped");
            products.push_back("Rollerskate");
            products.push_back("Stroller");
		}

		void Hook1() const override {
			std::cout << "Products says: Overridden Hook1\n";
		}

		void Process() override {
			std::cout << "Processing products:" << std::endl;
			std::list<std::string>::iterator it = products.begin();
			while (it != products.end()) {
				std::cout << "product: " << (*it) << std::endl;
				++it;
			}
		}

		void Disconnect() override {
			std::cout << "Clearing products:" << std::endl;
			products.clear();
		}

		void Hook2() const override {
			std::cout << "Products says: Overridden Hook2\n";
		}
};

/**
 * The client code calls the template method to execute the algorithm. Client
 * code does not have to know the concrete class of an object it works with, as
 * long as it works with objects through the interface of their base class.
 */
void ClientCode(DataAccessor *class_) {
	// ...
	class_->TemplateMethod();
	// ...
}

int main() {
	std::cout << "Same client code can work with different subclasses:\n\n";
	Categories *concreteClass1 = new Categories;
	ClientCode(concreteClass1);
	std::cout << "\n\n";

	std::cout << "Same client code can work with different subclasses:\n\n";
	Products *concreteClass2 = new Products;
	ClientCode(concreteClass2);

	delete concreteClass1;
	delete concreteClass2;
	
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}
