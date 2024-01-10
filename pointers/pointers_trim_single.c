#include <stdio.h>
#include <string.h>

// gcc pointers_trim_single.c; .\a.exe

void removeLeadingSpaces(char* s) {
    int i, j = 0;
    for (i = 0; s[i] == ' '; i++);
    if (i > 0) {
        while (s[i]) {
            s[j++] = s[i++];
        }
        s[j] = '\0';
    }
}

void removeSpaces(char* s) {
    int i = 0, j = 0;
    while (s[i]) {
        if (s[i] != ' ') {
            s[j++] = s[i];
        }
        i++;
    }
    s[j] = '\0';
}

void removeSpacesAlternative(char* s) {
    char* dst = s;
    while (*s) {
        if (*s != ' ') {
            *dst++ = *s;
        }
        s++;
    }
    *dst = '\0';
}

int main() {
    char test[] = "  h e l   l o ";
    printf("Original: '%s'\n", test);

    removeLeadingSpaces(test);
    printf("After removeLeadingSpaces: '%s'\n", test);

    removeSpaces(test);
    printf("After removeSpaces: '%s'\n", test);

    char test2[] = "  h e l   l o o o ";
    removeSpacesAlternative(test2);
    printf("After removeSpacesAlternative: '%s'\n", test2);

    return 0;
}