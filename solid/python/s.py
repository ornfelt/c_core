"""
https://towardsdatascience.com/solid-coding-in-python-1281392a6a94

# Instead of doing something like this:

import numpy as np

def math_operations(list_):
    # Compute Average
    print(f"the mean is {np.mean(list_)}")
    # Compute Max
    print(f"the max is {np.max(list_)}") 

math_operations(list_ = [1,2,3,4,5])

"""

# We should break it down to:

def get_mean(list_):
    '''Compute Mean'''
    print(f"the mean is {np.mean(list_)}") 

def get_max(list_):
    '''Compute Max'''
    print(f"the max is {np.max(list_)}") 

def main(list_): 
    # Compute Average
    get_mean(list_)
    # Compute Max
    get_max(list_)

main([1,2,3,4,5])
# the mean is 3.0
# the max is 5

"""
    It is easier to localize errors. Any error in execution will point out to a 
	smaller section of your code, accelerating your debug phase.
    Any part of the code is reusable in other section of your code.
    Moreover and, often overlooked, is that it is easier to create testing for 
	each function of your code. Side note on testing: You should write tests 
	before you actually write the script. But, this is often ignored in favour 
	of creating some nice result to be shown to the stakeholders instead.
"""