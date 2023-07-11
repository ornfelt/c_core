#include "GameStarter.h"
#include "Game.h"
#include "ConcreteGameStates.h"
#include "RandomPlaysGenerator.hpp"

//class GameState;
Game game;

GameStarter::GameStarter(char* newInput)
{
	input = newInput;
	StartGame();
	//delete input;
	//delete newInput;
}

// Start the game
// We first validate the data and then choose the appropriate state
void GameStarter::StartGame()
{
	//cout << "Received input: " << input << endl;

	// Validate input and set appropriate state
	//ValidateInput validateInput = new ValidateInput();
	bool inputIsValid = true;
	if (inputIsValid)
		game.setState(GameLoop::getInstance());
	else
		game.setState(GameInvalid::getInstance());

	initRndm();
	//string randomPlay = getRandomPlays();
	string randomPlay = getRandomPlaysSameBoard();

	// Both of these work for converting string to char*
	input = const_cast<char*>(randomPlay.c_str());
	//input = &*randomPlay.begin();

	RunGameState();
}

// Start handling the game state
void GameStarter::RunGameState()
{
	//game.setState(GameOver::getInstance());
	game.run(input);
}
