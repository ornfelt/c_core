#include <iostream>
#include <cstdint>

using namespace std;

/*
https://www.linkedin.com/pulse/first-5-principles-oop-c-what-so-solid-abdalrahman-hesham

”The single responsibility principle states that every module or class
should have responsibility over a single part of the functionality
provided by the software, and that responsibility should be entirely
encapsulated by the class, module or function. All its services should be
narrowly aligned with that responsibility.”

Guideline: Prefer cohesive software entities. Everything that does not
strictly belong together, should be separated.
*/

class TaxCalculator;

// A better approach would be to have a parent abstract class named Country that all
// concrete country classes inherit from, then the CalculateTax method would look like
// this:
// uint16_t CalculateTax(Country country)//Is this statement not violating
// Dependency Inversion Principle? { return country.getAvgCitizenIncome()/10; }
// This way, the classes don't fall into inappropriate intimacy with each other.

class UnitedStates{
	friend TaxCalculator;

	uint16_t avg_citizen_income;

	public:
	UnitedStates(uint16_t avg_income) :  avg_citizen_income(avg_income){}

};

class UnitedKingdom{
	friend TaxCalculator;

	uint16_t avg_citizen_income;

	public:
	UnitedKingdom(uint16_t avg_income) :  avg_citizen_income(avg_income){}
};

class TaxCalculator{
	public:
		uint16_t CalculateTax(UnitedKingdom country){
			return country.avg_citizen_income / 10;
		}
		uint16_t CalculateTax(UnitedStates country){
			return country.avg_citizen_income / 8;
		}
};

int main()
{
	cout << "Hello World" << endl;
	TaxCalculator tax;
	UnitedStates us(100);
	cout << tax.CalculateTax(us) << endl;
	return 0;
}
