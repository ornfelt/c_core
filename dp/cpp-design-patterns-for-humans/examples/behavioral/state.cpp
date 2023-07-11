#include <iostream>
#include <typeinfo>

/**
 * The base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Account object, associated
 * with the State. This backreference can be used by States to transition the
 * Account to another State.
 */
class Account;

class State {
	/**
	 * @var Account
	 */
	protected:
		Account *context_;
		double balance_;
		double interest;
		double lowerLimit;
		double upperLimit;

	public:
		virtual ~State() {
		}

		// Constructor
		State(const double balance) {
			this->balance_ = balance;
		}

		void set_context(Account *context) {
			this->context_ = context;
		}

		const virtual double balance() const {
			return balance_;
		}

		virtual void deposit(const double amount) = 0;
		virtual void withdraw(const double amount) = 0;
		virtual void payInterest() = 0;
		virtual void stateChangeCheck() = 0;
};

/**
 * The Account defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Account.
 */
class Account {
	/**
	 * @var State A reference to the current state of the Account.
	 */
	private:
		State *state_;
		std::string owner_;

	public:
		Account(const std::string owner) : owner_(owner) {
			this->state_ = nullptr;
			std::cout << "New account created! Owner: " << owner_ << std::endl; 
		}
		~Account() {
			delete state_;
		}
		/**
		 * The Account allows changing the State object at runtime.
		 */
		void TransitionTo(State *state) {
			std::cout << "Account: Transition to " << typeid(*state).name() << ".\n";
			if (this->state_ != nullptr)
				delete this->state_;
			this->state_ = state;
			this->state_->set_context(this);
		}

		double getBalance() {
			return state_->balance();
		}

		void deposit(const double amount) {
			this->state_->deposit(amount);

			std::cout << "Deposited: " << amount << std::endl;
			std::cout << "Balance: " << getBalance() << std::endl;
			std::cout << "Status: " << typeid(*this->state_).name() << std::endl;
		}

		void withdraw(const double amount) {
			this->state_->withdraw(amount);

			std::cout << "Withdrew: " << amount << std::endl;
			std::cout << "Balance: " << getBalance() << std::endl;
			std::cout << "Status: " << typeid(*this->state_).name() << std::endl;
		}

		void payInterest() {
			this->state_->payInterest();

			std::cout << "Interest paid: " << std::endl;
			std::cout << "Balance: " << getBalance() << std::endl;
			std::cout << "Status: " << typeid(*this->state_).name() << std::endl;
		}
};


/**
 * Concrete States implement various behaviors, associated with a state of the
 * Account.
 */
class RedState : public State {

	private:
		double serviceFee;

	public:
		RedState(const double balance) : State(balance) {
			// Initiliaze
			interest = 0.0;
			lowerLimit = -100.0;
			upperLimit = 0.0;
			serviceFee = 15.00;
		}

		void deposit(double amount) override {
			balance_ += amount;
			stateChangeCheck();
		}

		void withdraw(const double amount) override {
			//amount = amount - serviceFee;
			std::cout << "No funds available for withdrawal!" << std::endl;
			stateChangeCheck();
		}

		void payInterest() override {
			std::cout << "payInterest()" << std::endl;
			stateChangeCheck();
		}

		void stateChangeCheck() override;

};

class SilverState : public State {
	public:
		SilverState(const double balance) : State(balance) {
			// Initiliaze
			interest = 0.0;
			lowerLimit = 0.0;
			upperLimit = 1000.0;
		}

		void deposit(const double amount) override {
			balance_ += amount;
			stateChangeCheck();
		}

		void withdraw(const double amount) override {
			balance_ -= amount;
			stateChangeCheck();
		}

		void payInterest() override {
			balance_ += interest * balance_;
			stateChangeCheck();
		}

		void stateChangeCheck() override;
};

class GoldState : public State {
	public:
		GoldState(const double balance) : State(balance) {
			// Initiliaze
			interest = 0.05;
			lowerLimit = 1000.0;
			upperLimit = 10000000.0;
		}

		void deposit(const double amount) override {
			balance_ += amount;
			stateChangeCheck();
		}

		void withdraw(const double amount) override {
			balance_ -= amount;
			stateChangeCheck();
		}

		void payInterest() override {
			balance_ += interest * balance_;
			stateChangeCheck();
		}

		void stateChangeCheck() override;

};

void RedState::stateChangeCheck() {
	if (balance_ > upperLimit)
		this->context_->TransitionTo(new SilverState(this->balance_));
}

void SilverState::stateChangeCheck() {
	if (balance_ < lowerLimit)
		this->context_->TransitionTo(new RedState(this->balance_));
	else if (balance_ > upperLimit)
		this->context_->TransitionTo(new GoldState(this->balance_));
}

void GoldState::stateChangeCheck() {
	if (balance_ < 0.0)
		this->context_->TransitionTo(new RedState(this->balance_));
	else if (balance_ < lowerLimit)
		this->context_->TransitionTo(new SilverState(this->balance_));
}

/**
 * The client code.
 */
void ClientCode() {
	Account *context = new Account("Jonas");
	// New accounts are 'Silver' by default
	context->TransitionTo(new SilverState(0.0));

	// Apply financial transactions
	context->deposit(500.0);
	std::cout << "\n";
	context->deposit(300.0);
	std::cout << "\n";
	context->deposit(550.0);
	std::cout << "\n";
	context->payInterest();
	std::cout << "\n";
	context->withdraw(2000.00);
	std::cout << "\n";
	context->withdraw(1100.00);
	std::cout << "\n";

	delete context;
}

int main() {
	ClientCode();
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}
