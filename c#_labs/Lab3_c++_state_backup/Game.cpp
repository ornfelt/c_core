#include<iostream> 
#include "Game.h"
#include "ConcreteGameStates.h"

using namespace std;

Game::Game()
{
	// All Games are initially invalid
	currentState = &GameInvalid::getInstance();
}

void Game::setState(GameState& newState)
{
	currentState->exit(this);  // do stuff before we change state
	currentState = &newState;  // actually change states now
	currentState->enter(this); // do stuff after we change state
	cout << "Changed Game state" << endl;
}

void Game::run(char* input)
{
	// Delegate the task of determining the next state to the current state
	currentState->run(this, input);
}
