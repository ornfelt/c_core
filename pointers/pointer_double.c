#include<stdio.h>

void removeLeadingSpaces(char** s)
{
   int i;
   for(i = 0; *s[i] == ' '; i++);     
		*s = *s + i;
}

void removeSpace(char** s)
{
	int i;
	for(i = 0; (*s)[i]; i++) {
		if ((*s)[i] == ' ')
		printf("Looping: %c", (*s)[i]);
			/* *s = *s + i; */
   }
}

void removeSpaces(char** s)
{
    char* cpy = *s;
	printf("\ncpy: %c\n", *(cpy+1));

	int i = 0, j = 0;
    for (char* s2 = *s; *(s2+i); i++) {
        if (*(s2+i) != ' ') {
			printf("\n*(s2+i): %c", *(s2+i));
			//printf("\n*(*s+j++): %c", *(*s+j++));
			//printf("\ncmon: %c", *(*s+1));

            /* *(*s+j++) = *(s2+i); */
			(*s) = s2;
		}
    }
}

//void removeSpacesFinal(char*& s)
void removeSpacesFinal(char** s)
{
    char* s2 = s;
	int i;
    do {
        if (*s2 != ' ')
            *s++ = *s2;
    } while (*s2++);
}

void removeSpacesTest(char** s)
{
    while (**s != ' ') {
			(*s)++;
	}
}
  
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
        for(counter=0;counter<argc;counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
    }

	char* test = "  h e l   l o ";
	printf("\ntest: %s\n", test);
	removeLeadingSpaces(&test);
	printf("\ntest: %s\n", test);
	//removeSpaces(&test);
	//removeSpacesTest(&test);
	removeSpacesFinal(&test);
	printf("\ntest: %s\n", test);

    return 0;
}
