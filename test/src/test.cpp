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
#include "cmd_manager.h"
#include "stdio.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


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

void ModuleCMD_example(int speed, int arg2, int arg3, char* pcSubcmd)
{
	cout << "we have run example module cmd" << endl;
}


TEST_CASE("Json msg generation")
{
	char* exp_result = (char*)"m\0\0\0{\"top\":\"123456_out\",\"pl\":{\"ev\":\"faceCenter\",\"arg1\":17,\"arg2\":13},\"act\":1}";
	char* regMsg = NULL;
	regMsg = msg.createRegJson();
	CHECK( regMsg == exp_result);

}


//int main(int argc, char* argv[]) {
//	///program options
//	progOptions.addOption("--h", &help);
//	progOptions.addOption("--help", &help);
//	progOptions.addOption("--debug", &debug);
//	progOptions.executeOptions(argc, argv);
//
//	printf("%s \n", exp_result);
//
//	//registration msg
//	char* regMsg = NULL;
//	regMsg = msg.createRegJson();
//	for (unsigned int i = 0; i <= 4; i++) 	//this is just a work around to visualize output
//	{										// cout sends strings not bytes so we send 4 length bytes first and then the rest
//		cout << (regMsg+(i*sizeof(char))) << endl;
//	}
//	free(regMsg);
//
//	//event generation
//	int center[] = {17 , 13};
//	char* event = NULL;
//	event = msg.createEventJson( "faceCenter",center[0], center[1]);
//	for (unsigned int i = 0; i <= 4; i++) 	//this is just a work around to visualize output
//	{										// cout sends strings not bytes so we send 4 length bytes first and then the rest
//		cout << (event+(i*sizeof(char))) << endl;
//	}
//	free(event);
//
//
//	//Cmd manager tests
//	char* exCmd = msg.createCmdJson("Example", 123);
//	CmdManager_routine(exCmd);
//	free(exCmd);
//
//	return 0;
//}

