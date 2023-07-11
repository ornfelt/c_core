#include<iostream>
#include <bitset> // To print in bit representation
using namespace std;

/**
	https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
*/

/**
	1)
	How to set a bit in the number ‘num’:
	If we want to set a bit at nth position in the number ‘num’, it can be done using the
	‘OR’ operator( | ).  

    First, we left shift ‘1’ to n position via (1<<n)
	Then, use the ‘OR’ operator to set the bit at that position. ‘OR’ operator is used
	because it will set the bit even if the bit is unset previously in the binary
	representation of the number ‘num’.
	Note: If the bit would be already set then it would remain unchanged.
*/
// num is the number and pos is the position
// at which we want to set the bit.
void set(int &num, int pos)
{
	// First step is shift '1', second step is bitwise OR
	num |= (1 << pos);
}

/**
	2. How to unset/clear a bit at n'th position in the number 'num': 
	Suppose we want to unset a bit at nth position in number ‘num’ then we have to do this
	with the help of ‘AND’ (&) operator.

	First, we left shift ‘1’ to n position via (1<<n) then we use bitwise NOT operator ‘~’
	to unset this shifted ‘1’. Now after clearing this left shifted ‘1’ i.e making it to
	‘0’ we will ‘AND'(&) with the number ‘num’ that will unset bit at nth position.
*/

// First step is to get a number that has all 1's except the given position.
void unset(int &num, int pos)
{
    //Second step is to bitwise and this number with given number
    num &= (~(1 << pos));
}

/**
	3.  Toggling a bit at nth position:
	Toggling means to turn bit ‘on'(1) if it was ‘off'(0) and to turn ‘off'(0) if it was
	‘on'(1) previously. We will be using the ‘XOR’ operator here which is this ‘^’. The
	reason behind the ‘XOR’ operator is because of its properties. 

    Properties of ‘XOR’ operator. 
        1^1 = 0
        0^0 = 0
        1^0 = 1
        0^1 = 1
	If two bits are different then the ‘XOR’ operator returns a set bit(1) else it returns
	an unset bit(0).
*/

// First step is to shift 1,Second step is to XOR with given number
void toggle(int& num, int pos) { num ^= (1 << pos); }

/**
	4. Checking if bit at nth position is set or unset: 
	It is quite easily doable using the ‘AND’ operator.
    Left shift ‘1’ to given position and then ‘AND'(‘&’).
	
	Observe that we have first left shifted ‘1’ and then used ‘AND’ operator to get bit at
	that position. So if there is ‘1’ at position ‘pos’ in ‘num’, then after ‘AND’ our
	variable ‘bit’ will store ‘1’ else if there is ‘0’ at position ‘pos’ in the number
	‘num’ than after ‘AND’ our variable bit will store ‘0’.
*/

bool at_position(int num, int pos)
{
    bool bit = num & (1 << pos);
    return bit;
}

// 8. Getting the lowest set bit of a number:
/**
	This is done by using the expression ‘X &(-X)’ Let us see this by taking an example:
	Let X = 00101100. So ~X(1’s complement) will be ‘11010011’ and 2’s complement will be
	(~X+1 or -X) i.e.  ‘11010100’.So if we ‘AND’ original number ‘X’ with its two’s
	complement which is ‘-X’, we get the lowest set bit.
*/
int lowest_set_bit(int num)
{
    int ret = num & (-num);
    return ret;
}

// Main
int main()
{
	// 1 How to set a bit in the number 'num':
	cout << "num = 4, pos = 1, set(num, pos) How to set a bit in the number 'num':" << endl;
    int num = 4, pos = 1;
	cout << "num in bits: " << bitset<8>(num) << endl;
    set(num, pos);
    cout << (int)(num) << endl;
	cout << "num in bits: " << bitset<8>(num) << endl;
	cout << endl;
	 
	// 2. How to unset/clear a bit at n'th position in the number 'num': 
	cout << "num = 7, pos = 1, unset(num, pos) How to unset/clear a bit at n'th position in the number 'num': " << endl;
	num = 7;
    pos = 1;
    unset(num, pos);
    cout << num << endl;
	cout << endl;
	
	// 3.  Toggling a bit at nth position:
	cout << "num = 4, pos = 1, toggle(num, pos) Toggling a bit at nth position:" << endl;
	num = 4;
    pos = 1;
    toggle(num, pos);
    cout << num << endl;
	cout << endl;
	
	// 4. Checking if bit at nth position is set or unset: 
	cout << "num = 5, pos = 0, bool bit = at_position(num, pos) Checking if bit at nth position is set or unset:" << endl;
	num = 5;
    pos = 0;
    bool bit = at_position(num, pos);
    cout << bit << endl;
	cout << endl;
	
	// 5. Inverting every bit of number num (will be -5):
	num = 4;
	cout << "num = 4, Inverting every bit of number num:" << endl;
    cout << (~num) << endl;
	cout << endl;
	
	// 6. Two's complement of the number: 2’s complement of a number is 1’s complement + 1.
	// We can have 2’s complement by finding 1s complement and adding 1 to the result i.e (~num+1) or what else we can do is using '-' operator.
	cout << "num = 4, 2's complement (two different ways:)" << endl;
	num = 4;
	int twos_complement = -num;
    cout << "This is two's complement " << twos_complement << endl;
    cout << "This is also two's complement " << (~num+1) << endl;
	cout << endl;
	
	// 7. Stripping off the lowest set bit:
	// In many situations we want to strip off the lowest set bit for example in Binary Indexed tree data structure, counting number of set bit in a number. We do something like this: 
	cout << "num = 12, stripping off the lowest set bit:" << endl;
	num = 12;
	num = num & (num-1);
	// Logic: how does it even work? Let us see this by taking an example, let X = 1100.
	// (X-1)  inverts all the bits till it encounters the lowest set '1' and it also inverts that lowest set '1'. Then X-1 becomes 1011. After 'ANDing' X with X-1 we get the lowest set bit stripped.
	// can be made into function: void strip_last_set_bit(int &num) { num = num & (num-1); }
	cout << endl;
	
	// 8. Getting the lowest set bit of a number:
	cout << "num = 10, int ans = lowest_set_bit(num) Getting the lowest set bit of a number:" << endl;
	num = 10;
	//num = 20;
	cout << "num in bits: " << bitset<8>(num) << endl;
    int ans = lowest_set_bit(num);
    cout << ans << endl;
	cout << "ans in bits: " << bitset<8>(ans) << endl;
	cout << endl;

	cout << "end" << endl;
	
    return 0;
}
