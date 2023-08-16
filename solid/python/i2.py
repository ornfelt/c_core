"""
https://www.pythontutorial.net/python-oop/python-interface-segregation-principle/

The interface segregation principle states that an interface should be as small a possible in terms of cohesion. In other words, it should do ONE thing.
Make fine grained interfaces that are client-specific. Clients should not be forced to implement interfaces they do not use.

Consider the following example:


from abc import ABC, abstractmethod

class Vehicle(ABC):
    @abstractmethod
    def go(self):
        pass

    @abstractmethod
    def fly(self):
        pass
        
class Aircraft(Vehicle):
    def go(self):
        print("Taxiing")

    def fly(self):
        print("Flying")
        
class Car(Vehicle):
    def go(self):
        print("Going")

    def fly(self):
        raise Exception('The car cannot fly')

In this design the Car class must implement the fly() method from the Vehicle class that the Car class doesn’t use. Therefore, this design violates the interface segregation principle.

To fix this, you need to split the Vehicle class into small ones and inherits from these classes from the Aircraft and Car classes:
"""

# First, split the Vehicle interface into two smaller interfaces: Movable and Flyable, and inherits the Movable class from the Flyable class:
class Movable(ABC):
    @abstractmethod
    def go(self):
        pass


class Flyable(Movable):
    @abstractmethod
    def fly(self):
        pass
        
# Second, inherits from the Flyable class from the Aircraft class:        
class Aircraft(Flyable):
    def go(self):
        print("Taxiing")

    def fly(self):
        print("Flying")
       
# Third, inherit the Movable class from the Car class:
class Car(Movable):
    def go(self):
        print("Going")
        
# In this design, the Car only need to implement the go() method that it needs. It doesn’t need to implement the fly() method that it doesn’t use.        
 