/**
 * Investor Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the IBM is also called the
 * Publisher and the Investor is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 */

#include <iostream>
#include <list>
#include <string>

class Stock;

// Observer interface
class IInvestor {
	public:
		virtual ~IInvestor(){};
		//virtual void Update(const std::string &message_from_subject) = 0;
		virtual void Update(Stock* stock) = 0;
};

// Subject interface
class Stock {
	public:
		virtual ~Stock(){};
		virtual void Attach(IInvestor *observer) = 0;
		virtual void Detach(IInvestor *observer) = 0;
		virtual void Notify() = 0;
		virtual void CreateMessage(std::string msg) = 0;
		virtual double getPrice() const = 0;
		virtual void setPrice(double newPrice) = 0;
};

/**
 * The IBM owns some important state and notifies observers when the state
 * changes.
 */

class IBM : public Stock {
	public:
		virtual ~IBM() {
			std::cout << "Goodbye, I was IBM (Subject / Stock).\n";
		}

		/**
		 * The subscription management methods.
		 */
		void Attach(IInvestor *observer) override {
			list_observer_.push_back(observer);
		}
		void Detach(IInvestor *observer) override {
			list_observer_.remove(observer);
		}
		void Notify() override {
			std::list<IInvestor *>::iterator iterator = list_observer_.begin();
			HowManyObserver();
			while (iterator != list_observer_.end()) {
				//(*iterator)->Update(message_);
				(*iterator)->Update(this);
				++iterator;
			}
		}

		void CreateMessage (std::string message = "Empty") override {
			// Change price
			price += 20;
			this->message_ = message;
			Notify();
		}
		void HowManyObserver() {
			std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
		}

		/**
		 * Usually, the subscription logic is only a fraction of what a Subject can
		 * really do. Subjects commonly hold some important business logic, that
		 * triggers a notification method whenever something important is about to
		 * happen (or after it).
		 */
		void SomeBusinessLogic() {
			this->message_ = "change message message";
			Notify();
			std::cout << "I'm about to do some thing important\n";
		}

		double getPrice() const override {
			return price;
		}

		void setPrice(double newPrice) override {
			this->price = newPrice;
		}


	private:
		std::list<IInvestor *> list_observer_;
		std::string message_;
		double price;
};

class Investor : public IInvestor {
	public:
		Investor(Stock &subject) : subject_(subject) {
			this->subject_.Attach(this);
			std::cout << "Hi, I'm the Investor \"" << ++Investor::static_number_ << "\".\n";
			this->number_ = Investor::static_number_;
		}
		virtual ~Investor() {
			std::cout << "Goodbye, I was the Investor \"" << this->number_ << "\".\n";
		}

		//void Update(const std::string &message_from_subject) override {
		void Update(Stock* stock) override {
			std::cout << "Notified Investor " << this->number_ << " of stock price change to " << stock->getPrice() << std::endl;
			//PrintInfo();
		}
		void RemoveMeFromTheList() {
			subject_.Detach(this);
			std::cout << "Investor \"" << number_ << "\" removed from the list.\n";
		}
		void PrintInfo() {
			std::cout << "Investor \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
		}

	private:
		std::string message_from_subject_;
		Stock &subject_;
		static int static_number_;
		int number_;
};

int Investor::static_number_ = 0;

void ClientCode() {
	Stock *ibm = new IBM;
	ibm->setPrice(50.35);
	Investor *observer1 = new Investor(*ibm);
	Investor *observer2 = new Investor(*ibm);
	Investor *observer3 = new Investor(*ibm);
	Investor *observer4;
	Investor *observer5;

	ibm->CreateMessage("Hello World! :D");
	observer3->RemoveMeFromTheList();

	ibm->CreateMessage("New computer released!");
	observer4 = new Investor(*ibm);

	observer2->RemoveMeFromTheList();
	observer5 = new Investor(*ibm);

	ibm->CreateMessage("My new computer is great! ;)");
	observer5->RemoveMeFromTheList();

	observer4->RemoveMeFromTheList();
	observer1->RemoveMeFromTheList();

	delete observer5;
	delete observer4;
	delete observer3;
	delete observer2;
	delete observer1;
	delete ibm;
}

int main() {
	ClientCode();
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}
