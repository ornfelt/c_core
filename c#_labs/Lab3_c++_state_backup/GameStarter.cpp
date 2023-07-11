#include <iostream>
#include "GameStarter.h"
#include <string>
#include "Game.h"
#include "ConcreteGameStates.h"

using namespace std;

//class GameState;
Game game;

GameStarter::GameStarter(char* newInput)
{
	input = newInput;
	StartGame();
}

// Start the game
// We first validate the data and then choose the appropriate state
void GameStarter::StartGame()
{
	cout << "Received input: " << input << endl;
	// Validate input and set appropriate state
	//ValidateInput validateInput = new ValidateInput();
	bool inputIsValid = true;
	if (inputIsValid)
		game.setState(GameLoop::getInstance());
	else
		game.setState(GameInvalid::getInstance());

	RunGameState();
}

// Start handling the game state
void GameStarter::RunGameState()
{
	//game.setState(GameOver::getInstance());
	game.run(input);
}
