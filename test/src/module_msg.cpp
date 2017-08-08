/*
 * module_msg.cpp
 *
 *  Created on: 08.08.2017
 *      Author: skorzpaw
 */
#include "module_msg.hpp"
#include <cstring>
#include <sstream>
#include "cJSON.h"

namespace patch
{
	template < typename T > std::string to_string( const T& n )
	{
		std::ostringstream stm ;
		stm << n ;
		return stm.str() ;
	}
}


char* MoudleMsgs::createRegJson(void)
{
	cJSON *root;
	cJSON *pl;
	char* msg;
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "top", cJSON_CreateString("register"));
	cJSON_AddItemToObject(root, "pl", pl = cJSON_CreateObject());
	cJSON_AddStringToObject(pl, "type", "eye_module");
	cJSON_AddNumberToObject(pl, "sub_id", SERIAL_ID);
	cJSON_AddNumberToObject(pl, "pub_id", SERIAL_ID);
	cJSON_AddNumberToObject(root, "act", 1);
	msg = cJSON_Print(root);
	msg = MoudleMsgs::addJsonLength(msg, strlen(msg));
	cJSON_Delete(root);
	return msg;
}

char* MoudleMsgs::createEventJson(const char* event, int arg1, int arg2, int arg3)
{
	cJSON *root;
	cJSON *pl;
	char* msg;

	string serial = patch::to_string(SERIAL_ID);
	serial += "_out";
	const char * topic = serial.c_str();

	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "top", cJSON_CreateString(topic));
	cJSON_AddItemToObject(root, "pl", pl = cJSON_CreateObject());
	cJSON_AddStringToObject(pl, "ev", event);
	cJSON_AddNumberToObject(pl, "arg1", arg1);
	cJSON_AddNumberToObject(pl, "arg2", arg2);
	cJSON_AddNumberToObject(pl, "arg3", arg3);
	cJSON_AddNumberToObject(root, "act", 1);
	msg = cJSON_Print(root);
	msg = MoudleMsgs::addJsonLength(msg, strlen(msg));
	cJSON_Delete(root);
	return msg;
}

char* MoudleMsgs::createEventJson(const char* event, int arg1, int arg2)
{
	cJSON *root;
	cJSON *pl;
	char* msg;

	string serial = patch::to_string(SERIAL_ID);
	serial += "_out";
	const char * topic = serial.c_str();

	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "top", cJSON_CreateString(topic));
	cJSON_AddItemToObject(root, "pl", pl = cJSON_CreateObject());
	cJSON_AddStringToObject(pl, "ev", event);
	cJSON_AddNumberToObject(pl, "arg1", arg1);
	cJSON_AddNumberToObject(pl, "arg2", arg2);
	cJSON_AddNumberToObject(root, "act", 1);
	msg = cJSON_Print(root);
	msg = MoudleMsgs::addJsonLength(msg, strlen(msg));
	cJSON_Delete(root);
	return msg;
}

char* MoudleMsgs::createEventJson(const char* event, int arg1)
{
	cJSON *root;
	cJSON *pl;
	char* msg;

	string serial = patch::to_string(SERIAL_ID);
	serial += "_out";
	const char * topic = serial.c_str();

	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "top", cJSON_CreateString(topic));
	cJSON_AddItemToObject(root, "pl", pl = cJSON_CreateObject());
	cJSON_AddStringToObject(pl, "ev", event);
	cJSON_AddNumberToObject(pl, "arg1", arg1);
	cJSON_AddNumberToObject(root, "act", 1);
	msg = cJSON_Print(root);
	msg = MoudleMsgs::addJsonLength(msg, strlen(msg));
	cJSON_Delete(root);
	return msg;
}

char* MoudleMsgs::createCmdJson(const char* cmd, int arg1)
{
	cJSON *root;
	cJSON *pl;
	char* msg;

	string serial = patch::to_string(SERIAL_ID);
	serial += "_in";
	const char * topic = serial.c_str();

	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "top", cJSON_CreateString(topic));
	cJSON_AddItemToObject(root, "pl", pl = cJSON_CreateObject());
	cJSON_AddStringToObject(pl, "cmd", cmd);
	cJSON_AddNumberToObject(pl, "arg1", arg1);
	cJSON_AddNumberToObject(root, "act", 1);
	msg = cJSON_Print(root);
	//msg = MoudleMsgs::addJsonLength(msg, strlen(msg));
	cJSON_Delete(root);
	return msg;
}

char* MoudleMsgs::addJsonLength(char *jsonMsg, int length)
{
	#define LEN_BYTES 4U
	char* newBuf;

    newBuf = (char*)malloc(LEN_BYTES + length);

  //  length = htonl((unsigned long)length); // make it work
    memcpy(newBuf, (char*)&length, LEN_BYTES);
    memcpy(newBuf + LEN_BYTES, jsonMsg, length);
    free(jsonMsg);
    return newBuf;
}

