#include <iostream>

// https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/solutions/1062161/c-bit-manipulation-5-approaches-0ms-o-logn-beats-100/
// https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/solutions/507736/c-o-1-solution-without-iteration-recursion/

// Given an integer num, return the number of steps to reduce it to zero.
// In one step, if the current number is even, you have to divide it by 2, 
// otherwise, you have to subtract 1 from it.

/**
	Input: num = 14
	Output: 6
	Explanation: 
	Step 1) 14 is even; divide by 2 and obtain 7. 
	Step 2) 7 is odd; subtract 1 and obtain 6.
	Step 3) 6 is even; divide by 2 and obtain 3. 
	Step 4) 3 is odd; subtract 1 and obtain 2. 
	Step 5) 2 is even; divide by 2 and obtain 1. 
	Step 6) 1 is odd; subtract 1 and obtain 0.
*/

// Solution:
/**
    num=num>>1 right shift num is equivalent to num=num/2
    bitset<32>(num).count() = number of set bits(1) in num
    log2(num)=number of bits required to make the num - 1
    __builtin_clz(num) = It counts number of zeros before the first occurrence of 1 (set bit), that is leading zeroes in num
    __builtin_popcount(num) = number of set bits(1) in num
    log2(num) is equivalent to 31 - __builtin_clz(num)
    bitset<32>(num).count() is equivalent to __builtin_popcount(num)
	
	TIME COMPLEXITY
	O(logn)

	SPACE COMPLEXITY
	O(1)
*/

// Approach 1 (Iterative, simulating the process)
class SolutionIterative {
public:
    int numberOfSteps (int num) {
        int count=0;
        while(num){
            if(num%2){ // odd
                --num;
            }
            else{ // even
                num>>=1; // num=num/2
            }
            ++count;
        }
        return count;
    }
	
	// https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/solutions/502809/just-count-number-of-0-and-1-in-binary/
	int numberOfStepsV2 (int num) {
		if(!num) return 0;
        int res = 0;
        while(num) {
            res += (num & 1) ? 2 : 1;
            num >>= 1;
        }
        return res - 1;
    }
};

// Approach 2 (Built-In)
class SolutionBuiltIn {
public:
    int numberOfSteps (int num) {
        return num ? log2(num) + bitset<32>(num).count() : 0;
    }
};

// Approach 3 (Built-In)
class SolutionBuiltInTwo {
public:
    int numberOfSteps (int num) {
        return num ? log2(num) + __builtin_popcount(num) : 0;
    }
};

// Approach 4 (Built-In)
class SolutionBuiltInThree {
public:
    int numberOfSteps (int num) {
        return num ? 31 - __builtin_clz(num) + bitset<32>(num).count() : 0;
    }
};

// Approach 5 (Built-In)
class SolutionBuiltInFive {
public:
    int numberOfSteps (int num) {
        return num ? 31 - __builtin_clz(num) + __builtin_popcount(num) : 0;
    }
};

// OR:
//return num ? __builtin_popcount(num) + 31 - __builtin_clz(num) : 0;

int main()
{
	return 0;
}
