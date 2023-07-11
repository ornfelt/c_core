#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// See first comment on:
// https://leetcode.com/problems/reverse-integer/solutions/4124/8-ms-simple-c-solution-which-checks-overflow/

/**
	Given a signed 32-bit integer x, return x with its digits reversed. 
	If reversing x causes the value to go outside the signed 32-bit 
	integer range [-231, 231 - 1], then return 0.

	Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

	Input: x = 123
	Output: 321
*/

class Solution {
public:
    int reverse(int x) {
       int rev = 0;
       while (x){
           int digit = x % 10;
           x /= 10;
           if ((rev > 0 && rev > (INT_MAX - digit)/10) | (rev < 0 && rev < (INT_MIN - digit)/10)) return 0;
           rev = rev * 10 + digit;
       }
       return rev;
   }
};

int main()
{
	Solution s;
	cout << "Rever int: " << s.reverse(35) << endl;

	return 0;
}

/**
Java version:

public int reverse(int x)
{
    int result = 0;

    while (x != 0)
    {
        int tail = x % 10;
        int newResult = result * 10 + tail;
        if ((newResult - tail) / 10 != result)
        { return 0; }
        result = newResult;
        x = x / 10;
    }

    return result;
}

*/
