// FROM: https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/

/*
* argv[argc] is a NULL pointer.
* argv[0] holds the name of the program.
* argv[1] points to the first command line argument and argv[n] points last argument.
*/

// Name of program mainreturn.cpp
#include <iostream>
using namespace std;
  
int main(int argc, char** argv)
{
    cout << "You have entered " << argc
         << " arguments:" << "\n";
  
    for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";
  
    return 0;
}

// $ g++ mainreturn.cpp -o main 
// $ ./main geeks for geeks

// ---------------------------------------------------------------------------------------------------

// C program to illustrate
// command line arguments
#include<stdio.h>
  
int main2(int argc,char* argv[])
{
    int counter;
    printf("Program Name Is: %s",argv[0]);
    if(argc==1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if(argc>=2)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\n----Following Are The Command Line Arguments Passed----");
        for(counter=0;counter<argc;counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
    }
    return 0;
}

