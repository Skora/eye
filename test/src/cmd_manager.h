/*
 * CmdManager.h
 *
 *  Created on: 8 wrz 2016
 *      Author: SkorzecP
 */

#ifdef __cplusplus
extern "C"
{
#endif
#include "cJSON.h"
#include <stdbool.h>


#ifndef CmdManager_CmdManager_H_
#define CmdManager_CmdManager_H_

void ModuleCMD_example(int speed, int arg2, int arg3, char* pcSubcmd);

bool CmdManager_GetRegistarationResult_msg(char* tsBuffJson);
bool CmdManager_routine (char* tsBuffJson); /**Call when message arrives*/


#ifdef __cplusplus
}
#endif

#endif /* CmdManager_CmdManager_H_ */
