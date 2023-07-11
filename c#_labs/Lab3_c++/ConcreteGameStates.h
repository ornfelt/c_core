#pragma once
#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <map>

using namespace std;

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
	const string boardNames[9] = { "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };

private:
	GameLoop() {}
	GameLoop(const GameLoop& other);
	GameLoop& operator=(const GameLoop& other);
	Game* game;
	Player playerOne;
	Player playerTwo;
	Player* currPlayer;

	char* input;
	char* gameOverStatus = "over";
	string playerOneName, playerTwoName;
	string boardPos;
	int totalPlaysCount = 0;
	int maxPlays;
	// Bool that determines what player the new play should be added to
	bool addToPlayerOne;
	bool superBoardWon;
	bool hasDepthOne;
	bool hasBeenPlayed(string& playValue);
	bool canBeAdded(string& pos);
	bool hasWon(unordered_set<string> board, bool isSuper);
	bool hasWonSuperBoard(string playerName);

	void toLowerString(string* input);
	void initValues();
	void loopGame();
	void handleNewPlay(string& playValue);
	void visualizePlays();
	unordered_set<string> totalPlays;
	// Vector containing the boards that led to superBoardWon
	vector<string> winningBoards;
	// New vec for visualizing final valid plays
	vector<string> finalValidPlays;
	vector<string> totalPlaysVec;
	// Map containing boards won
	map<string, string> boardWinsMap;
};

class GameOver : public GameState
{
public:
	void enter(Game* game) {}
	void run(Game* game, char* input);
	void exit(Game* game) {}
	static GameState& getInstance();

private:
	GameOver() {}
	GameOver(const GameOver& other);
	GameOver& operator=(const GameOver& other);
};
