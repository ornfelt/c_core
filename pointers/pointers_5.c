#include<stdio.h>
#include <stdlib.h>

// OBS: char **argv Is equivalent to char *argv[]
int main(int argc, char* argv[])
//int main(int argc, char** argv)
{
    int counter;
    printf("Program Name Is: %s",argv[0]);
    if(argc==1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if(argc>=2)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\n----Following Are The Command Line Arguments Passed----");
        for(counter=0; counter < argc; counter++)
            printf("\nargv[%d]: %s", counter, argv[counter]);
    }
	
	 
	/**
https://stackoverflow.com/questions/5580761/why-use-double-indirection-or-why-use-pointers-to-pointers
	1. char *ch - (called character pointer)
	- ch contains the address of a single character.
	- (*ch) will dereference to the value of the character.. 
	
	2. char **ch -
	'ch' contains the address of an Array of character pointers. (as in 1)
	'*ch' contains the address of a single character. (Note that it's different from 1, due to difference in declaration).
	(**ch) will dereference to the exact value of the character..

	Adding more pointers expand the dimension of a datatype, from character to string, to array of strings, and so on... You can relate it to a 1d, 2d, 3d matrix..
	*/
	
	char **p;
    p = (char **)malloc(100);
    p[0] = (char *)"Apple";      	// or write *p, points to location of 'A'
    p[1] = (char *)"Banana";     	// or write *(p+1), points to location of 'B'

    //cout << *p << endl;          	//Prints the first pointer location until it finds '\0'
    //cout << **p << endl;         	//Prints the exact character which is being pointed
	
	printf("\n\n*p: %s\n", *p);		//Prints the first pointer location until it finds '\0'
	printf("*(p+1): %s\n", *(p+1));	//Prints the exact character which is being pointed
    *p++;                        	//Increments for the next string
	printf("*p after increment: %s\n", *p);
    //cout << *p;
	
	
    return 0;
}
// gcc .\pointers_5.c; .\a.exe -1 -2