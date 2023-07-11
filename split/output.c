#include <stdio.h>
#include "output.h"

void printOptions()
{
	int numOfArtists = 6, i = 0;
	printf("Who is your favourite artist?\n");
	const char* artists[numOfArtists];

	artists[0] = "a";
	artists[1] = "b";
	artists[2] = "c";
	artists[3] = "d";
	artists[4] = "e";
	artists[5] = "f";

	for (i = 0; i < numOfArtists; i++){
		printf("%d) %s\n", i+1, artists[i]);
	}
}

void printCompliment (int choice)
{
	char* compliment;
	switch (choice)
	{

		case 1: compliment = "a is great"; break;
		case 2: compliment = "b is great"; break;
		case 3: compliment = "c is great"; break;
		case 4: compliment = "d is great"; break;
		case 5: compliment = "e is great"; break;
		case 6: compliment = "f is great"; break;
		default: compliment = "Choice doesn't exist"; break;
	}

	printf("Compliment for selected artist: %s\n", compliment);
}
