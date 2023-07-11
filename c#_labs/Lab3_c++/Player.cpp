#include<iostream> 
#include "Player.h"

Player::Player()
{
}

void Player::printEndResults()
{
	cout << endl << "End results:" << endl;
	cout << "Winning plays:" << endl;
	while (!playerQueue.empty())
	{
		cout << playerQueue.front() << " ";
		playerQueue.pop();
	}
	cout << endl;
	cout << "Final score: " << getSuperBoardsWon() << "," << getBoardsWon() << endl;
}

void Player::setPlayerName(string name)
{
	playerName = name;
	cout << "New player name: " << playerName << endl;
}

string Player::getPlayerName()
{
	return playerName;
}

void Player::addToQueue(string newPlay)
{
	playerQueue.push(newPlay);
}

int Player::getBoardsWon()
{
	return boardsWon;
}

int Player::getSuperBoardsWon()
{
	return superBoardsWon;
}

void Player::incrBoardsWon()
{
	boardsWon++;
}

void Player::incrSuperBoardsWon()
{
	superBoardsWon++;
}
