#include<iostream> 
#include "GameStarter.h"

using namespace std;

// g++ main.cpp other.cpp; ./a.exe
int main(int argc, char** argv) { 
	cout << "This program has " << argc << " arguments:" << endl; 

	if (argc == 1) {
		cout << "No input from argument. Using standard input." << endl;
		// Use original inputs from assignment
		GameStarter start("NW.CC, NC.CC,NW.NW, NE.CC, NW.SE, CE.CC, CW.CC, SE.CC, CW.NW, CC.CC, CW.SE, CC.NW, CC.SE, CE.NW, SW.CC, CE.SE, SW.NW, SE.SE, SW.SE");

		// Examples of invalid inputs 
		// Depth 1
		//GameStarter start("NW,NC,CW,CC,SW");
		//GameStarter start("NW.CC, NC.CC,NW.NW, NE.CC, NW.SE, CE.CG, CW.CC");
		//GameStarter start("adasdasda");
		//GameStarter start("NW.CC, NC.CC,NW.NW, NE.CC, NW.SE, CE.C, CW.CC, SE.CC, CW.NW, CC.CC, CW.SE, CC.NW, CC.SE, CE.NW, SW.CC, CE.SE, SW.NW, SE.SE, SW.SE");
		//GameStarter start("NW.CC, NC.CC,NW.NWE, NE.CC, NW.SE, CE.CCG, CW.CC, SE.CC, CW.NW, CC.CC, CW.SE, CC.NW, CC.SE, CE.NW, SW.CC, CE.SE, SW.NW, SE.SE, SW.SE");

	} else {
		// else means inputs are given
		for (int i = 0; i < argc; ++i) { 
			cout << "input: " << argv[i] << endl; 
		} 
		GameStarter start(argv[1]);
	}

    return 0;
}
