#pragma once
#include <string>
#include <queue>

using namespace std;

class Player
{
public:
	Player();
	void printEndResults();
	void setPlayerName(string name);
	string getPlayerName();
	void addToQueue(string newPlay);
	void incrBoardsWon();
	void incrSuperBoardsWon();
	int getBoardsWon();
	int getSuperBoardsWon();

private:
	string playerName;
	// Queue that will track all player moves
	queue<string> playerQueue;
	int boardsWon = 0;
	int superBoardsWon = 0;
};
