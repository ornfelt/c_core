"""
https://towardsdatascience.com/solid-coding-in-python-1281392a6a94

Interface Segregation Principle (ISP)

“Many client-specific interfaces are better than one general-purpose interface”

In this sense, the IS principles tell us that a class should only have the interface needed (SRP) and avoid methods that won’t work or that have no reason to be part of that class.

This problem arises, primarily, when, a subclass inherits methods from a base class that it does not need.

Let’s see an example:

import numpy as np
from abc import ABC, abstractmethod

class Mammals(ABC):
    @abstractmethod
    def swim() -> bool:
        print("Can Swim") 

    @abstractmethod
    def walk() -> bool:
        print("Can Walk") 

class Human(Mammals):
    def swim():
        return print("Humans can swim") 

    def walk():
        return print("Humans can walk") 

class Whale(Mammals):
    def swim():
        return print("Whales can swim") 

The sub-class whale can still invoke the method “walk” but it shouldn’t, and we must avoid it.
"""

# The way suggested by ISP is to create more client-specific interfaces rather than one general-purpose interface. So, our code example becomes:

from abc import ABC, abstractmethod

class Walker(ABC):
  @abstractmethod
  def walk() -> bool:
    return print("Can Walk") 

class Swimmer(ABC):
  @abstractmethod
  def swim() -> bool:
    return print("Can Swim") 

class Human(Walker, Swimmer):
  def walk():
    return print("Humans can walk") 
  def swim():
    return print("Humans can swim") 

class Whale(Swimmer):
  def swim():
    return print("Whales can swim") 

if __name__ == "__main__":
  Human.walk()
  Human.swim()

  Whale.swim()
  Whale.walk()

# Humans can walk
# Humans can swim
# Whales can swim

"""
Now, every sub-class inherits only what it needs, avoiding invoking an out-of-context (wrong) sub-method. That might create an error hard to catch.

This principle is closely connected with the other ones and specifically, it tells us to keep the content of a subclass clean from elements of no use to that subclass. This has the final aim to keep our classes clean and minimise mistakes.
"""