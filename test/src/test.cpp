//============================================================================
// Name        : test.cpp
// Author      : Skora
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "program_options.hpp"
#include "cJSON.h"
#include <iostream>

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

	cJSON *root;
	cJSON *fmt;
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
	cJSON_AddStringToObject(fmt, "type", "rect");
	cJSON_AddNumberToObject(fmt, "width", 1920);
	cJSON_AddNumberToObject(fmt, "height", 1080);
	cJSON_AddFalseToObject (fmt, "interlace");
	cJSON_AddNumberToObject(fmt, "frame rate", 24);
	char *rendered = cJSON_Print(root);
	cJSON_Delete(root);
	cout << rendered << endl;



	return 0;
}
