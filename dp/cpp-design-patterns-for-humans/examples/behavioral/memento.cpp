#include <iostream>
#include <string>
#include <ctime>
#include <vector>

/**
 * The Memento interface provides a way to retrieve the memento's metadata, such
 * as creation date or name. However, it doesn't expose the SalesProspect's state.
 */
class Memento {
	public:
		virtual ~Memento() {}
		virtual std::string GetName() const = 0;
		virtual std::string date() const = 0;
		virtual std::string state() const = 0;
		const virtual std::string name() const = 0;
		const virtual std::string phone() const = 0;
		const virtual double budget() const = 0;
};

/**
 * The Concrete Memento contains the infrastructure for storing the SalesProspect's
 * state.
 */
class ConcreteMemento : public Memento {
	private:
		std::string date_;
		std::string state_;

		std::string name_;
		std::string phone_;
		double budget_;

	public:
		ConcreteMemento(std::string state, std::string name, std::string phone, double budget) : state_(state), name_(name), phone_(phone), budget_(budget) {
			this->state_ = state;
			std::time_t now = std::time(0);
			this->date_ = std::ctime(&now);
		}

		// Getters and setters
		const std::string name() const override { return name_; } 
		void name(const std::string& name) { name_ = name; }

		const std::string phone() const override { return phone_; } 
		void phone(const std::string& phone) { phone_ = phone; }

		const double budget() const override { return budget_; } 
		void budget(const double& budget) { budget_ = budget; }

		/**
		 * The SalesProspect uses this method when restoring its state.
		 */
		std::string state() const override {
			return this->state_;
		}
		/**
		 * The rest of the methods are used by the ProspectMemory to display metadata.
		 */
		std::string GetName() const override {
			return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
		}
		std::string date() const override {
			return this->date_;
		}
};

/**
 * The SalesProspect holds some important state that may change over time. It also
 * defines a method for saving the state inside a memento and another method for
 * restoring the state from it.
 */
class SalesProspect {
	/**
	 * @var string For the sake of simplicity, the originator's state is stored
	 * inside a single variable.
	 */
	private:
		std::string state_;
		std::string name_;
		std::string phone_;
		double budget_;

		std::string GenerateRandomString(int length = 10) {
			const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			int stringLength = sizeof(alphanum) - 1;

			std::string random_string;
			for (int i = 0; i < length; i++) {
				random_string += alphanum[std::rand() % stringLength];
			}
			return random_string;
		}

	public:
		SalesProspect(std::string state) : state_(state) {
			std::cout << "SalesProspect: My initial state is: " << this->state_ << "\n";
		}
		/**
		 * The SalesProspect's business logic may affect its internal state. Therefore,
		 * the client should backup the state before launching methods of the business
		 * logic via the save() method.
		 */
		void DoSomething() {
			std::cout << "SalesProspect: I'm doing something important.\n";
			this->state_ = this->GenerateRandomString(30);
			std::cout << "SalesProspect: and my state has changed to: " << this->state_ << "\n";

			// Change name, phone and budget...
		}

		// Getters and setters
		//const std::string& name() const { return name_; } 
		const std::string name() const { return name_; } 
		void name(const std::string& name) { name_ = name; }

		//const std::string& phone() const { return phone_; } 
		const std::string phone() const { return phone_; } 
		void phone(const std::string& phone) { phone_ = phone; }

		//const double& budget() const { return budget_; } 
		const double budget() const { return budget_; } 
		void budget(const double& budget) { budget_ = budget; }

		std::string state() const {
			return this->state_;
		}

		/**
		 * Saves the current state inside a memento.
		 */
		Memento *Save() {
			std::cout << "Saving state..." << std::endl;
			return new ConcreteMemento(this->state_, this->name_, this->phone_, this->budget_);
		}
		/**
		 * Restores the SalesProspect's state from a memento object.
		 */
		void Restore(Memento *memento) {
			this->state_ = memento->state();
			std::cout << "SalesProspect: My state has been restored to: " << this->state_ << "\n";

			this->name_ = memento->name();
			this->phone_ = memento->phone();
			this->budget_ = memento->budget();
			//this->name(memento->name());
			//this->phone(memento->phone());
			//this->budget(memento->budget());
			std::cout << "New name, phone and budget: " << name_ << ", " << phone_ << ", " << budget_ << std::endl;
		}
};

/**
 * The ProspectMemory doesn't depend on the Concrete Memento class. Therefore, it
 * doesn't have access to the originator's state, stored inside the memento. It
 * works with all mementos via the base Memento interface.
 */
class ProspectMemory {
	/**
	 * @var Memento[]
	 */
	private:
		std::vector<Memento *> mementos_;

		/**
		 * @var SalesProspect
		 */
		SalesProspect *originator_;

	public:
		ProspectMemory(SalesProspect* originator) : originator_(originator) {
		}

		~ProspectMemory() {
			for (auto m : mementos_) delete m;
		}

		void Backup() {
			std::cout << "\nCaretaker: Saving SalesProspect's state...\n";
			std::cout << "state, name, phone and budget: " << this->originator_->state() << "," << this->originator_->name() << ", " << this->originator_->phone() << ", " << this->originator_->budget() << std::endl;
			this->mementos_.push_back(this->originator_->Save());
		}
		void Undo() {
			if (!this->mementos_.size()) {
				return;
			}
			Memento *memento = this->mementos_.back();
			this->mementos_.pop_back();
			std::cout << "ProspectMemory: Restoring state to: " << memento->GetName() << "\n";
			try {
				this->originator_->Restore(memento);
			} catch (...) {
				this->Undo();
			}
		}
		void ShowHistory() const {
			std::cout << "ProspectMemory: Here's the list of mementos:\n";
			for (Memento *memento : this->mementos_) {
				std::cout << memento->GetName() << "\n";
				std::cout << "name, phone and budget: " << memento->name() << ", " << memento->phone() << ", " << memento->budget() << std::endl;
			}
		}
};

/**
 * Client code.
 */
void ClientCode() {
	SalesProspect *originator = new SalesProspect("Super-duper-super-puper-super.");
	ProspectMemory *caretaker = new ProspectMemory(originator);
	originator->name("Noel van Halen"); // setName
	originator->phone("(412) 256-0990"); // setPhone
	originator->budget(2500); // setBudget

	caretaker->Backup();
	originator->DoSomething();
	originator->name("Testing person"); // setName
	originator->phone("081111"); // setPhone
	originator->budget(25.9522); // setBudget

	caretaker->Backup();
	originator->DoSomething();
	originator->name("Leo Welch"); // setName
	originator->phone("(310) 209-7111"); // setPhone
	originator->budget(100000.25); // setBudget

	caretaker->Backup();
	originator->DoSomething();
	originator->name("Jonas test"); // setName
	originator->phone("123"); // setPhone
	originator->budget(1500); // setBudget
	std::cout << "\nstate, name, phone and budget (before rollback): " << originator->state() << originator->name() << ", " << originator->phone() << ", " << originator->budget() << std::endl;

	std::cout << "\n";
	caretaker->ShowHistory();
	std::cout << "\nClient: Now, let's rollback!\n\n";
	caretaker->Undo();
	std::cout << "\nClient: Once more!\n\n";
	caretaker->Undo();

	delete originator;
	delete caretaker;
}

int main() {
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	ClientCode();
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}
