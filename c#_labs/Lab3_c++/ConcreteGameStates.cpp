#include "ConcreteGameStates.h"
#include <iostream> 
#include <vector>
#include <sstream>

class BoardObject {
public:
	virtual unordered_set<string> getUpdatedBoardSet(string& play)
	{
	}
	virtual string getName()
	{
	}

	virtual void setName(string newName)
	{
	}
};

class Board : public BoardObject {

public:
	unordered_set<string> getUpdatedBoardSet(string& play)
	{
		boardSet.insert({play});
		return boardSet;
	}

	string getName()
	{
		return boardName;
	}

	void setName(string newName)
	{
		boardName = newName;
	}

private:
	unordered_set<string> boardSet;
	string boardName = "";
};

class SuperBoard : public BoardObject {
	// Map of different BoardObjects that can be used to add new plays to the correct "small board"
	map<string, BoardObject*> playingBoards;

public:
	void addBoard(string &name, BoardObject* a)
	{
		playingBoards.insert({name, a});
	}

	void deleteBoard(BoardObject a)
	{
		cout << "something is deleted from the superboard";
	}

	// Add value to the correct board and return it
	unordered_set<string> getUpdatedBoardSet(string& play)
	{
		// If depth is 1, then just use 1 board
		if ((play).find('.') == string::npos)
			return playingBoards["nw"]->getUpdatedBoardSet(play);

		string boardPos = play.substr(0, play.find('.'));
		string boardPlay = play.substr(3, play.length());

		//cout << "Calling boardPos: " << boardPos << " with: " << boardPlay << endl;
		// Add value to the correct board
		return playingBoards[boardPos]->getUpdatedBoardSet(boardPlay);
	}
};

/*
   GameInvalid state
*/

void GameInvalid::run(Game* game, char* newInput)
{
	input = newInput;
	// GameInvalid -> GameLoop
	//game->setState(GameLoop::getInstance());
	cout << "Running game invalid" << endl;
}

GameState& GameInvalid::getInstance()
{
	static GameInvalid singleton;
	return singleton;
}

/*
   GameLoop state
*/

void GameLoop::run(Game* game, char* newInput)
{
	this->game = game;
	input = newInput;
	cout << "Input in game loop: " << input << endl << endl;
	initValues();

	string sInput(input);
	string::iterator end_pos = remove(sInput.begin(), sInput.end(), ' ');
	sInput.erase(end_pos, sInput.end());
	//cout << "Removed spaces: " << sInput << endl;
	toLowerString(&sInput);
	//cout << "To lower: " << sInput << endl;

	stringstream inputStream(sInput);
	vector<string> inputSplit;

	while(inputStream.good())
	{
		string substr;
		getline(inputStream, substr, ',' );
		inputSplit.push_back(substr);
	}

	// Only add plays that haven't been done before
	for(string play : inputSplit) {
		//cout << "play: " << play << endl;
		//if (!hasBeenPlayed(play)) totalPlays.insert({play});
		if (!hasBeenPlayed(play)) totalPlaysVec.push_back(play);
	}

	// Loop vector
	//for(string play : inputSplit)
	//	cout << "play: " << play << endl;

	loopGame();
	cout << "End of game loop" << endl;
	inputSplit.clear();
	totalPlays.clear();
	winningBoards.clear();
	finalValidPlays.clear();
	totalPlaysVec.clear();
	//delete input;
	//delete newInput;
	//delete game;
	//delete currPlayer;
	//delete gameOverStatus;
}

void GameLoop::loopGame()
{
	// TODO: Fix this init somewhere else? Put board and superBoard into headerfile etc...
	SuperBoard boardComposite;
	BoardObject** boards = new BoardObject*[9];
	string boardName;
	for(int i = 0; i < 9; i++)
	{
		boardName = boardNames[i];
		boards[i] = new Board();
		boards[i]->setName(boardName);
		boardComposite.addBoard(boardName, boards[i]);
	}

	totalPlaysCount = totalPlaysVec.size();
	// Keep track of valid plays
	int validPlays = 0;

	auto playsItr = totalPlaysVec.begin();
	hasDepthOne = ((*playsItr).find('.') == string::npos);
	maxPlays = hasDepthOne ? 7 : 80;
	string boardPos;
	cout << "totalPlaysCount: " << totalPlaysCount << endl;
	cout << "First element in totalPlays: " << *playsItr << endl;
	cout << "hasDepthOne: " << hasDepthOne << endl;

	for(string playValue : totalPlaysVec){
		if (superBoardWon) break;
		boardPos = playValue.substr(0, playValue.find('.'));
		//cout << "playValue: " << playValue << endl;
		//cout << "boardPos: " << boardPos << endl;

		currPlayer = addToPlayerOne ? &playerOne : &playerTwo;
		//cout << "currPlayer: " << currPlayer->getPlayerName() << endl;
		// Check if new play can be played on small board (the small board shouldn't have a winner already)
		if (canBeAdded(boardPos))
		{
			// Toggle addToPlayerOne so that next value is added to other player
			addToPlayerOne = !addToPlayerOne;
			validPlays++;
			finalValidPlays.push_back(playValue);

			/* handleNewPlay(playValue); */
			currPlayer->addToQueue(playValue);
            // If the player wins a small board run, check if that player has won the super board
			playValue += currPlayer->getPlayerName();
			if (hasWon(boardComposite.getUpdatedBoardSet(playValue), false)) {
				currPlayer->incrBoardsWon();
				boardWinsMap[boardPos]  = currPlayer->getPlayerName();
				if (hasDepthOne || hasWonSuperBoard(currPlayer->getPlayerName())) {
					superBoardWon = true;
					currPlayer->incrSuperBoardsWon();
					currPlayer->printEndResults();
					cout << currPlayer->getPlayerName() << " (" << (currPlayer->getPlayerName() == "p1" ? "X" : "O") << ") won SuperBoard with boards:" << endl;
					for (auto& it : boardWinsMap) {
						if (it.second == currPlayer->getPlayerName())
							cout << it.first << " ";
					}
					cout << endl;
					visualizePlays();

					for (int i = 0; i < 9; i++)
						delete boards[i];
					delete[] boards;
					// Change state to game over state
					game->setState(GameOver::getInstance());
					game->run(gameOverStatus);
				}
			}
		}
	}

	// If this part is reached, the game in unfinished
	if (!superBoardWon)
	{
		game->setState(GameOver::getInstance());
		gameOverStatus = "unfinished";
		game->run(gameOverStatus);
		//gameStarter.ChangeState("unfinished", new GameOverState());
		//instanceCreater.GetResultVisualizer().VisualizePlays(finalValidPlays, HasDepthOne);
	}
}

void GameLoop::visualizePlays()
{
	int matrixSize = 9;
	cout << endl << "Visualization:" << endl;

	string boardMatrix[matrixSize][matrixSize] = {
	{"nw.nw", "nw.nc", "nw.ne",		"nc.nw", "nc.nc", "nc.ne",		"ne.nw", "ne.nc", "ne.ne"},
	{"nw.cw", "nw.cc", "nw.ce", 	"nc.cw", "nc.cc", "nc.ce", 		"ne.cw", "ne.cc", "ne.ce"},
	{"nw.sw", "nw.sc", "nw.se", 	"nc.sw", "nc.sc", "nc.se", 		"ne.sw", "ne.sc", "ne.se"},

	{"cw.nw", "cw.nc", "cw.ne",		"cc.nw", "cc.nc", "cc.ne",		"ce.nw", "ce.nc", "ce.ne"},
	{"cw.cw", "cw.cc", "cw.ce",		"cc.cw", "cc.cc", "cc.ce", 		"ce.cw", "ce.cc", "ce.ce"},
	{"cw.sw", "cw.sc", "cw.se",		"cc.sw", "cc.sc", "cc.se", 		"ce.sw", "ce.sc", "ce.se"},

	{"sw.nw", "sw.nc", "sw.ne",		"sc.nw", "sc.nc", "sc.ne", 		"se.nw", "se.nc", "se.ne"},
	{"sw.cw", "sw.cc", "sw.ce",		"sc.cw", "sc.cc", "sc.ce", 		"se.cw", "se.cc", "se.ce"},
	{"sw.sw", "sw.sc", "sw.se",		"sc.sw", "sc.sc", "sc.se", 		"se.sw", "se.sc", "se.se"}
	};

	// Create map of (row, col) and "nw.nw"
    // map<int,int*> colors;
    // int red[] = {3,7,9};
    // colors[52] = red;
    // cout << colors[52][1];  //prints 7
	map<string, tuple<int, int>> visBoardMap;

	for (int row = 0; row < matrixSize; row++) {
		for (int col = 0; col < matrixSize; col++)
		{
			visBoardMap.insert({boardMatrix[row][col], make_tuple(row, col)});
		}
	}

	// Loop map values
	//for (const auto& entry : visBoardMap)
	//	cout << entry.first << ": " << get<0>(entry.second) << "," << get<1>(entry.second) << endl;

	int matrix[matrixSize][matrixSize] = {};

	// Loop vector
	int x, y;
	int z = 0;
	for(string play : finalValidPlays) {
		//cout << "play: " << play << endl;
		x = get<0>(visBoardMap[play]);
		y = get<1>(visBoardMap[play]);
		matrix[x][y] = z % 2 == 0 ? 1 : 2;
		z++;
	}

	for (int row = 0; row < matrixSize; row++) {
		for (int col = 0; col < matrixSize; col++)
		{
			//cout << matrix[row][col] << (col + 1 < 9 ? ", " : "\n");
			int val = matrix[row][col];
			if (val == 0)
				cout << "|	";
			else if (val == 1)
				cout << "X	";
			else if (val == 2)
				cout << "O	";
			if (col == 8)
				cout << "\n";
			else if (col == 2 || col == 5)
				cout << "\t";
		}
		if (row == 2 || row == 5)
			cout << "\n";
	}
}

bool GameLoop::hasWonSuperBoard(string playerName)
{
	unordered_set<string> playerWins;
	for (auto& it : boardWinsMap) {
		// If mapped value is playerName,
		if (it.second == playerName) {
			//playerWins.insert(it.first);
			playerWins.insert({it.first + playerName});
		}
	}
	return hasWon(playerWins, true);
}

// TODO: Move boardComposite into own class and handle new play in this func
void GameLoop::handleNewPlay(string& play)
{
}

bool GameLoop::hasWon(unordered_set<string> board, bool isSuper)
{
	string playerName = currPlayer->getPlayerName();

	// Loop unordered_set
	//if (isSuper) {
	//	for (auto P: board)
	//		cout << "HasWon check - board: " << P << endl;
	//}

	// Check top horizontal row
	if (board.find(("nw" + playerName)) != board.end() && board.find(("nc" + playerName)) != board.end() && board.find(("ne" + playerName)) != board.end()) {
		if (isSuper) winningBoards.push_back("nw,nc,ne");
		return true;
	}
	// Check south horizontal row
	else if (board.find(("sw" + playerName)) != board.end() && board.find(("sc" + playerName)) != board.end() && board.find(("se" + playerName)) != board.end()) {
		if (isSuper) winningBoards.push_back("sw,sc,se");
		return true;
	}
	// Check center horizontal row
	else if (board.find(("cw" + playerName)) != board.end() && board.find(("cc" + playerName)) != board.end() && board.find(("ce" + playerName)) != board.end()) {
		if (isSuper) winningBoards.push_back("cw,cc,ce");
		return true;
	}
	// Check first vertical column
	else if (board.find(("nw" + playerName)) != board.end() && board.find(("cw" + playerName)) != board.end() && board.find(("sw" + playerName)) != board.end()) {
		if (isSuper) winningBoards.push_back("nw,cw,sw");
		return true;
	}
	// Check second vertical column
	else if (board.find(("cc" + playerName)) != board.end() && board.find(("nc" + playerName)) != board.end() && board.find(("sc" + playerName)) != board.end()) {
		if (isSuper) winningBoards.push_back("cc,nc,sc");
		return true;
	}
	// Check third vertical column
	else if (board.find(("ne" + playerName)) != board.end() && board.find(("ce" + playerName)) != board.end() && board.find(("se" + playerName)) != board.end()) {
		if (isSuper) winningBoards.push_back("ne,ce,se");
		return true;
	}
	// Check diagonally
	else if (board.find(("nw" + playerName)) != board.end() && board.find(("cc" + playerName)) != board.end() && board.find(("se" + playerName)) != board.end()) {
		if (isSuper) winningBoards.push_back("nw,cc,se");
		return true;
	}
	// Check diagonally
	else if (board.find(("sw" + playerName)) != board.end() && board.find(("cc" + playerName)) != board.end() && board.find(("ne" + playerName)) != board.end()) {
		if (isSuper) winningBoards.push_back("sw,cc,ne");
		return true;
	}
	else
		return false;
}

// Return bool of whether the board has a winner or not (play can only 
// be added to small board if it doesn't already have a winner)
bool GameLoop::canBeAdded(string& pos)
{
	return (boardWinsMap[pos] == "");
}

bool GameLoop::hasBeenPlayed(string& playValue)
{
	if (find(totalPlaysVec.begin(), totalPlaysVec.end(), playValue) != totalPlaysVec.end())
		cout << "hasBeenPlayed" << endl;
	return (find(totalPlaysVec.begin(), totalPlaysVec.end(), playValue) != totalPlaysVec.end());
}

void GameLoop::toLowerString(string* sInput)
{
	transform(sInput->begin(), sInput->end(), sInput->begin(), [](unsigned char c){ return std::tolower(c); });
}

void GameLoop::initValues()
{
	// Player names
	playerOne = Player();
	playerTwo = Player();
	this->playerOne.setPlayerName("p1");
	this->playerTwo.setPlayerName("p2");
	addToPlayerOne = true;
	superBoardWon = false;
	// Feed boardWinsMap with all board names (nw, nc etc...)
	for (string boardString : boardNames)
	{
		boardWinsMap.insert({boardString, ""});
	}
}

GameState& GameLoop::getInstance()
{
	static GameLoop singleton;
	return singleton;
}

/*
   GameOver state
*/

void GameOver::run(Game* game, char* input)
{
	// GameOver -> GameLoop
	//game->setState(GameLoop::getInstance());
	cout << "Running game over: " << input << endl;
}

GameState& GameOver::getInstance()
{
	static GameOver singleton;
	return singleton;
}
