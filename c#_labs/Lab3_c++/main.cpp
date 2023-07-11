#include <iostream> 
#include "GameStarter.h"

using namespace std;

// g++ main.cpp other.cpp; ./a.exe
int main(int argc, char** argv) { 
	//cout << "This program has " << argc << " arguments:" << endl; 

	if (argc == 1) {
		cout << "No input from argument. Using standard input." << endl;
		// Use original inputs from assignment
		//GameStarter start("NW.CC, NC.CC,NW.NW, NE.CC, NW.SE, CE.CC, CW.CC, SE.CC, CW.NW, CC.CC, CW.SE, CC.NW, CC.SE, CE.NW, SW.CC, CE.SE, SW.NW, SE.SE, SW.SE  ");
		// Random plays 1:
		//GameStarter start("NE.NC,NE.SC,NE.CW,NE.SW,NE.NE,NE.CE,NE.CC,NE.SE,NE.NW,CW.SW,CW.SC,CW.CE,CW.NE,CW.CC,CW.NW,CW.SE,CW.CW,CW.NC,NC.NE,NC.CC,NC.NC,NC.SW,NC.CW,NC.NW,NC.CE,NC.SE,NC.SC,SE.SE,SE.CE,SE.NW,SE.NC,SE.SC,SE.CC,SE.CW,SE.SW,SE.NE,SW.SE,SW.SW,SW.SC,SW.NE,SW.CC,SW.CE,SW.NC,SW.NW,SW.CW,CC.NC,CC.NW,CC.CE,CC.SW,CC.NE,CC.SC,CC.CC,CC.SE,CC.CW,NW.CW,NW.CE,NW.SE,NW.NE,NW.NC,NW.SC,NW.SW,NW.CC,NW.NW,SC.CW,SC.SE,SC.SW,SC.NE,SC.NC,SC.CC,SC.CE,SC.SC,SC.NW,CE.CC,CE.NW,CE.SC,CE.CE,CE.SW,CE.SE,CE.NC,CE.NE,CE.CW");

		// Random plays 2:
		//GameStarter start("NW.SC,NW.NW,NW.NE,NW.SE,NW.SW,NW.NC,NW.CW,NW.CC,NW.CE,CE.SE,CE.NW,CE.NE,CE.CE,CE.CW,CE.SW,CE.SC,CE.CC,CE.NC,NE.NE,NE.CE,NE.SC,NE.NC,NE.CW,NE.NW,NE.SE,NE.SW,NE.CC,CW.SW,CW.NE,CW.NW,CW.SC,CW.CC,CW.CE,CW.SE,CW.NC,CW.CW,SW.NW,SW.CC,SW.CW,SW.NE,SW.SE,SW.SW,SW.SC,SW.NC,SW.CE,SE.NC,SE.SC,SE.NW,SE.CW,SE.SE,SE.CC,SE.NE,SE.SW,SE.CE,SC.NW,SC.CW,SC.CE,SC.NC,SC.SE,SC.SW,SC.SC,SC.NE,SC.CC,CC.SE,CC.NE,CC.NC,CC.NW,CC.CW,CC.SC,CC.CC,CC.SW,CC.CE,NC.NE,NC.SC,NC.SW,NC.CE,NC.NW,NC.SE,NC.NC,NC.CC,NC.CW");

		// Random plays 3:
		GameStarter start("CC.SW,CC.NW,CC.CE,CC.NC,CC.SC,CC.NE,CC.CC,CC.CW,CC.SE,SE.SW,SE.NE,SE.CC,SE.CE,SE.NW,SE.CW,SE.SE,SE.SC,SE.NC,NC.CW,NC.NC,NC.NW,NC.NE,NC.CC,NC.CE,NC.SW,NC.SC,NC.SE,SW.SW,SW.NE,SW.SE,SW.SC,SW.CW,SW.CE,SW.CC,SW.NC,SW.NW,SC.SW,SC.CC,SC.SC,SC.CE,SC.SE,SC.NW,SC.NE,SC.CW,SC.NC,CW.SC,CW.CC,CW.CW,CW.SW,CW.NW,CW.NE,CW.SE,CW.CE,CW.NC,NE.SC,NE.NC,NE.CE,NE.CW,NE.NW,NE.CC,NE.SW,NE.NE,NE.SE,NW.SW,NW.NW,NW.NC,NW.CW,NW.CE,NW.SC,NW.CC,NW.NE,NW.SE,CE.CE,CE.NC,CE.NE,CE.SE,CE.SC,CE.NW,CE.SW,CE.CW,CE.CC");

		// See GameStarter for using random plays...

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
