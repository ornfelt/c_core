#include <iostream>
#include <array>

/**
 * The IVisitor Interface declares a set of visiting methods that correspond to
 * component classes. The signature of a visiting method allows the visitor to
 * identify the exact class of the component that it's dealing with.
 */
class Employee;

class IVisitor {
	public:
		virtual void Visit(Employee* const element) = 0;
};

/**
 * The Element interface declares an `accept` method that should take the base
 * visitor interface as an argument.
 */
class Element {
	public:
		virtual ~Element() {}
		virtual void Accept(IVisitor* const visitor) = 0;
};

/**
 * Each Concrete Element must implement the `Accept` method in such a way that
 * it calls the visitor's method corresponding to the component's class.
 */
class Employee : public Element {
	protected:
		std::string name_;
		double income_;
		unsigned int vacationDays_;

	public:
		Employee(std::string name, double income, unsigned int vacationDays) : name_(name), income_(income), vacationDays_(vacationDays) {
		}

		void Accept(IVisitor* const visitor) override {
			visitor->Visit(this);
		}
		/**
		 * Concrete Components may have special methods that don't exist in their base
		 * class or interface. The IVisitor is still able to use these methods since
		 * it's aware of the component's concrete class.
		 */
		std::string GetInfo() const {
			return "Employee info: " + name_ + ", " + std::to_string(income_) + ", " + std::to_string(vacationDays_);
		}

		// Getters and setters
		const std::string name() const { return name_; } 
		void name(const std::string& name) { name_ = name; }

		const double income() const { return income_; } 
		void income(double income) { income_ = income; }

		const unsigned int vacationDays() const { return vacationDays_; } 
		void vacationDays(unsigned int vacationDays) { vacationDays_ = vacationDays; }
		
};

// Three employee types
class Clerk : public Employee {
	public:
		Clerk(std::string name, double income, unsigned int vacationDays) : Employee(name, income, vacationDays) {
		}

		void Accept(IVisitor* const visitor) override {
			visitor->Visit(this);
		}
		std::string SpecialMethodOfClerk() const {
			return "Clerk";
		}
};

class Director : public Employee {
	public:
		Director(std::string name, double income, unsigned int vacationDays) : Employee(name, income, vacationDays) {
		}

		void Accept(IVisitor* const visitor) override {
			visitor->Visit(this);
		}
		std::string SpecialMethodOfDirector() const {
			return "Director";
		}
};

class President : public Employee {
	public:
		President(std::string name, double income, unsigned int vacationDays) : Employee(name, income, vacationDays) {
		}

		void Accept(IVisitor* const visitor) override {
			visitor->Visit(this);
		}
		std::string SpecialMethodOfPresident() const {
			return "President";
		}
};

/**
 * Concrete Visitors implement several versions of the same algorithm, which can
 * work with all concrete component classes.
 *
 * You can experience the biggest benefit of the IVisitor pattern when using it
 * with a complex object structure, such as a Composite tree. In this case, it
 * might be helpful to store some intermediate state of the algorithm while
 * executing visitor's methods over various objects of the structure.
 */
class IncomeVisitor : public IVisitor {
	public:
		void Visit(Employee* const element) override {
			std::cout << "IncomeVisitor providing income increase for " << element->name() << std::endl;
			std::cout << "Prev income: " << element->income() << std::endl;
			// Provide 10 % pay raise
			element->income(element->income() * 1.10);
			std::cout << "New income: " << element->income() << std::endl;
		}
};

class VacationVisitor : public IVisitor {
	public:
		void Visit(Employee* const element) override {
			std::cout << "VacationVisitor providing income increase for " << element->name() << std::endl;
			std::cout << "Prev vacationDays: " << element->vacationDays() << std::endl;
			// Provide 10 % pay raise
			element->vacationDays(element->vacationDays() + 3);
			std::cout << "New vacationDays: " << element->vacationDays() << std::endl;
		}
};

/**
 * The client code can run visitor operations over any set of elements without
 * figuring out their concrete classes. The accept operation directs a call to
 * the appropriate operation in the visitor object.
 */
void ClientCode(std::array<Element* const, 3> components, IVisitor *visitor) {
	// ...
	for (Element* const comp : components) {
		comp->Accept(visitor);
	}
	// ...
}

int main() {
	std::array<Element* const, 3> components = {new Clerk("Jonas", 2000.5, 5), new Director("John", 3000.99, 6), new President("Buster", 4000.0, 8)};

	std::cout << "The client code works with all visitors via the base IVisitor interface:\n";

	IncomeVisitor *visitor1 = new IncomeVisitor;
	ClientCode(components, visitor1);
	std::cout << "\n";

	std::cout << "It allows the same client code to work with different types of visitors:\n";
	VacationVisitor *visitor2 = new VacationVisitor;
	ClientCode(components, visitor2);

	for (Element *comp : components) {
		delete comp;
	}
	delete visitor1;
	delete visitor2;
	std::cout << "\nEnd of program!" << std::endl;

	return 0;
}
