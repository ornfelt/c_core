#include<iostream> 
#include <unordered_set>

using namespace std;


void startGame(char* input)
{
	cout << "Received input: " << input << endl;

	unordered_set<int> X { 2020, 2019, 2018 };
	for (auto Y: X)
		cout << Y << endl;

}

// g++ main.cpp ./a.exe
int main(int argc, char** argv) {
	cout << "This program has " << argc << " arguments:" << endl; 

	if (argc == 1) {
		cout << "No input from argument. Using standard input." << endl;
		// Use original inputs from assignment
		startGame("NW.CC, NC.CC,NW.NW, NE.CC, NW.SE, CE.CC, CW.CC, SE.CC, CW.NW, CC.CC, CW.SE, CC.NW, CC.SE, CE.NW, SW.CC, CE.SE, SW.NW, SE.SE, SW.SE");

		// Examples of invalid inputs 
		// Depth 1
		//startGame("NW,NC,CW,CC,SW");
		//startGame("NW.CC, NC.CC,NW.NW, NE.CC, NW.SE, CE.CG, CW.CC");
		//startGame("adasdasda");
		//startGame("NW.CC, NC.CC,NW.NW, NE.CC, NW.SE, CE.C, CW.CC, SE.CC, CW.NW, CC.CC, CW.SE, CC.NW, CC.SE, CE.NW, SW.CC, CE.SE, SW.NW, SE.SE, SW.SE");
		//startGame("NW.CC, NC.CC,NW.NWE, NE.CC, NW.SE, CE.CCG, CW.CC, SE.CC, CW.NW, CC.CC, CW.SE, CC.NW, CC.SE, CE.NW, SW.CC, CE.SE, SW.NW, SE.SE, SW.SE");

	} else {
		// else means inputs are given
		for (int i = 0; i < argc; ++i) { 
			cout << "input: " << argv[i] << endl; 
		} 
		startGame(argv[1]);
	}

    return 0;
}
