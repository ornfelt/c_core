#include <iostream>

/**
https://www.codymorterud.com/design/2018/09/07/dependency-injection-cpp.html

The usefulness of Dependency Injection is in that the implementation of a class is more
flexible and independent by decreasing the amount of coupling between a client and another
service. The exact decoupling is the removal of a client class’s dependency on the
implementation of an interface, instead requiring the implementation to be passed in.

The solution for this issue is Dependency Injection. We can inject the implementation for
GasolineSource at runtime and use runtime polymorphism to abstract away the explicit
implementation of GasolineSource.
*/

using namespace std;

class GasolineSource {
public:
    virtual void FuelUp() = 0;
    virtual ~GasolineSource() = default;
};

class GasStation : public GasolineSource {
public:
    void FuelUp() {
        std::cout << "Pumping gas at gas station" << std::endl;
    }
};

class FuelCan : public GasolineSource {
public:
    void FuelUp() {
        std::cout << "Pumping gas from fuel can" << std::endl;
    }
};

class Car {
    GasolineSource *gasolineService = nullptr;
public:
    // The dependency for a source of gasoline is passed in
    // through constructor injection
    // as opposed to hard-coded into the class definition.
    Car(GasolineSource *service) : gasolineService(service) {
        // If the dependency was not defined, throw an exception.
        if(gasolineService == nullptr){
            throw std::invalid_argument("service must not be null");
        }
    }

    void getGasoline() {
        std::cout << "Car needs more gasoline!" << std::endl;
        // Abstract away the dependency implementation with polymorphism.
        gasolineService->FuelUp();
    }
};

int main() {
    GasolineSource *stationService = new GasStation();
    GasolineSource *canService = new FuelCan();

    // racecar is independent from the implementation of the fuel service.
    // a gas station service is injected.
    Car racecar(stationService);
    racecar.getGasoline();
	std::cout << std::endl;

    // dune buggy is independent from the implementation of the fuel service.
    // a fuel can service is injected.
    Car duneBuggy(canService);
    duneBuggy.getGasoline();

    delete stationService;
    delete canService;

	std::cout << "End!" << std::endl;
    return 0;
}
