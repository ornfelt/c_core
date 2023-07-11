// FROM: https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
#include <iostream>
using namespace std;

// Function to return the only odd occurring element
int findOdd(int arr[], int n)
{
    int res = 0, i;
    for (i = 0; i < n; i++)
        res ^= arr[i];
    return res;
}
 
int main() {
    // a = 5(00000101), b = 9(00001001)
    int a = 5, b = 9;
 
    // The result is 00000001
    cout<<"a = " << a <<","<< " b = " << b <<endl;
    cout << "a & b = " << (a & b) << endl;
 
    // The result is 00001101
    cout << "a | b = " << (a | b) << endl;
 
    // The result is 00001100
    cout << "a ^ b = " << (a ^ b) << endl;
 
    // The result is 11111010
    cout << "~a = " << (~a) << endl;
 
    // The result is 00010010
    cout<<"b << 1" <<" = "<< (b << 1) <<endl;
 
    // The result is 00000100
    cout<<"b >> 1 "<<"= " << (b >> 1 )<<endl;
	
	// FIND ODD
	int arr[] = { 12, 12, 14, 90, 14, 14, 14 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "The odd occurring element is  "<< findOdd(arr, n);
 
    return 0;
}
 