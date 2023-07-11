#ifndef GAMESTARTER_H
#define GAMESTARTER_H
#include <iostream>
#include <string>

using namespace std;

class GameStarter
{
	private:
		char* input;
		void StartGame();
		void RunGameState();

	public:
		GameStarter(char* newInput);
};

#endif
