#include <iostream>

using namespace std;

/*
https://platis.solutions/blog/2020/06/22/how-to-write-solid-cpp/

Open/closed principle
Software entities should be open for extension, but closed for modification

The open/closed principle is an interesting one, mainly because it evolved through time
along with the programming languages. The principle dictates the software modules are open
for extension but closed for modification. This allows new functionality to be added
without changing existing source code.

In practice, the best way to achieve this with C++ is polymorphism. Particularly, with the
use of abstract interfaces, we can extend a class and specialize its behavior without
changing the interface specification. This principle allows for reusable and maintainable
software.
Let’s start by looking at a counterexample. Something you should not do:

enum class SensorModel {
   Good,
   Better
};

struct DistanceSensor {
   DistanceSensor(SensorModel model) : mModel{model} {}
   int getDistance() {
       switch (mModel) {
           case SensorModel::Good :
               // Business logic for "Good" model
           case SensorModel::Better :
               // Business logic for "Better" model
       }
   }
};

In this snippet we have a DistanceSensor class, that depending on the way we have
initialized it, it effectively represents a different sensor.
Unfortunately, our class design does not allow the behavior to be extended unless we
modify the source. For example, if we want to add a new sensor model, we would have to
change the DistanceSensor class to accommodate the new functionality.
By defining and implementing an interface, we avoid having to alter that switch statement
in a way that can make things quickly very inconvenient for us.
*/

/*
We start by defining what we want a DistanceSensor to do in general. Remember, a
DistanceSensor is something generic, i.e. it does not have a model, therefore it does not
make any sense to have a concrete instance of it.
Therefore we need to define DistanceSensor as a pure abstract class or, an interface, as
we would say in other languages such as Java.

Then, we create specializations of the interface, for each of the different DistanceSensor
models that we have. Every time we want to add a new sensor, we can create a new child
class that implements the DistanceSensor interface, without changing any of the existing
classes.

* Notes:
When do we need to write a user-defined destructor? 
If we do not write our own destructor in class, compiler creates a default destructor for
us. The default destructor works fine unless we have dynamically allocated memory or
pointer in class. When a class contains a pointer to memory allocated in class, we should
write a destructor to release memory before the class instance is destroyed. This must be
done to avoid memory leak.

Also see: https://www.geeksforgeeks.org/virtual-destructor/
*/
struct DistanceSensor {
	// If I want to give my class a destructor that is virtual, but is otherwise the same as what the compiler would generate, I can use =default:
	virtual ~DistanceSensor() = default;
	virtual int getDistance() = 0;
};

struct GoodDistanceSensor : public DistanceSensor {
	int getDistance() override {
		// Business logic for "Good" model
	}
};

struct BetterDistanceSensor : public DistanceSensor {
	int getDistance() override {
		// Business logic for "Better" model
	}
};
