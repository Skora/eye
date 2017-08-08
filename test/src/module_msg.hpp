/*
 * module_msg.hpp
 *
 *  Created on: 08.08.2017
 *      Author: skorzpaw
 */

#ifndef MODULE_MSG_HPP_
#define MODULE_MSG_HPP_

#include <stdlib.h>

#define SERIAL_ID 123456

using namespace std;


class MoudleMsgs
{

private:
	char* addJsonLength(char *jsonMsg, int length);
public:
	char* createRegJson(void);
	char* createEventJson(const char* event, int arg1, int arg2, int arg3);
	char* createEventJson(const char* event, int arg1, int arg2);
	char* createEventJson(const char* event, int arg1);

};


#endif /* MODULE_MSG_HPP_ */
