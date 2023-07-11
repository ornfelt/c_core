#pragma once
#include "GameState.h"
#include "Game.h"

class GameInvalid : public GameState
{
public:
	void enter(Game* game) {}
	void run(Game* game, char* newInput);
	void exit(Game* game) {}
	static GameState& getInstance();

private:
	GameInvalid() {}
	GameInvalid(const GameInvalid& other);
	GameInvalid& operator=(const GameInvalid& other);
	char* input;
};

class GameLoop : public GameState
{
public:
	void enter(Game* game) {}
	void run(Game* game, char* newInput);
	void exit(Game* game) {}
	static GameState& getInstance();

private:
	GameLoop() {}
	GameLoop(const GameLoop& other);
	GameLoop& operator=(const GameLoop& other);
	char* input;
};

class GameOver : public GameState
{
public:
	void enter(Game* game) {}
	void run(Game* game, char* newInput);
	void exit(Game* game) {}
	static GameState& getInstance();

private:
	GameOver() {}
	GameOver(const GameOver& other);
	GameOver& operator=(const GameOver& other);
	char* input;
};
