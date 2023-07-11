#include <iostream>
#include <string>
#include <list>

/**
 * The Mediator interface declares a method used by components to notify the
 * chatroom about various events. The Mediator may react to these events and
 * pass the execution to other components.
 */
class Participant;
class Mediator {
	public:
		virtual void Register(Participant *participant) = 0;
		virtual void UnRegister(Participant *participant) = 0;
		virtual void Notify(Participant *sender, std::string event) const = 0;
		virtual void Send(std::string from, std::string to, std::string message) = 0;
};

/**
 * The Base Component provides the basic functionality of storing a chatroom's
 * instance inside component objects.
 */
class Participant {
	protected:
		Mediator *mediator_;
		std::string name_;

	public:
		Participant(const std::string name, Mediator *chatroom = nullptr) : name_(name), mediator_(chatroom) {
		}

		void set_mediator(Mediator *chatroom) {
			this->mediator_ = chatroom;
		}

		void Send(std::string to, std::string message) {
			std::cout << "Participant: Sending message!" << std::endl;
			mediator_->Send(name_, to, message);
		}

		virtual void Receive(std::string from, std::string to) const = 0;

		std::string getName() {
			return name_;
		}
};

/**
 * Concrete Components implement various functionality. They don't depend on
 * other components. They also don't depend on any concrete chatroom classes.
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
			std::cout << name_ << " (Beatle) receives message From: " << from << ", Message: " << message << std::endl;
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
			std::cout << name_ << " (NonBeatle) receives message From: " << from << ", Message: " << message << std::endl;
		}
};

/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
class ChatRoom : public Mediator {
	private:
		std::list<Participant *> participants;

	public:
		// TODO: initiliazer list?
		//ChatRoom(Participant *c1, Participant *c2) : component1_(c1), component2_(c2) {
		ChatRoom(Participant *c1, Participant *c2) {
			//this->component1_->set_mediator(this);
			//this->component2_->set_mediator(this);
			c1->set_mediator(this);
			c2->set_mediator(this);
			Register(c1);
			Register(c2);
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

			while (participant_it != participants.end()) {
				if ((*participant_it)->getName() == to) {
					(*participant_it)->Receive(from, message);
					std::cout << "ChatRooom: Forwarding message to " << (*participant_it)->getName() << "..." << std::endl;
				}
				++participant_it;
			}

		}
};

/**
 * The client code.
 */

void ClientCode() {
	Participant *c1 = new Beatle("John");
	Participant *c2 = new NonBeatle("Paul");
	Participant *c3 = new Beatle("Ringo");
	Participant *c4 = new Beatle("John");
	Participant *c5 = new NonBeatle("Yoko");
	ChatRoom *chatroom = new ChatRoom(c1, c2);

	// Testing
	std::cout << "\n";
	c2->Send("John", "Hi John!");
	std::cout << "\n";
	c1->Send("Test", "invalid test message");
	std::cout << "\n";
	c1->Send("Paul", "valid test message");

	// Old
	//std::cout << "Client triggers operation A.\n";
	//c1->DoA();
	//std::cout << "\n";
	//std::cout << "Client triggers operation D.\n";
	//c2->DoD();

	c1;
	delete c2;
	delete chatroom;
}

int main() {
	ClientCode();
	return 0;
}
