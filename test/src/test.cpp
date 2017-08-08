//============================================================================
// Name        : test.cpp
// Author      : Skora
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "program_options.hpp"
#include "module_msg.hpp"
#include <iostream>



using namespace std;



ProgramOptions progOptions;
bool debug_flag = false;

void help (void)
{
	progOptions.listOptions();
}

void debug (void)
{
	debug_flag = true;
}

MoudleMsgs msg;

int main(int argc, char* argv[]) {

	progOptions.addOption("--h", &help);
	progOptions.addOption("--help", &help);
	progOptions.addOption("--debug", &debug);
	while (1)
	{
		progOptions.executeOptions(argc, argv);

		char* regMsg = NULL;
		regMsg = msg.createRegJson();
		for (unsigned int i = 0; i <= 4; i++) 	//this is just a work around to visualize output
		{										// cout sends strings not bytes so we send 4 length bytes first and then the rest
			cout << (regMsg+(i*sizeof(char))) << endl;
		}
		free(regMsg);


		int center[] = {17 , 13};
		char* event = NULL;
		event = msg.createEventJson( "faceCenter",center[0], center[1]);
		for (unsigned int i = 0; i <= 4; i++) 	//this is just a work around to visualize output
		{										// cout sends strings not bytes so we send 4 length bytes first and then the rest
			cout << (event+(i*sizeof(char))) << endl;
		}
		free(event);
	}


	return 0;
}
