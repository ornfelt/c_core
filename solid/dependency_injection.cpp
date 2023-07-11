#include <iostream>

/**
https://www.codymorterud.com/design/2018/09/07/dependency-injection-cpp.html

The usefulness of Dependency Injection is in that the implementation of a class is more
flexible and independent by decreasing the amount of coupling between a client and another
service. The exact decoupling is the removal of a client class’s dependency on the
implementation of an interface, instead requiring the implementation to be passed in.

Let’s take a look at a class that requires a dependency and the class defining that
dependency.
*/

class GasolineSource {
public:
    virtual void FuelUp() = 0;
};

class GasStation : public GasolineSource {
public:
    void FuelUp(){
        std::cout << "Pumping gas at gas station" << std::endl;
    }
};

// the class Car is dependent on the definition for GasStation.
// Car cannot be defined without GasStation being defined and 
// Car would need to be changed whenever the source of 
// gasoline is changed, like to a can (FuelCan).
class FuelCan : public GasolineSource {
public:
    void FuelUp(){
        std::cout << "Pumping gas from fuel can" << std::endl;
    }
};

// Car is dependent on GasStation being defined in order to fuel up.
class Car {
    GasStation gasolineService;
	//FuelCan gasolineService;
public:
    Car(){ }
    void getGasoline() {
        std::cout << "Car needs more gasoline!" << std::endl;
        gasolineService.FuelUp();
    }
};

int main() {
    GasolineSource *stationService = new GasStation();

    // racecar is independent from the implementation of the fuel service.
    // a gas station service is injected.
    Car car;
    car.getGasoline();

    delete stationService;
    return 0;
}

// The solution for this issue is Dependency Injection. We can inject the 
// implementation for GasolineSource at runtime and use runtime 
// polymorphism to abstract away the explicit implementation of GasolineSource.
// See dependency_injection_solution.cpp
