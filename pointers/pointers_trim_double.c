#include <stdio.h>
#include <string.h>

// gcc pointers_trim_double.c; .\a.exe

void removeLeadingSpaces(char** s) {
    while (**s == ' ') {
        (*s)++;
    }
}

void removeSpaces(char** s) {
    int i = 0, j = 0;
    while ((*s)[i]) {
        if ((*s)[i] != ' ') {
            (*s)[j++] = (*s)[i];
        }
        i++;
    }
    (*s)[j] = '\0';
}

void removeSpacesAlternative(char** s) {
    char* dst = *s;
    char* src = *s;
    while (*src) {
        if (*src != ' ') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

// OBS: char **argv Is equivalent to char *argv[]
int main(int argc, char* argv[])
//int main(int argc, char** argv)
{
    int counter;
    printf("Program Name Is: %s",argv[0]);
    if(argc==1)
        printf("\nNo extra command line argument passed other than program name");
    if(argc>=2)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\n----The following are the command line arguments passed----");
        for(counter=0;counter<argc;counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
    }

    char original[] = "  h e l   l o ";
    char testArray[sizeof(original)];
    char* test = testArray;

    // Copy original string into testArray
    strcpy(testArray, original);
    printf("Original: '%s'\n", test);
    removeLeadingSpaces(&test);
    printf("After removeLeadingSpaces: '%s'\n", test);

    // Reset test for next function
    strcpy(testArray, original);  // Re-copy original string
    test = testArray;             // Reset test pointer
    printf("Reset: '%s'\n", test);
    removeSpaces(&test);
    printf("After removeSpaces: '%s'\n", test);

    // Reset test for final function
    strcpy(testArray, original);  // Re-copy original string
    test = testArray;             // Reset test pointer
    printf("Reset: '%s'\n", test);
    removeSpacesAlternative(&test);
    printf("After removeSpacesAlternative: '%s'\n", test);
}