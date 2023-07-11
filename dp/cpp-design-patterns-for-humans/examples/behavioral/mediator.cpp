#include <iostream>
#include <string>
#include <list>
#include <initializer_list>

/**
 * The Mediator interface declares a method used by components to notify the
 * chatroom about various events. The Mediator may react to these events and
 * pass the execution to other components.

 initializer_list ref: https://en.cppreference.com/w/cpp/utility/initializer_list
 */
class Participant;
class Mediator {
	public:
		virtual ~Mediator(){};
		virtual void Register(Participant *participant) = 0;
		virtual void UnRegister(Participant *participant) = 0;
		virtual void Notify(Participant *sender, std::string event) const = 0;
		virtual void Send(std::string from, std::string to, std::string message) = 0;
};

/**
 * The Base Component provides the basic functionality of storing a chatroom's
 * instance inside component objects. AKA AbstractColleague / AbstractParticipant.
 */
class Participant {
	protected:
		Mediator *mediator_;
		std::string name_;

	public:
		Participant(const std::string name, Mediator *chatroom = nullptr) : name_(name), mediator_(chatroom) {
		}

		virtual ~Participant(){};

		void set_mediator(Mediator *chatroom) {
			this->mediator_ = chatroom;
		}

		void Send(std::string to, std::string message) {
			std::cout << "Participant: Sending message!" << std::endl;
			mediator_->Send(name_, to, message);
		}

		virtual void Receive(std::string from, std::string message) const {
			std::cout << from << " to " << name_ << ": " << message << std::endl;
		}

		std::string getName() {
			return name_;
		}
};

/**
 * Concrete Components implement various functionality. They don't depend on
 * other components. They also don't depend on any concrete chatroom classes.
 * AKA ConcreteColleague, ConcreteParticipant.
 */
class Beatle : public Participant {
	public:
		Beatle(const std::string name) : Participant(name) { 
		}
		void DoA() {
			std::cout << "Component 1 does A.\n";
			this->mediator_->Notify(this, "A");
		}
		void DoB() {
			std::cout << "Component 1 does B.\n";
			this->mediator_->Notify(this, "B");
		}

		void Receive(std::string from, std::string message) const override {
			std::cout << "To a Beatle: ";
			Participant::Receive(from, message);
		}
};

class NonBeatle : public Participant {
	public:
		NonBeatle(const std::string name) : Participant(name) { 
		}
		void DoC() {
			std::cout << "Component 2 does C.\n";
			this->mediator_->Notify(this, "C");
		}
		void DoD() {
			std::cout << "Component 2 does D.\n";
			this->mediator_->Notify(this, "D");
		}

		void Receive(std::string from, std::string message) const override {
			std::cout << "To a non-Beatle: ";
			Participant::Receive(from, message);
		}
};

/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
template<typename T>
class ChatRoom : public Mediator {
	private:
		std::list<T> participants;

	public:
		ChatRoom(std::initializer_list<T> participants_init_list) : participants(participants_init_list) {

			std::cout << "init list size: " << participants.size() << std::endl;
			std::list<Participant *>::iterator participant_it = participants.begin();
			while (participant_it != participants.end()) {
				std::cout << "Initializing participant: " << (*participant_it)->getName() << std::endl;
				(*participant_it)->set_mediator(this);
				++participant_it;
			}
		}

		void Register(Participant *participant) override {
			participants.push_back(participant);
		}

		void UnRegister(Participant *participant) override {
			participants.remove(participant);
		}

		void Notify(Participant *sender, std::string event) const override {
			if (event == "A") {
				std::cout << "Mediator reacts on A and triggers following operations:\n";
				//this->component2_->DoC();
			}
			if (event == "D") {
				std::cout << "Mediator reacts on D and triggers following operations:\n";
				//this->component1_->DoB();
				//this->component2_->DoC();
			}
		}

		void Send(std::string from, std::string to, std::string message) override {
			std::list<Participant *>::iterator participant_it = participants.begin();
			bool message_sent = false;

			while (participant_it != participants.end()) {
				if ((*participant_it)->getName() == to) {
					std::cout << "ChatRooom: Forwarding message to " << (*participant_it)->getName() << "..." << std::endl;
					(*participant_it)->Receive(from, message);
					message_sent = true;
				}
				++participant_it;
			}

			if (!message_sent)
				std::cout << "Invalid recipient: " << to << std::endl;
		}
};

/**
 * The client code.
 */
void ClientCode() {
	Participant *george = new Beatle("George"); // Harrison
	Participant *paul = new Beatle("Paul"); // McCartney
	Participant *ringo = new Beatle("Ringo"); // Starr
	Participant *john = new Beatle("John"); // Lennon
	Participant *yoko = new NonBeatle("Yoko");

	// Registration occurs in constructor
	ChatRoom<Participant*> *chatroom = new ChatRoom<Participant*>({george, paul, ringo, john, yoko});

	// New participants can be added later as well...
	Participant *jonas = new NonBeatle("Jonas");
	jonas->set_mediator(chatroom);
	chatroom->Register(jonas);

	// Testing
	std::cout << "\n";
	yoko->Send("John", "Hi John!");
	std::cout << "\n";
	paul->Send("Ringo", "All you need is love");
	std::cout << "\n";
	ringo->Send("George", "My sweet Lord");
	std::cout << "\n";
	paul->Send("John", "Can't buy me love");
	std::cout << "\n";
	john->Send("Yoko", "My sweet love");

	std::cout << "\n";
	paul->Send("Jonas", "Hi jonas!");
	std::cout << "\n";
	john->Send("Test", "invalid test message");
	std::cout << "\n";
	john->Send("Paul", "valid test message");

	std::cout << "\n";
	jonas->Send("Ringo", "valid test message2");

	delete george;
	delete paul;
	delete ringo;
	delete yoko;
	delete john;
	delete jonas;
	delete chatroom;
}

int main() {
	ClientCode();
	std::cout << "\nEnd of program!" << std::endl;
	return 0;
}
