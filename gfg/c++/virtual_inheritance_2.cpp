#include <iostream>

class A {
public:
    virtual void show() {
        std::cout << "Class A" << std::endl;
    }
};

class B : virtual public A {
public:
    void show() override {
        std::cout << "Class B" << std::endl;
    }
};

class C : virtual public A {
public:
    void show() override {
        std::cout << "Class C" << std::endl;
    }
};

// If you comment the overriden show, you will get an error that there's more
// than one final overrider...
class D : public B, public C {
public:
    void show() override {
        // Call a specific show method if needed or provide a new implementation
        B::show();
    }
};

int main() {
    D d;
    d.show(); // No ambiguity, prints "Class B" or "Class C" based on your implementation
    return 0;
}
