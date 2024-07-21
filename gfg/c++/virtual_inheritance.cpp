/**

Virtual inheritance in C++ is a concept used to solve the "diamond problem" that
occurs with multiple inheritance. The diamond problem happens when two classes
(B and C) inherit from a common base class (A), and then another class (D)
inherits from both B and C. Without virtual inheritance, this would lead to D
having two copies of A, which can cause ambiguity and redundancy.

See example code below.

While making the show method virtual is a valid concept in C++ for polymorphism,
it does not solve the diamond problem related to multiple inheritance. Let's
discuss both approaches and why virtual inheritance is necessary in this case.
Making the Method Virtual

Making a method virtual allows derived classes to override it. It enables
runtime polymorphism, which means the correct method implementation is chosen
based on the actual object type at runtime. However, it doesn't address the
issue of multiple copies of the base class in the diamond inheritance scenario.
See virtual_inheritance_2.cpp for usage of virtual void show...
*/

#include <iostream>

class A {
public:
    void show() {
        std::cout << "Class A" << std::endl;
    }
};

class B : virtual public A { };

class C : virtual public A { };

class D : public B, public C { };

int main() {
    D d;
    d.show(); // No ambiguity, prints "Class A"
    return 0;
}
