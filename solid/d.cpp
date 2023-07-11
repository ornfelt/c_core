#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>

using namespace std;

/*
https://www.linkedin.com/pulse/first-5-principles-oop-c-what-so-solid-abdalrahman-hesham

Dependency Inversion Principle

This principle states that a higher level-module should not depend on a lower-level
module, but they both should depend on abstractions. It also states that abstractions
should not depend on details, but details should depend on abstractions. Since that sounds
like some logic class in school, let's clarify with an example.

Suppose we have a "FruitBasket" class, which is a low-level module, where the user has
"AddToBasket" functionality that appends a tuple of strings containing the fruit and the
color to a vector.

Now suppose we have a high-level class named "ColorSeracher" that has a "ListColor"
functionality, which goes through the vector item by item, then prints each found fruit
with the matching color given to the function. This can be seen below.

class FruitBasket { // Low-level module
    public:
    std::vector<std::tuple<std::string, std::string>> Basket;

    void AddToBasket(const std::string& Fruit, const std::string& Color){
        Basket.push_back(std::make_tuple(Fruit, Color));
    }
};

class ColorSearcher { // High-level module
	public:
	void ListColor(FruitBasket fruit_basket, const std::string& color) {
        for(auto item: fruit_basket.Basket){
            if (std::get<1>(item) == color){
				std::cout << "Found " <<std:get<0>(item) << std::endl;
            }
        }
    }
};

The problem with this design is that the "ColorSearcher" high-level module depends heavily
on the low-level module, since it knows the details about the "Basket" object found in it,
as it knows it's a vector of tuples. Any modification to the low-level class, will now
affect the higher-level one.

A simple solution would be to introduce an abstract class that both these modules depend
on. By doing so, the high level class is seperated from the details. The code given below
follows the dependency inversion principle.
*/

class BasketSearcher{ // Abstract module
    public:
	virtual void AddToBasket(const std::string& Fruit, const std::string& Color) = 0;
    virtual std::vector<std::string> SearchByColor(const std::string& color) = 0;
	virtual ~BasketSearcher() = default;
};

class FruitBasket: public BasketSearcher{ // Low-level module
    public:
    std::vector<std::tuple<std::string, std::string>> Basket;

    void AddToBasket(const std::string& Fruit, const std::string& Color){
        Basket.push_back(std::make_tuple(Fruit, Color));
    }

    std::vector<std::string> SearchByColor(const std::string& color) override{
        std::vector<std::string> Found;
        for(auto item: Basket){
            if (std::get<1>(item) == color){
                Found.push_back(std::get<0>(item));
            }
        }
    return Found;
    }
};

class ColorSearcher{ // High-level module
    public:
	
	// Some polymorphism (not required to have two ListColor...
    void ListColor(BasketSearcher& basket, std::string color){
		std::cout<< "ListColor by reference called" << std::endl;
        for(auto item: basket.SearchByColor(color)){
            std::cout<< "Found " << item << std::endl;
        }
    }

    void ListColor(BasketSearcher* basket, std::string color){
		std::cout<< "ListColor by pointer called" << std::endl;
        //for(auto item: basket.SearchByColor(color)){
        for(auto item: basket->SearchByColor(color)){
            std::cout<< "Found " << item << std::endl;
        }
    }
};

int main()
{
	cout << "Hello World" << endl;
	BasketSearcher *fruit_basket = new FruitBasket();
	fruit_basket->AddToBasket("banana", "yellow");
	fruit_basket->AddToBasket("apple", "red");
	fruit_basket->AddToBasket("apple", "green");
	fruit_basket->AddToBasket("pear", "green");

	ColorSearcher cs;
	cs.ListColor(fruit_basket, "yellow");
	cs.ListColor(fruit_basket, "green");

	cout << endl;
	// Using reference
	FruitBasket fruit_basket_ref;
	fruit_basket_ref.AddToBasket("banana", "yellow");
	fruit_basket_ref.AddToBasket("apple", "red");
	fruit_basket_ref.AddToBasket("apple", "green");
	fruit_basket_ref.AddToBasket("pear", "green");

	cs.ListColor(fruit_basket_ref, "yellow");
	cs.ListColor(fruit_basket_ref, "green");

	// Delete fruit_basket pointer
	delete fruit_basket;
	cout << "End!" << endl;
	return 0;
}

/**
Note on casting:

Up-casting is implicit in C++, and is used a lot when you deal with virtual dispatching.
In other words, you have a pointer to Base from which you can access the common interface
of a whole hierarchy of classes, and the selection can be done at runtime. This assumes
that your interface functions are marked virtual. Example:

Up-casting:
Base* pBase; 
cin >> x; 
if(x == 0) // this is done at runtime, as we don't know x at compile time
    pBase = new Derived1;
else
    pBase = new Derived2;

pBase->draw(); // draw is a virtual member function

It is extremely useful in these situations in which the dispatch is done at runtime.
Simply said, upcasting allows one to treat a derived class as a base class (via its common
interface).

Down-casting is less useful, and IMO should be avoided whenever one can. In general is a
sign of bad design, as one rarely needs to convert a Base object to a derived one. It can
be done (and the result checked) via dynamic_cast, like
Base* pBase = new Derived; // OK, the dynamic type of pBase is Derived
Derived* pDerived = dynamic_cast<Derived*>(pBase);
if(pDerived) // always test  
{
    // success
}
else
{
    // fail to down-cast
}

*/
