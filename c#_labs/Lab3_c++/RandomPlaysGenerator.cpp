#include "RandomPlaysGenerator.hpp"

string join(vector<string> const &strings, string delim)
{
	stringstream ss;
	copy(strings.begin(), strings.end(), ostream_iterator<string>(ss, delim.c_str()));
	return ss.str();
}

string getRandomPlays()
{
	vector<string> superBoardNamesVec;
	// Init super board names, like this:
	// boardNames[0] = "NW.NW"
	// boardNames[1] = "NW.NC"
	// boardNames[2] = "NW.NE"

	int boardNamesLength = sizeof boardNames / sizeof boardNames[0];
	for (int i = 0; i < boardNamesLength; i++) {
		for (int j = 0; j < boardNamesLength; j++) {
			superBoardNamesVec.push_back(boardNames[i] + "." + boardNames[j]);
		}
	}

	vector<string> randomVec;
	int r;
	int superBoardNamesCount = superBoardNamesVec.size();
	for (int i = 0; i < superBoardNamesCount; i++)
	{
		r = rand() % superBoardNamesVec.size();
		randomVec.push_back(superBoardNamesVec[r]);
		superBoardNamesVec.erase(superBoardNamesVec.begin() + r);
	}

	//for (string boardPlay : randomVec)
	//	cout << "random: " << boardPlay << endl;

	cout << "RandomPlays:" << endl;
	string joinedRandomPlays = join(randomVec, ",");
	// Remove last comma
	//joinedRandomPlays = joinedRandomPlays.substr(0, joinedRandomPlays.size()-1);
	joinedRandomPlays.pop_back();
	cout << joinedRandomPlays << endl;

	return joinedRandomPlays;
}

string getRandomPlaysSameBoard()
{
	int boardNamesLength = sizeof boardNames / sizeof boardNames[0];
	vector<string> randomVec;
	int r, r2;
	vector<string> randBoardNames = { "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };

	for (int i = 0; i < boardNamesLength; i++) {
		vector<string> tempBoardNames = { "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };
		r = rand() % randBoardNames.size();
		
		for (int j = 0; j < boardNamesLength; j++) {
			r2 = rand() % tempBoardNames.size();
			//cout << "Added random ele: " << randBoardNames[r] << "." << tempBoardNames[r2] << endl;
			randomVec.push_back(randBoardNames[r] + "." + tempBoardNames[r2]);
			tempBoardNames.erase(tempBoardNames.begin() + r2);
		}
		randBoardNames.erase(randBoardNames.begin() + r);
	}

	cout << "RandomPlays:" << endl;
	string joinedRandomPlays = join(randomVec, ",");
	// Remove last comma
	//joinedRandomPlays = joinedRandomPlays.substr(0, joinedRandomPlays.size()-1);
	joinedRandomPlays.pop_back();
	cout << joinedRandomPlays << endl;

	return joinedRandomPlays;
}

void initRndm()
{
	// Seed random number generator
	srand(time(NULL));
}
