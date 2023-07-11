#include <stdio.h>
#include "input.h"

int getUserInput()
{
	printf("Enter the number of your favourite artist.\n");
	int choice = 0;
	
	while(1)
	{
		if (scanf("%d", &choice)) {
			if (choice >= 1 && choice <= 6) return choice;
			printf("Please choose a number between 1 and 6.\n");
		} else {
			printf("You must enter a number. Bye!\n");
			return 0;
		}
	}
	return choice;
}
