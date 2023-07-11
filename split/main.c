#include "input.h"
#include "output.h"

// Execute with: gcc -Wall main.c input.c output.c -o main.exe; .\main.exe

/**
	If you have a dependency circle where with files:
	fileA.c fileA.h fileB.c fileB.h fileC.c fileC.h main.c

	where fileA depends on fileB, fileB depends on fileC, and fileC depends on fileA,
	this can occur when you have more header files than you need or if you forget to remove an include after you refactor.

	The error message can be: #include nested too deeply.

	If you wish to use gcc to only recompile input.c for example, you can use object files.
	You then need the following command(s) to create object files:
	gcc -c input.c; gcc -c output.c; gcc -c main.c

	Then:
	gcc main.o input.o output.o -o mainWithObjectiveFiles.exe

 */

int main (void)
{
	printOptions();
	int choice = 0;
	if ((choice = getUserInput())){
		printCompliment(choice);
	}

	return 0;
}
