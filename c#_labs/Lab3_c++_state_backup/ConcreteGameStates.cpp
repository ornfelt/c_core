#include "ConcreteGameStates.h"
#include <iostream> 

using namespace std;

void GameInvalid::run(Game* game, char* newInput)
{
	input = newInput;
	// GameInvalid -> GameLoop
	//game->setState(GameLoop::getInstance());
	cout << "Running game invalid" << endl;
}

GameState& GameInvalid::getInstance()
{
	static GameInvalid singleton;
	return singleton;
}

void GameLoop::run(Game* game, char* newInput)
{
	input = newInput;
	cout << "Input in game loop: " << input << endl;

}

GameState& GameLoop::getInstance()
{
	static GameLoop singleton;
	return singleton;
}

void GameOver::run(Game* game, char* newInput)
{
	input = newInput;
	// GameOver -> GameLoop
	//game->setState(GameLoop::getInstance());
	cout << "Running game over" << endl;
}

GameState& GameOver::getInstance()
{
	static GameOver singleton;
	return singleton;
}
