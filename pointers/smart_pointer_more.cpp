#include <iostream>
// Dynamic Memory management library
#include <memory>
#include <cassert>

using namespace std;

/**
https://stackoverflow.com/questions/30905487/how-can-i-pass-stdunique-ptr-into-a-function

unique_ptr:
unique_ptr stores one pointer only. We can assign a different
object by removing the current object from the pointer. 

How can I pass std::unique_ptr into a function?

Also see good MS docs: https://learn.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-unique-ptr-instances?view=msvc-170
Also see: https://www.scaler.com/topics/cpp-unique-ptr/
*/

class A
{
	int num;
    public:
    explicit A(int newNum): num{newNum} {}
    int GetVal() {return num;}
    //Destructor
    ~A() {cout <<"Destructor is called"<< endl;}
};

// Pass the smart pointer by reference
void MyFunc(unique_ptr<A> & arg)
{
    cout << arg->GetVal() << endl;
}

// Move the smart pointer into the function argument
void MyFuncTwo(unique_ptr<A> arg)
{
    cout << arg->GetVal() << endl;
}

void MyTestingFunc()
{
	// Pass the smart pointer by reference
    unique_ptr<A> ptr = unique_ptr<A>(new A(1234));
    MyFunc(ptr);
	
	// Move the smart pointer into the function argument
	unique_ptr<A> ptrTwo = unique_ptr<A>(new A(123));
    MyFuncTwo(move(ptrTwo));
    assert(ptrTwo == nullptr);
}

int main(int argc, char* argv[])
{
	cout << "Hello world" << endl;
	MyTestingFunc();
	cout << "End!" << endl;
}
