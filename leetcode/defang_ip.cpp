#include <iostream>

// https://leetcode.com/problems/defanging-an-ip-address/solutions/351240/c-100-faster-solution-with-0ms-runtime/

// Given a valid (IPv4) IP address, return a defanged version of that IP address.
// A defanged IP address replaces every period "." with "[.]".

// Input: address = "1.1.1.1"
// Output: "1[.]1[.]1[.]1"

class Solution {
public:
    string defangIPaddr(string address) {
        string res;
        for(auto c: address) {
            if(c=='.') {
                res+="[.]";
            } else res+=c;
        }
        return res;
    }
	
	// https://leetcode.com/problems/defanging-an-ip-address/solutions/328855/c-1-liner-regex-replace/
	string defangIPaddrRegex(string address) {
		return regex_replace(address, regex("[.]"), "[.]");
	}
};

int main()
{
	return 0;
}