"""
https://towardsdatascience.com/solid-coding-in-python-1281392a6a94

Open–closed principle (OCP):
“Software entities … should be open for extension but closed for modification”.
In other words: You should not need to modify the code you have already written to accommodate new functionality, but simply add what you now need.

This does not mean that you cannot change your code when the code premises needs to be modified, but that if you need to add new functions similar to the one present, you should not require to change other parts of the code.

To clarify this point let’s refer to the example we saw earlier. If we wanted to add new functionality, for example, compute the median, we should have created a new method function and add its invocation to “main”. That would have added an extension but also modified the main.

We can solve this by turning all the functions we wrote into subclasses of a class. In this case, I have created an abstract class called “Operations” with an abstract method “get_operation”. (Abstract classes are generally an advanced topic. If you don’t know what an abstract class is, you can run the following code even without).

Now, all the old functions, are now classes called by the __subclasses__() method. That will find all classes inheriting from Operations and operate the function “operations” that is present in all sub-classes.
"""

import numpy as np
from abc import ABC, abstractmethod

class Operations(ABC):
    '''Operations'''
    @abstractmethod
    def operation():
        pass

class Mean(Operations):
    '''Compute Max'''
    def operation(list_):
        print(f"The mean is {np.mean(list_)}") 

class Max(Operations):
    '''Compute Max'''
    def operation(list_):
        print(f"The max is {np.max(list_)}") 

class Main:
    '''Main'''
    @abstractmethod
    def get_operations(list_):
        # __subclasses__ will found all classes inheriting from Operations
        for operation in Operations.__subclasses__():
            operation.operation(list_)

if __name__ == "__main__":
    Main.get_operations([1,2,3,4,5])
    
# The mean is 3.0
# The max is 5

"""
If now we want to add a new operation e.g.: median, we will only need to add a class “Median” inheriting from the class “Operations”. The newly formed sub-class will be immediately picked up by __subclasses__() and no modification in any other part of the code needs to happen.

The result is a very flexible class, that requires minimum time to be maintained.

"""