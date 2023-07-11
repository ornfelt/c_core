# https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/solutions/2738381/python-elegant-short-o-1-recursive-iterative-bit-manipulation/

# Python Elegant & Short | O(1) | Recursive / Iterative / Bit Manipulation

# Recursive solution
class Solution:
    """
    Time:   O(log(n))
    Memory: O(log(n))
    """

    def numberOfSteps(self, num: int) -> int:
        if num == 0:
            return 0
        return 1 + self.numberOfSteps(num - 1 if num & 1 else num >> 1)
        
# Iterative solution
class SolutionIterative:
    """
    Time:   O(log(n))
    Memory: O(1)
    """

    def numberOfSteps(self, num: int) -> int:
        steps = 0

        while num != 0:
            steps += 1
            if num & 1:
                num -= 1
            else:
                num >>= 1

        return steps

# Bit Manipulation solution
class SolutionBits:
    """
    Time:   O(1)
    Memory: O(1)
    """

    def numberOfSteps(self, num: int) -> int:
        if num == 0:
            return 0
        return num.bit_length() - 1 + num.bit_count()