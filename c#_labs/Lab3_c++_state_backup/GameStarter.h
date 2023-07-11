#ifndef GAMESTARTER_H
#define GAMESTARTER_H
#include <string>

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
