#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <time.h> // Needed for the usual srand() initialization
#include<tuple>
#include<string> // Used for printSolution
#include <cstring>
#include <climits>

using namespace std;

#define X 4
#define Y 4

// ACTIONS = {'U': (-1, 0), 'D': (1, 0), 'L': (0, -1), 'R': (0, 1)}

// 1 = U, 2 = D, 3 = L, 4 = R
map<int, tuple<int, int>> ACTIONS = {
	{ 1, make_tuple(-1, 0) },
	{ 2, make_tuple(1, 0) },
	{ 3, make_tuple(0, -1) },
	{ 4, make_tuple(0, 1) },
};

class MazeGame {
	public:
	int steps;
	// https://www.geeksforgeeks.org/tuples-in-c/
	tuple <int, int> robotPos;
	tuple <int, int> startPos;
	tuple <int, int> winPos;
	int* env;
	map<tuple<int, int>, int> environment;
	map<tuple<int, int>, vector<int>> allowedStates;

	// Constructor
	MazeGame(int* newEnv)
	{
		setEnv(newEnv);
		robotPos = startPos;
		steps = 0;
		constructAllowedStates();
	}

	// Set environment - slighly shorter than the python version since environment numbers (0,1,2,3) are already set...
	void setEnv(int* newEnv)
	{
		env = newEnv;
		startPos = getIndex(2, env);
		/* cout << "startPos: " << get<0>(startPos) << "," << get<1>(startPos) << endl; */
		winPos = getIndex(3, env);
		/* cout << "winPos: " << get<0>(winPos) << "," << get<1>(winPos) << endl; */
	}

	// Check allowed move from a given state
	bool isAllowedMove(tuple<int, int> state, int action)
	{
		int x = get<0>(state);
		int y = get<1>(state);

		x += get<0>(ACTIONS[action]);
		y += get<1>(ACTIONS[action]);

		// If robot moves off board
		/* if (y < 0 || x < 0 || y > 3 || x > 3) */
		if (y < 0 || x < 0 || y > (Y-1) || x > (X-1))
			return false;
		return true;
	}

	// Set allowed states
	void constructAllowedStates()
	{
		int i, j;
		for(i=0; i < X; i++){
			for(j=0; j < Y; j++){
				for (const auto& kv : ACTIONS){
					/* cout << kv.first << " has value " << get<0>(kv.second) << "," << get<1>(kv.second) << endl; */
					if (isAllowedMove({i, j}, kv.first)) {
						allowedStates[{i,j}].push_back(kv.first);
						// 1 = U, 2 = D, 3 = L, 4 = R
						/* cout << "new allowedStates set: " << kv.first << " for state: " << i << "," << j << endl; */
					}
				}
			}
		}
	}

	// Update the maze with new action
	void updateMaze(int &action)
	{
		/* cout << "updating maze with action: " << action << endl; */
		// Current position
		int x = get<0>(robotPos);
		int y = get<1>(robotPos);

		// New position
		x += get<0>(ACTIONS[action]);
		y += get<1>(ACTIONS[action]);
		get<0>(robotPos) = x;
		get<1>(robotPos) = y;
		steps += 1;
	}

	// Get state and reward is split up into getState and getReward in this c++ version
	tuple<int, int> getState()
	{
		return robotPos;
	}

	// Get reward through giveReward function
	int getReward()
	{
		return giveReward();
	}

	int getEnvPos(tuple<int, int> &pos)
	{
		return (*(env + get<0>(pos)*Y + get<1>(pos)));
	}

	// Give reward based on position
	int giveReward()
	{
        // If won give 1 reward
        /* if (robotPos == winPos) */
        if (isGameOver())
            return 1;
		else if (getEnvPos(robotPos) == 1){
			return -3;
		}
        else 
			return -1;
	}

	// Check if robot in the final position
	bool isGameOver()
	{
		return robotPos == winPos;
	}

	// Get the coordinates of some block in state
	tuple <int, int> getIndex(int block, int* state)
	{
		int i, j;
		for(i=0; i < X; i++){
			for(j=0; j < Y; j++){
				/* printf("%d ", *(matrix + i*Y + j)); // or better: printf("%d ", *matrix++); */
				if (*(state + i*Y + j) == block){
					return make_tuple(i, j);
				}
			}
		}
		return make_tuple(0, 0);
	}
};

class Robot {
	public:
	float epsilon;
	float eMin;
	int annealingSteps;
	// stateHistory is split up to a vector of tuples and vector of rewards, in python it's: self.state_history = [((0, 0), 0)] # state, reward
	vector<tuple<int, int>> stateHistory;
	vector<int> rewardHistory;
	map<tuple<int, int>, float> qTable;

	// Constructor
	//Robot(vector<tuple<int, int>> states, float newEpsilon)
	Robot(int* states, float newEpsilon)
	{
		//self.state_history = [((0, 0), 0)] // State, reward
		stateHistory.clear();
		rewardHistory.clear();
		epsilon = newEpsilon;
		annealingSteps = 200;
		eMin = 0.01;
		initReward();
	}

	/* void initReward(vector<tuple<int, int>> states) */
	void initReward()
	{
		int i, j;
		for(i = 0; i < X; i++){
			for(j = 0; j < Y; j++){
				//*matrix++ = i+1*j+1; // or better: printf("%d ", *matrix++);
				qTable[{i,j}] =  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				/* cout << "qTable[i,j] set " << i << j << ": " << qTable[make_tuple(i,j)] << endl; */
			}
		}
	}

	int chooseAction(tuple<int, int> &state, vector<int> &allowedMoves)
	{
		int maxG = -10000000000000000;
		int nextMove;
		// np.random.random return random floats in the half-open interval [0.0, 1.0).
		float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		if (randomNumber < epsilon){
			int randMove = rand() % allowedMoves.size();
			nextMove = allowedMoves[randMove];
			/* cout << "nextMove (random): " << nextMove << endl; */
		}
		else {
			// If exploiting, gather all possible actions and choose one with the highest G (reward)
			for (int action : allowedMoves){
				tuple <int, int> newState = {get<0>(state) + get<0>(ACTIONS[action]), get<1>(state) + get<1>(ACTIONS[action])};
				if (qTable[newState] >= maxG){
					nextMove = action;
					maxG = qTable[newState];
				}
			}
			/* cout << "nextMove: " << nextMove << endl; */
		}
		return nextMove;
	}

	// Update statehistory and rewardhistory
	void updateStateHistory(tuple<int, int> &state, int &reward)
	{
		stateHistory.push_back(state);
		rewardHistory.push_back(reward);
	}

	void learn()
	{
		int target = 0;
		float gamma = 0.8;
		float learningRate = 0.3;

		// Reverse history
		for(int i = stateHistory.size() -1 ; i >= 0; i--){
			qTable[stateHistory[i]] = qTable[stateHistory[i]] + learningRate * (target - qTable[stateHistory[i]]);
			target += rewardHistory[i];
		}

		stateHistory.clear();
		rewardHistory.clear();
		if (epsilon > eMin)
			epsilon = epsilon - ((1 - eMin) / annealingSteps);
	}
};

// Function for printing values
void printValues(int* matrix)
{
    int i, j, curr;
    for(i=0; i < X; i++){
        for(j=0; j < Y; j++){
            /* printf("%d ", *(matrix + i*Y + j)); // or better: printf("%d ", *matrix++); */
            /* printf("%d ", *matrix++); // or better: printf("%d ", *matrix++); */

			curr = *matrix++;
			// TODO: create dict to better print APG?
			/* if (curr > 0) */
			if (curr == 1)
				printf("P ");
			else if (curr == 2)
				printf("A ");
			else if (curr == 3)
				printf("G ");
			else
				printf("%d ", curr);
        }
        printf("\n");
    }
}

map<char, int> actionPos = {
	{ 'U', -5 },
	{ 'D', 5 },
	{ 'L', -1 },
	{ 'R', 1 },
};

/* map<char, char> actionChar = { */
/* 	{ 'U', '\u2191' }, */
/* 	{ 'D', '\u2193' }, */
/* 	{ 'L', '\u2190' }, */
/* 	{ 'R', '\u2192' }, */
/* }; */
map<char, char> actionChar = {
	{ 'U', '^' },
	{ 'D', 'v' },
	{ 'L', '<' },
	{ 'R', '>' },
};

int getCharIndex(char searchChar, char* arr, int arrSize)
{
	for(int i = 0; i < arrSize; i++){
		if (*(arr+i) == searchChar)
			return i;
	}
	return 0;
}

string spaced(string str)
{
   if ( str == "" ) return str;

   string result( 2 * str.size() - 1, ' ' );
   for ( int i = 0, j = 0; i < str.size(); i++, j+=2 ) result[j] = str[i];
   return result;
}

void printSolution(int* env, vector<char> &actionList)
{
	string envString = "";
    int i, j, curr;
    for(i=0; i < X; i++){
        for(j=0; j < Y; j++){
			curr = *env++;
			// TODO: create dict to better print APG?
			if (curr == 1)
				envString += "P";
			else if (curr == 2)
				envString += "A";
			else if (curr == 3)
				envString += "G";
			else
				envString += "0";
        }
		envString += '\n';
    }
	string spacedEnvString = spaced(envString);
	// Fix ugly spaces...
	spacedEnvString.erase(9, 1);
	spacedEnvString.erase(18, 1);
	spacedEnvString.erase(27, 1);
	cout << "Environment:\n" << spacedEnvString << endl;

	char envStringArr[envString.length()+1];
	strcpy(envStringArr, envString.c_str());

	/* int aPosition = getCharIndex('A', envStringArr, envString.length()+1); */
	// Same as getCharIndex function:
	int aPosition = strchr(envStringArr, 'A') - envStringArr;

	int currPosition = aPosition;
	/* cout << "A POS: " << aPosition << endl; */
	for (char action : actionList){
		currPosition += actionPos[action];
		envStringArr[currPosition] = actionChar[action];
	}

	string spacedEnvStringArr = spaced(envStringArr);
	// Fix ugly spaces...
	spacedEnvStringArr.erase(9, 1);
	spacedEnvStringArr.erase(18, 1);
	spacedEnvStringArr.erase(27, 1);
	cout << "Solution:\n" << spacedEnvStringArr << endl;
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
	int cleanState[X][Y] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    updateArr(state, cleanState[0]);
	// List of elements to place out
	/* vector<int> elementVector = {3, 2, 1, 1}; */
	vector<int> elementVector = {3, 2, 1, 1, 1, 1, 1, 1};

	int randPos, randEle, randRow, randCol;
	while (elementVector.size() > 0){
		randPos = rand() % elementVector.size();
		randEle = elementVector[randPos];
		elementVector.erase(elementVector.begin() + randPos);

		// Get random col coordinate (0-3)
		randRow = (rand() % ((X-1) - 0 + 1));
		// Get random col coordinate (0-3)
		randCol = (rand() % ((Y-1) - 0 + 1));
		while (*(state + randRow*Y + randCol) != 0){
			randRow = (rand() % ((X-1) - 0 + 1));
			randCol = (rand() % ((Y-1) - 0 + 1));
		}
		*(state + randRow*Y + randCol) = randEle;
	}
}

vector<pair<int, int>> getBlockIndexes(int block, int* state)
{
	vector<pair<int, int>> result;

    int i, j;
    for(i=0; i < X; i++){
        for(j=0; j < Y; j++){
			if (*state++ == block)
				result.push_back({i, j});
        }
    }
	return result;
}

// Check if it is possible to go to (x, y) from the current position. The
// function returns false if the cell has value 0 or already visited
bool isSafe(vector<vector<int>> &mat, vector<vector<bool>> &visited, int x, int y)
{
	return (x >= 0 && x < mat.size() && y >= 0 && y < mat[0].size()) &&
			mat[x][y] == 1 && !visited[x][y];
}

void findShortestPath(vector<vector<int>> &mat, vector<vector<bool>> &visited,
				int i, int j, int x, int y, int &min_dist, int dist){
	if (i == x && j == y){
		min_dist = min(dist, min_dist);
		return;
	}
	// set (i, j) cell as visited
	visited[i][j] = true;
	// go to the bottom cell
	if (isSafe(mat, visited, i + 1, j)) {
		findShortestPath(mat, visited, i + 1, j, x, y, min_dist, dist + 1);
	}
	// go to the right cell
	if (isSafe(mat, visited, i, j + 1)) {
		findShortestPath(mat, visited, i, j + 1, x, y, min_dist, dist + 1);
	}
	// go to the top cell
	if (isSafe(mat, visited, i - 1, j)) {
		findShortestPath(mat, visited, i - 1, j, x, y, min_dist, dist + 1);
	}
	// go to the left cell
	if (isSafe(mat, visited, i, j - 1)) {
		findShortestPath(mat, visited, i, j - 1, x, y, min_dist, dist + 1);
	}
	// backtrack: remove (i, j) from the visited matrix
	visited[i][j] = false;
}

// Wrapper over findShortestPath() function
int findShortestPathLength(vector<vector<int>> &mat, pair<int, int> &src,
					pair<int, int> &dest){
	if (mat.size() == 0 || mat[src.first][src.second] == 0 ||
			mat[dest.first][dest.second] == 0)
		return -1;
	
	int row = mat.size();
	int col = mat[0].size();
	// construct an `M × N` matrix to keep track of visited cells
	vector<vector<bool>> visited;
	visited.resize(row, vector<bool>(col));

	int dist = INT_MAX;
	findShortestPath(mat, visited, src.first, src.second, dest.first, dest.second,
			dist, 0);

	if (dist != INT_MAX)
		return dist;
	return -1;
}


bool isSolveable(int* state)
{
	vector<vector<int>> mat = {
	{1, 1, 1, 1 },
	{1, 1, 1, 1 },
	{1, 1, 1, 1 },
	{1, 1, 1, 1 }};

	vector<pair<int, int>> pitIndexes = getBlockIndexes(1, state);
	for (pair<int, int> pit : pitIndexes){
		mat[pit.first][pit.second] = 0;
		/* cout << "new mat val: " << mat[pit.first][pit.second] << " for: " << pit.first << "," << pit.second << endl; */
	}

	vector<pair<int, int>> startIndex = getBlockIndexes(2, state);
	vector<pair<int, int>> endIndex = getBlockIndexes(3, state);
	/* pair<int, int> start = make_pair(0, 3); */
	pair<int, int> start = {startIndex[0].first, startIndex[0].second};
	pair<int, int> end = {endIndex[0].first, endIndex[0].second};
	cout << "start: " << start.first << "," << start.second << endl;
	cout << "end: " << end.first << "," << end.second << endl;

	int dist = findShortestPathLength(mat, start, end);
	if (dist != -1)
		cout << "Shortest Path is " << dist << endl;
	else {
		cout << "Shortest Path doesn't exist" << endl;
		return false;
	}

	return true;
}

// Main code
int main() {
	int isRandomMaze = 1;
	// Before calling rand(), you must first "seed" the random number generator by calling srand()
	srand (static_cast <unsigned> (time(0)));
	// 1 = P, 2 = A, 3 = G
	// ExampleEnvironment = [['','','','A'],['','','P','P'],['','','',''],['','','','G']]
    int currentEnv[X][Y] = {{0, 0, 0, 2}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 3}};
    /* int currentEnv[X][Y] = {{0, 2, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {1, 0, 0, 3}}; */
    /* int currentEnv[X][Y] = {{0, 0, 0, 3}, {0, 1, 1, 1}, {0, 0, 1, 0}, {1, 0, 0, 2}}; */
	// 5x5
    /* int currentEnv[X][Y] = {{0, 0, 0, 0, 2}, {0, 0, 0, 1, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 3}}; */

	if (isRandomMaze){
		genRandomState(currentEnv[0]);
		if (isSolveable(currentEnv[0]))
			cout << "Is solveable!" << endl;
		else {
			cout << "Not solvable maze. Generating new..." << endl;
			do {
				genRandomState(currentEnv[0]);
			} while (!isSolveable(currentEnv[0]));
		}
	}

	cout << endl;
	printValues(currentEnv[0]);
	cout << endl;

	MazeGame *maze = new MazeGame(currentEnv[0]);
	Robot *robot = new Robot(currentEnv[0], 1.0);
	vector<int> moveHistory;
	vector<char> actionList;
	tuple<int, int> state;
	int action;
	int reward;

	for(int i = 0; i < 2000; i++){
		while (!maze->isGameOver()){
			// Get state
			state = maze->getState();
			/* cout << "state: " << get<0>(state) << "," << get<1>(state) << endl; */
			// Choose explore or exploit action
			action = robot->chooseAction(state, maze->allowedStates[state]);
			// Print last set of actions
			if (i == 999){
				/* cout << "action (999): " << action << endl; */
				// 1 = U, 2 = D, 3 = L, 4 = R
				if (action == 1) {
					cout << "action (999): U" << endl;
					actionList.push_back('U');
				}
				else if (action == 2) {
					cout << "action (999): D" << endl;
					actionList.push_back('D');
				}
				else if (action == 3) {
					cout << "action (999): L" << endl;
					actionList.push_back('L');
				}
				else if (action == 4) {
					cout << "action (999): R" << endl;
					actionList.push_back('R');
				}
			}
			// Update the maze according to the action
			maze->updateMaze(action);
			// Update state and reward
			state = maze->getState();
			reward = maze->getReward();
			robot->updateStateHistory(state, reward);

			// If robot falls into pit, reset position
			if (maze->getEnvPos(maze->robotPos) == 1){
				maze->robotPos = maze->startPos;
			}
			// End if robot takes too long...
			if (maze->steps > 1000)
				break;
		}

		// Teach robot after reach game
		robot->learn();
		moveHistory.push_back(maze->steps);
		delete maze;
		maze = new MazeGame(currentEnv[0]);
	}

	cout << "Solution length: " << actionList.size() << endl << endl;
	printSolution(currentEnv[0], actionList);

	moveHistory.clear();
	actionList.clear();

	delete maze;
	delete robot;
	cout << "END" << endl;

	return 0;
}
