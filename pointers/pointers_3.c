/**
FROM: https://stackoverflow.com/questions/5580761/why-use-double-indirection-or-why-use-pointers-to-pointers

If you want to have a list of characters (a word), you can use char *word
If you want a list of words (a sentence), you can use char **sentence
If you want a list of sentences (a monologue), you can use char ***monologue
If you want a list of monologues (a biography), you can use char ****biography
If you want a list of biographies (a bio-library), you can use char *****biolibrary
If you want a list of bio-libraries (a ??lol), you can use char ******lol
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wordsinsentence(char **x) {
    int w = 0;
    while (*x) {
        w += 1;
        x++;
    }
    return w;
}

int wordsinmono(char ***x) {
    int w = 0;
    while (*x) {
        w += wordsinsentence(*x);
        x++;
    }
    return w;
}

int wordsinbio(char ****x) {
    int w = 0;
    while (*x) {
        w += wordsinmono(*x);
        x++;
    }
    return w;
}

int wordsinlib(char *****x) {
    int w = 0;
    while (*x) {
        w += wordsinbio(*x);
        x++;
    }
    return w;
}

int wordsinlol(char ******x) {
    int w = 0;
    while (*x) {
        w += wordsinlib(*x);
        x++;
    }
    return w;
}

int main(void) {
    char *word;
    char **sentence;
    char ***monologue;
    char ****biography;
    char *****biolibrary;
    char ******lol;

    // fill data structure
	// The malloc() function reserves a block of memory of the specified number of bytes.
	// And, it returns a pointer of void which can be casted into pointers of any form
    word = malloc(4 * sizeof *word); // assume it worked
	char *word2;
	char *word3;
	word2 = malloc(4 * sizeof *word2); // assume it worked
	word3 = malloc(4 * sizeof *word3); // assume it worked
    strcpy(word, "foo");
	strcpy(word2, "bar");
	strcpy(word3, "xzy");

    sentence = malloc(4 * sizeof *sentence); // assume it worked
    sentence[0] = word;
    sentence[1] = word2;
    sentence[2] = word3;
    sentence[3] = NULL;

    monologue = malloc(4 * sizeof *monologue); // assume it worked
    monologue[0] = sentence;
    monologue[1] = sentence;
    monologue[2] = sentence;
    monologue[3] = NULL;

    biography = malloc(4 * sizeof *biography); // assume it worked
    biography[0] = monologue;
    biography[1] = monologue;
    biography[2] = monologue;
    biography[3] = NULL;

    biolibrary = malloc(4 * sizeof *biolibrary); // assume it worked
    biolibrary[0] = biography;
    biolibrary[1] = biography;
    biolibrary[2] = biography;
    biolibrary[3] = NULL;

    lol = malloc(4 * sizeof *lol); // assume it worked
    lol[0] = biolibrary;
    lol[1] = biolibrary;
    lol[2] = biolibrary;
    lol[3] = NULL;

    printf("total words in my lol: %d\n", wordsinlol(lol));
	
	printf("word: %c\n", *(word));
	printf("word+1: %c\n", *(word+1));
	printf("word+2: %c\n", *(word+2));
	printf("lol: %c\n", ******lol);
	
	// char **sentence;
    // char ***monologue;
    // char ****biography;
    // char *****biolibrary;
    // char ******lol;
	printf("\nsentence: %c\n", sentence[0][0]);
	printf("monologue: %c\n", monologue[1][1][2]);
	printf("biography: %c\n", biography[1][1][2][2]);
	printf("biolibrary: %c\n", biolibrary[1][1][2][2][0]);
	printf("lol: %c\n", lol[1][1][2][2][0][1]);
	
	printf("\nsen: %s\n", *(sentence));
	printf("mon: %s\n", **(monologue));
	printf("lol: %s\n", *****(lol));
	
    free(lol);
    free(biolibrary);
    free(biography);
    free(monologue);
    free(sentence);
    free(word);
	free(word2);
	free(word3);
}
