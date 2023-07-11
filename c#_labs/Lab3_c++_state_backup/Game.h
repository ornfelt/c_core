#pragma once
#include "GameState.h"

// Forward declaration to resolve circular dependency/include
class GameState;

class Game
{
public:
	Game();
	inline GameState* getCurrentState() const { return currentState; }
	void run(char* newInput);
	// This is where the magic happens
	void setState(GameState& newState);

private:
	GameState* currentState;
};
