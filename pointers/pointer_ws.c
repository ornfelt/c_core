#include<stdio.h>
#include <ctype.h>


// FROM: https://stackoverflow.com/questions/31036058/removing-spaces-from-string-using-pointers
void remove_whitespace_single(char *s)
{
	char *rd; // "read" pointer
	char *wr; // "write" pointer

	rd = wr = s; // initially, both read and write pointers point to beginning of string

	while ( *rd != 0 ) // while not at end of string
	{
	while ( isspace( *rd ) ) // while rd points to a whitespace character
		rd++;                  // advance rd
	*wr++ = *rd++;           // copy *rd to *wr, advance both pointers
	}
	*wr = 0;                   // terminate the result

	printf("squished: %s\n", s);
}

// Remove whitespace using double pointer
void remove_whitespace(char **s)
{
    char *rd; // "read" pointer
    char *wr; // "write" pointer
    rd = wr = *s; 

    while (*rd != 0) // while not at end of string
    {
    while (isspace((unsigned char)*rd)) // while rd points to a whitespace character
        rd++; // advance rd
    *wr++ = *rd++; // copy *rd to *wr, advance both pointers
    }
    *wr = 0; // terminate the result

    printf("\nsquished: %s\n", *s);
}

void test(char* s)
{
	printf("\n-----------------------------\n");
	printf("String: %s\n", s);
	remove_whitespace(&s);
	printf("String: %s\n", s);
}

//int main(int argc, char* argv[])
int main(int argc, char** argv)
{
	// Remove whitespace using double pointers
    //char* x = "asdas das as \r dfds \n dsa \t"; // This doesn't work (can't change string literal)
    //char x[] = "  1  2 3 "; // This works
	//remove_whitespace_single(x);

    //char* z = "asdas das as \r dfds \n dsa \t"; // This doesn't work (can't change string literal)
    //char* z = "a s d  "; // This doesn't work (can't change string literal)
    //char z[] = "asdas das as \r dfds \n dsa \t"; // This works (maybe bad example cause "String:" gets removed from print somehow...
    char z[] = "a s d  x "; // This works
    char *ws_test = z;
	test(ws_test);

	// This works:
	//printf("%s",*argv);
	//remove_whitespace(argv);

	// Try this with:
	// gcc -Wall pointer_ws.c; ./a.exe " 1  2 3 "
	//test(argv[1]);
}
