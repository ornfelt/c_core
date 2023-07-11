#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <time.h> // needed for the usual srand() initialization

using namespace std;

// THIS: https://stackoverflow.com/questions/2136998/using-a-stl-map-of-function-pointers
typedef int (*playArm)(); // function pointer type
typedef std::map<int, playArm> actions_map;

int roll(int min, int max)
{
	double x = rand()/static_cast<double>(RAND_MAX+1); 
	int that = min + static_cast<int>( x * (max - min) );
	return that;
}

int playArm1() { return roll(10, 60); }
int playArm2() { return roll(12, 51); }
int playArm3() { return roll(18, 26); }
int playArm4() { return roll(-20, 101); }
int playArm5() { return roll(-100, 150); }

map<int, playArm> ACTIONS = {
	{ 1, &playArm1 },
	{ 2, &playArm2 },
	{ 3, &playArm3 },
	{ 4, &playArm4 },
	{ 5, &playArm5 }
};

vector<int> scoreStepTracker;

class Game {
	public:
	int score;
	int steps;
	int newScore;
	// Constructor
	Game()
	{
		score = 0;
		steps = 0;
		newScore = 0;
	}

	// Update game by adding new score and updating steps and score
	void updateGame(int &action)
	{
		// Get score
		newScore = ACTIONS[action]();
		/* printf("\nNew points: %d\n", newScore); */
		score += newScore;
		steps += 1;
	}

	int getReward()
	{
		return giveReward();
	}

	float vectorAverage(std::vector<int> &v){
		if(v.empty()){
			return 0;
		}
		return accumulate( v.begin(), v.end(), 0.0)/v.size();
	}

	// Give reward based on score
	int giveReward()
	{
		if (scoreStepTracker.size() == 1)
			return 0;
		else if (scoreStepTracker.size() > 5 && score > *max_element(scoreStepTracker.begin(), scoreStepTracker.end())){
			/* cout << "score > *max_element" << score << *max_element(scoreStepTracker.begin(), scoreStepTracker.end()) << endl; */
			return 1;
		} else if (score > vectorAverage(scoreStepTracker) ){
			/* cout << "score > avg" << score << "avg: " << vectorAverage(scoreStepTracker) << endl; */
			return 0;
		} else {
			return -1;
		}
		/* return 0; */
	}
};


class Agent {
	float alpha;
	float randomFactor;
	vector<int> actionHistory; // action, reward
	map<int, float> G;
	public:
	// Constructor
	Agent(float newAlpha, float newRandomFactor)
	{
		alpha = newAlpha;
		randomFactor = newRandomFactor;
		initReward();
	}

	void initReward()
	{
		for(int i = 0; i < ACTIONS.size() ; i++){
			G[i+1] = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
		}
	}

	int chooseAction()
	{
		// maxG = -10e15
		float maxG = -10000000000000000;
		// np.random.random return random floats in the half-open interval [0.0, 1.0).
		float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		int nextMove;

		if (randomNumber < randomFactor)
			nextMove = (rand() % 5) + 1;
		else {
			// If exploiting, gather all possible actions and choose one with the highest G (reward)
			//    for action in ACTIONS:
			//        if self.G[action] >= maxG:
			//            next_move = action
			//            maxG = self.G[action]
			// TODO: hmmm?
			for (const auto& kv : G) {
				/* std::cout << kv.first << " has value " << kv.second << std::endl; */
				if (kv.second >= maxG){
					nextMove = kv.first;
					maxG = kv.second;
				}
			}
		}
		return nextMove;
	}

	void updateActionHistory(int &action, int &reward)
	{
		actionHistory.push_back(action);
		actionHistory.push_back(reward);
	}

	void learn()
	{
		int target = 0;
		int rewAction = actionHistory[0];
		int reward = actionHistory[1];
		G[rewAction] += reward;
		target += reward;
		actionHistory.clear();
		randomFactor -= 0.0001;
        //self.randomFactor -= 10e-5 # Decrease randomFactor after each game session
	}

};


void swapnum(int &i, int &j) {
	int temp = i;
	i = j;
	j = temp;
}

int main() {
	int a = 10;
	int b = 20;
	swapnum(a, b);
	printf("A is %d and B is %d\n", a, b);

	// Before calling rand(), you must first "seed" the random number generator by calling srand()
	srand (static_cast <unsigned> (time(0)));

	Game *game = new Game();
	// Very random:
	/* Agent agent(0.1, 2.85); */
	// standard random factor:
	Agent *agent = new Agent(0.1, 0.15);

	vector<int> actionList;
	vector<int> scoreTracker;
	float finalScore = 0.0;
	float tempScore = 0.0;

	int action;
	int reward;
	/* for(int i = 0; i < 10000; i++){ */
	// 1 million
	/* for(int i = 0; i < 1000000; i++){ */
	for(int i = 0; i < 10000; i++){
		if (game->steps == 0)
			action = agent->chooseAction(); // Choose an action (explore or exploit)

		actionList.push_back(action);
		game->updateGame(action);
		scoreTracker.push_back(game->newScore);

		if (game->steps > 50){
          finalScore += game->score;
          tempScore = game->score;
          scoreStepTracker.push_back(tempScore);
          tempScore = 0.0;
		  // Score after 50 tries
		  /* cout << "Score: " << scoreStepTracker[scoreStepTracker.size()-1] << "Action: " << action << endl; */

		  reward = game->getReward();
		  // Update agent memory with action and reward
		  agent->updateActionHistory(action, reward);
		  // Learn after 50 tries
		  agent->learn();

		  delete game;
          game = new Game();
		}
	}

    // Print and plot results
	cout << "Final score: " << finalScore << endl << endl;
	int firstCount = 0;
	int secondCount = 0;
	int thirdCount = 0;
	int fourthCount = 0;
	int fifthCount = 0;
	for (int i: actionList) {
		if (i == 1)
			firstCount++;
		else if (i == 2)
			secondCount++;
		else if (i == 3)
			thirdCount++;
		else if (i == 4)
			fourthCount++;
		else if (i == 5)
			fifthCount++;
		
	}
	cout << "firstCount: " << firstCount << endl;
	cout << "secondCount: " << secondCount << endl;
	cout << "thirdCount: " << thirdCount << endl;
	cout << "fourthCount: " << fourthCount << endl;
	cout << "fifthCount: " << fifthCount << endl;

	cout << "fourthCount %: " << static_cast< float >(fourthCount)/actionList.size() << endl;

	scoreStepTracker.clear();
	actionList.clear();
	scoreTracker.clear();

	delete game;
	delete agent;
	cout << "End" << endl;

	return 0;
}
