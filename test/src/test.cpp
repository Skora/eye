//============================================================================
// Name        : test.cpp
// Author      : Skora
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "program_options.hpp"
#include "cJSON.h"
#include <cstring>
#include <stdlib.h>



using namespace std;

#define SERIAL_ID 123456

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

static inline char* createRegJson(int serialID)
{
	cJSON *root;
	cJSON *pl;
	char* msg;
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "top", cJSON_CreateString("register"));
	cJSON_AddItemToObject(root, "pl", pl = cJSON_CreateObject());
	cJSON_AddStringToObject(pl, "type", "eye_module");
	cJSON_AddNumberToObject(pl, "sub_id", serialID);
	cJSON_AddNumberToObject(pl, "pub_id", serialID);
	cJSON_AddNumberToObject(root, "act", 1);
	msg = cJSON_Print(root);
	cJSON_Delete(root);
	return msg;
}

static inline char* addJsonLength(char *jsonMsg, int length)
{
	#define LEN_BYTES 4U
	char* newBuf;

    newBuf = (char*)malloc(LEN_BYTES + length);

  //  length = htonl((unsigned long)length); // make it work
    memcpy(newBuf, (char*)&length, LEN_BYTES);
    memcpy(newBuf + LEN_BYTES, jsonMsg, length);

    return newBuf;
}


int main(int argc, char* argv[]) {



	progOptions.addOption("--h", &help);
	progOptions.addOption("--help", &help);
	progOptions.addOption("--debug", &debug);
	progOptions.executeOptions(argc, argv);


	char* regMsg = createRegJson(SERIAL_ID);
	char* msg =  addJsonLength(regMsg, strlen(regMsg));

	for (unsigned int i = 0; i <= 4; i++) 	//this is just a work around to visualize output
	{										// cout sends strings not bytes so we send 4 length bytes first and then the rest
		cout << (msg+(i*sizeof(char))) << endl;
	}
	//Absolutely necessary
	free(regMsg);
	free(msg);




	return 0;
}
