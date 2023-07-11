#pragma once
#include "Game.h"

// Forward declaration to resolve circular dependency/include
class Game;

class GameState
{
public:
	virtual void enter(Game* game) = 0;
	virtual void run(Game* game, char* newInput) = 0;
	virtual void exit(Game* game) = 0;
	virtual ~GameState() {}
};
