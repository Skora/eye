//============================================================================
// Name        : test.cpp
// Author      : Skora
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "program_options.hpp"

using namespace std;



ProgramOptions progOptions;

void help (void)
{
	progOptions.listOptions();
}

int main(int argc, char* argv[]) {

	progOptions.addOption("--h", &help);
	progOptions.addOption("--help", &help);
	progOptions.executeOptions(argc, argv);



	return 0;
}
