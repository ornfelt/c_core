#include<iostream> 
using namespace std;

// argc stands for argument count and argv stands for argument values. These are variables passed to the main function when it starts executing. When we run a program we can give arguments to that program like: ./a.out hello

// Here hello is an argument to the executable. This can be accessed in your program. For example,
int main(int argc, char** argv) { 
	cout << "This program has " << argc << " arguments:" << endl; 
    for (int i = 0; i < argc; ++i) { 
        cout << argv[i] << endl; 
    } 
    return 0;
}
// g++ arg.cpp -o main 
// ./main geeks for geeks

// OBS: char **argv Is equivalent to char *argv[]