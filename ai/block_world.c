#include <stdio.h>
#include <stdlib.h>
#include <time.h> // needed for the usual srand() initialization

#define X 3
#define Y 3

// Function for printing values
void printValues(int* matrix){
    int i, j, curr;
    for(i=0; i < X; i++){
        for(j=0; j < Y; j++){
            /* printf("%d ", *(matrix + i*Y + j)); // or better: printf("%d ", *matrix++); */
            /* printf("%d ", *matrix++); // or better: printf("%d ", *matrix++); */

			curr = *matrix++;
			// TODO: create dict to better print ABC?
			/* if (curr > 0) */
			if (curr == 1)
				printf("A ");
			else if (curr == 2)
				printf("B ");
			else if (curr == 3)
				printf("C ");
			else
				printf("%d ", curr);
        }
        printf("\n");
    }
}

// Function for enter values
void enterValues(int* matrix){
    int i, j;
    for(i = 0; i < X; i++){
        for(j = 0; j < Y; j++){
            /* *(matrix + i*Y + j) = i+1*j+1; // or better: printf("%d ", *matrix++); */
            *matrix++ = i+1*j+1; // or better: printf("%d ", *matrix++);
        }
    }
}

// Check if game won (1 = won, 0 = not won)
int hasWon(int* state, int* goalState)
{
    int i, j;
    for(i = 0; i < X; i++){
        for(j = 0; j < Y; j++){
			if (*state++ != *goalState++)
				return 0;
        }
    }
	return 1;
}

// Try to pick up block at given coordinates. Returns 0 if fail, or value of coords if success
int pickUpBlockAt(int row, int col, int* state)
{
	// Check if there is a block that can be picked up
	// Not required since the last line will return 0 either way if it is indeed 0...
	//if (*(state + row*Y + col) == 0)
	//	return 0;

	// Check if there are blocks above
	if (row == 2 && (*(state + 0*Y + col) > 0 || *(state + 1*Y + col) > 0)){
		return 0;
	}
	else if (row == 1 && (*(state + 0*Y + col) > 0)){
		return 0;
	}
	else
		return *(state + row*Y + col);
}

// Try to drop  block at given coordinates. Returns 0 if fail, or value of coords if success
int dropBlockAt(int row, int col, int block, int* state)
{
	// Return 0 if busy slot
	if (*(state + row*Y + col) != 0)
		return 0;
	// If trying to place at top - fall to bottom if no blocks at row 2 and 1
	if (row == 0 && *(state + 2*Y + col) == 0 && *(state + 1*Y + col) == 0)
		*(state + 2*Y + col) = block;
	// If trying to place at top - fall to row 1 if block exists at row 2
	else if (row == 0 && *(state + 1*Y + col) == 0)
		*(state + 1*Y + col) = block;
	// If trying to place at row 1, put on row 2 if no block exists there
	else if (row == 1 && *(state + 2*Y + col) == 0)
		*(state + 2*Y + col) = block;
	else
		*(state + row*Y + col) = block;
	return 1;
}

// Return 1 if successful operation
int operateArm(int r1, int c1, int r2, int c2, int* state)
{
	if (r1 == r2 && c1 == c2)
		return 0;

	// print(f"Attempting to move: {r1},{c1} to {r2}, {c2}\n")
	int currBlock = pickUpBlockAt(r1, c1, state);
	if (currBlock > 0) {
		// Remove block from prev location
		*(state + r1*Y + c1) = 0;
		if (dropBlockAt(r2, c2, currBlock, state))
			return 1;
		else {
			// Add block to prev location again
			*(state + r1*Y + c1) = currBlock;
		}
	}
	return 0;
}

// Update array / state with new state
void updateArr(int* arr, int* newArr)
{
    int i, j;
    for(i = 0; i < X; i++){
        for(j = 0; j < Y; j++){
            *arr++ = *newArr++;
        }
    }
}

// Generate new random startState
void *genRandomState(int *state)
{
	// Clean state (set only 0's)
	int cleanState[X][Y] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    updateArr(state, cleanState[0]); // Or: memcpy(state, newState, sizeof(state));

	// Get random int 1-3 (A, B, C) 
	int randBlock = (rand() % (3 - 1 + 1)) + 1;
	// Get random col coordinate (0-2)
	int randRow = (rand() % (2 - 0 + 1));
	// Get random col coordinate (0-2)
	int randCol = (rand() % (2 - 0 + 1));
	/* printf("\nrandBlock: %d, randRow: %d, randCol: %d\n", randBlock, randRow, randCol); */
	*(state + randRow*Y + randCol) = randBlock;

	// Set second block
	// Make sure to get a new block (not same as the one already set)
	//int newRandBlock = (rand() % (3 - 1 + 1)) + 1;
	//while (randBlock == newRandBlock) newRandBlock = (rand() % (3 - 1 + 1)) + 1;
	int newRandBlock = (randBlock >> 1) == 0 ? randBlock << 1 : randBlock >> 1;
	/* printf("\nrandBlockTwo: %d, randRow: %d, randCol: %d\n", newRandBlock, randRow, randCol); */
	// Make sure to get a new position (not same as the one already set)
	while (*(state + randRow*Y + randCol) != 0){
		randRow = (rand() % (2 - 0 + 1));
		randCol = (rand() % (2 - 0 + 1));
	}
	*(state + randRow*Y + randCol) = newRandBlock;

	// 01, 10, 11
	// XOR magic:::
	newRandBlock ^= randBlock;
	// Make sure to get a new position (not same as the one already set)
	while (*(state + randRow*Y + randCol) != 0){
		randRow = (rand() % (2 - 0 + 1));
		randCol = (rand() % (2 - 0 + 1));
	}
	*(state + randRow*Y + randCol) = newRandBlock;
}

// Get the coordinates of some block in state
int *getIndex(int block, int* state)
{
    int i, j;
	static int idx[2] = {0, 0};
    for(i=0; i < X; i++){
        for(j=0; j < Y; j++){
            /* printf("%d ", *(matrix + i*Y + j)); // or better: printf("%d ", *matrix++); */
			if (*(state + i*Y + j) == block){
				idx[0] = i;
				idx[1] = j;
			}
		}
	}
	return idx;
}

void solveC(int* state)
{
	int *cPos = getIndex(3, state);
	// Check if C is already at correct position
	if (*cPos == 2 && *(cPos+1) == 2)
		return;
	// Try to naively move it to the correct pos
	if (operateArm(*cPos, *(cPos+1), 2, 2, state))
		return;

    // Remove all blocks from col2
	// If there's a block at row 0, col 2
	if (*(state + 0*Y + 2) != 0) {
		// Try to move block from row 0, col 2 -> row 2, col 0
		if (!operateArm(0,2,2,0, state)){
			// Try to move block from row 0, col 2 -> row 1, col 0
			if (!operateArm(0,2,1,0, state))
				// Try to move block from row 0, col 2 -> row 2, col 1
				operateArm(0,2,2,1, state);
		}
	}

	// If there's a block at row 1, col 2
	if (*(state + 1*Y + 2) != 0) {
		if (!operateArm(1,2,2,0, state)){
			if (!operateArm(1,2,1,0, state))
				operateArm(1,2,2,1, state);
		}
	}

	// If there's a block at row 2, col 2
	if (*(state + 2*Y + 2) != 0) {
		if (!operateArm(2,2,2,0, state)){
			if (!operateArm(2,2,1,0, state))
				operateArm(2,2,2,1, state);
		}
	}

	cPos = getIndex(3, state);
	// Update coords of c
    // If any blocks above C, then move those to other column...
	// First try to just move it to the right pos (works if on top (row:0))
	if (operateArm(*cPos, *(cPos+1), 2, 2, state))
		return;

	// If C is in col 0
	if (*(cPos+1) == 0){
		if (*(state + 0*Y + 0) != 0 && *(state + 0*Y + 0) != 3){
			if (!operateArm(0,0,2,1, state))
				operateArm(0,0,1,1, state);
		}

		if (*(state + 1*Y + 0) != 0 && *(state + 1*Y + 0) != 3){
			if (!operateArm(1,0,2,1, state))
				operateArm(1,0,1,1, state);
		}

		cPos = getIndex(3, state);
		if (operateArm(*cPos, *(cPos+1), 2, 2, state)) // Move to correct pos
			return;
	}

	// If C is in col 1
	if (*(cPos+1) == 1){
		if (*(state + 0*Y + 1) != 0 && *(state + 0*Y + 1) != 3){
			if (!operateArm(0,1,2,0, state))
				operateArm(0,1,1,0, state);
		}

		if (*(state + 1*Y + 1) != 0 && *(state + 1*Y + 1) != 3){
			if (!operateArm(1,1,2,0, state))
				operateArm(1,1,1,0, state);
		}

		cPos = getIndex(3, state);
		if (operateArm(*cPos, *(cPos+1), 2, 2, state)) // Move to correct pos
			return;
	}
}

void solveB(int* state)
{
	int *bPos = getIndex(2, state);
	// Check if B is already at correct position
	if (*bPos == 1 && *(bPos+1) == 2)
		return;
	// Try to naively move it to the correct pos
	if (operateArm(*bPos, *(bPos+1), 1, 2, state))
		return;

    // Remove all blocks from col2 (row 0 and 1)
	if (*(state + 0*Y + 2) != 0) {
		if (!operateArm(0,2,2,0, state)){
			if (!operateArm(0,2,1,0, state))
				operateArm(0,2,2,1, state);
		}
	}

	if (*(state + 1*Y + 2) != 0) {
		if (!operateArm(1,2,2,0, state)){
			if (!operateArm(1,2,1,0, state))
				operateArm(1,2,2,1, state);
		}
	}

	bPos = getIndex(2, state);
	// Try to naively move it to the correct pos again
	if (operateArm(*bPos, *(bPos+1), 1, 2, state))
		return;

	// If any blocks above B, then move those to other column...

	// If B is in col 0
	if (*(bPos+1) == 0){
		if (*(state + 0*Y + 0) != 0 && *(state + 0*Y + 0) != 2){
			if (!operateArm(0,0,2,1, state))
				operateArm(0,0,1,1, state);
		}

		if (*(state + 1*Y + 0) != 0 && *(state + 1*Y + 0) != 2){
			if (!operateArm(1,0,2,1, state))
				operateArm(1,0,1,1, state);
		}
		bPos = getIndex(2, state);
		// Try to naively move it to the correct pos again
		if (operateArm(*bPos, *(bPos+1), 1, 2, state))
			return;
	}

	// If B is in col 1
	if (*(bPos+1) == 1){
		if (*(state + 0*Y + 1) != 0 && *(state + 0*Y + 1) != 2){
			if (!operateArm(0,1,2,0, state))
				operateArm(0,1,1,0, state);
		}

		if (*(state + 1*Y + 1) != 0 && *(state + 1*Y + 1) != 2){
			if (!operateArm(1,1,2,0, state))
				operateArm(1,1,1,0, state);
		}

		bPos = getIndex(2, state);
		if (operateArm(*bPos, *(bPos+1), 1, 2, state)) // Move to correct pos
			return;
	}
}

// Solve any game
void solveGame(int* state)
{
	solveC(state);
	solveB(state);

	int *aPos = getIndex(1, state);
	/* printf("aPos: %d,%d\n", *aPos, *(aPos + 1)); */
	// Move A to correct pos
	operateArm(*aPos, *(aPos + 1), 0, 2, state);
}

int main(){
	// A = 1, B = 2, C = 3
    //int state[X][Y] = { {0, 1, 2}, {0, 0, 3}, {0, 0, 0} };
    int state[X][Y] = {{0, 0, 0}, {0, 3, 0}, {2, 1, 0}};
    int goalState[X][Y] = {{0, 0, 1}, {0, 0, 2}, {0, 0, 3}};

	// Using pointers and 2d arrays:
	// arr[i][j] = *(ptr + (i x no_of_cols + j))
	// https://dyclassroom.com/c/c-pointers-and-two-dimensional-array

	printf("\ntestx\n");
    //enterValues(state[0]);
	printf("\nGoal state:\n");
    printValues(goalState[0]);
	printf("\nInitial state:\n");
    printValues(state[0]);

	// Testing for second row...
	//printf("\npickupBlockAt(2,0): %d", pickUpBlockAt(2, 0, state[0]));
	//printf("\npickupBlockAt(2,1): %d", pickUpBlockAt(2, 1, state[0]));
	//printf("\npickupBlockAt(2,2): %d", pickUpBlockAt(2, 2, state[0]));
	//printf("\nhasWon: %d\n", hasWon(state[0], goalState[0]));
	//operateArm(0, 1, 0, 2, state[0]); // Invalid 
	//operateArm(0, 1, 2, 1, state[0]); // Valid 

	// Solution for first start state:
	printf("\nhasWon: %d\n", hasWon(state[0], goalState[0]));
	operateArm(1,1,2,2, state[0]);
	printf("\n");
    printValues(state[0]);

	operateArm(2,0,1,2, state[0]);
	printf("\n");
    printValues(state[0]);

	operateArm(2,1,0,2, state[0]);
	printf("\n");
    printValues(state[0]);
	printf("\nhasWon: %d\n", hasWon(state[0], goalState[0]));

	printf("\n----------------------------------------------------------\nSecond startState\n");
	// Solution for second start state:
    int newState[X][Y] = {{0, 0, 0}, {0, 1, 0}, {2, 3, 0}};
    updateArr(state[0], newState[0]); // Or: memcpy(state, newState, sizeof(state));
    printValues(state[0]);

	operateArm(1,1,1,0, state[0]);
	printf("\n");
    printValues(state[0]);
	operateArm(2,1,2,2, state[0]);
	printf("\n");
    printValues(state[0]);
	operateArm(1,0,2,1, state[0]);
	printf("\n");
    printValues(state[0]);
	operateArm(2,0,1,2, state[0]);
	printf("\n");
    printValues(state[0]);
	operateArm(2,1,0,2, state[0]);
	printf("\n");
    printValues(state[0]);
	printf("\nhasWon: %d\n", hasWon(state[0], goalState[0]));


	printf("\n----------------------------------------------------------\nThird startState:\n");
	// Solution for third start state:
    int newStateTwo[X][Y] = {{0, 0, 2}, {0, 0, 1}, {0, 0, 3}};
    updateArr(state[0], newStateTwo[0]); // Or: memcpy(state, newState, sizeof(state));
    printValues(state[0]);

	operateArm(0,2,2,0, state[0]);
	printf("\n");
    printValues(state[0]);
	operateArm(1,2,2,1, state[0]);
	printf("\n");
    printValues(state[0]);
	operateArm(2,0,1,2, state[0]);
	printf("\n");
    printValues(state[0]);
	operateArm(2,1,0,2, state[0]);
	printf("\n");
    printValues(state[0]);
	printf("\nhasWon: %d\n", hasWon(state[0], goalState[0]));


	printf("\n----------------------------------------------------------\nRandom startState:\n");
	// Solution for Random states:
	// Randomize start value
	srand(time(NULL));
	int hasWonBool = 0;
	int winCounter = 0;
	// 1 million
	/* for(int i = 0; i < 1000000; i++){ */
	// 10 million
	for(int i = 0; i < 10000000; i++){
	// 100 million
	/* for(int i = 0; i < 100000000; i++){ */
	// 1 billion (1 miljard)
	/* for(int i = 0; i < 1000000000; i++){ // Takes a few minutes... */
		genRandomState(state[0]);
		/* printValues(state[0]); */

		solveGame(state[0]);
		//printf("\nhasWon: %d\n", hasWon(state[0], goalState[0]));
		hasWonBool = hasWon(state[0], goalState[0]);
		if (!hasWonBool)
			printf("ERROR!");
		else
			winCounter++;
	}

	printf("Games won: %d!", winCounter);

    return 0;
}
