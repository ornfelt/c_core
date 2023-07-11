#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <time.h>

using namespace std;

const string boardNames[9] = { "nw", "nc", "ne", "cw", "cc", "ce", "sw", "sc", "se" };

string getRandomPlays();
string getRandomPlaysSameBoard();
void initRndm();
