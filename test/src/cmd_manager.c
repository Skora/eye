/*
 * CmdManager.c
 *
 *  Created on: 8 wrz 2016
 *      Author: SkorzecP
 */

#include "cmd_manager.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

#define SERIAL_ID 123456

#define SIZE_tcCmdStrFunc sizeof(tcCmdStrFunc)/sizeof(tcCmdStrFunc[0])

/**
 * Private typedefs
 */

typedef void (*pfuntionHandler)(int arg1,int arg2,int arg3, char* pcSubcmd ); // just pointer to fucntion typedef

typedef struct
{
	char* pCMDstr;
	pfuntionHandler ptr_func;
}CMD_Descriptor;

typedef struct
{
	int Arg1;
	int Arg2;
	int Arg3;
	char* pcSubcmd;
}T_CMDarg;

//*** Include list of Configurable parameters **/


/**
 * THIS IS WHATS NEEDS TO BE EDITED IN DIFRENTS MODULES
 * ---------------------------------------------------------------------
 */
/**Define your own functions in functional part this are just prototypes */




static const CMD_Descriptor tcCmdStrFunc[] ={
		{"Example",  &ModuleCMD_example},
		};
/**----------------------------------------------------------------------
 *
 */



/**
 *  Private variable declaration
 */


/**
 * 	Priv functions declarations
 */

bool CmdManager_privVerifyDirec (cJSON*  poJson_reciv);
bool CmdManager_privVerifyTopic (cJSON*  poJson_reciv);
bool CmdManager_privFindCMD (char* strCmdRecived, T_CMDarg oArgs);
int CmdManager_privGetArgument (cJSON* poArg);
long CmdManager_privStr2number(char* pstr);
char* CmdManager_privGetSubcmd (cJSON* poArg);

bool CmdManager_GetRegistarationResult_msg(char* tsBuffJson)
{
	  cJSON* poJson_reciv;
	  cJSON* poPayload;
	  cJSON* poResult;
	  bool bOK = false;

	  poJson_reciv = cJSON_Parse(tsBuffJson);
	  if(poJson_reciv == NULL)
	  {
		  return false;
	  }


	 if(!(CmdManager_privVerifyDirec(poJson_reciv)) )
	 		 return (bOK); //This is a subscribing request
	 if(!(CmdManager_privVerifyTopic(poJson_reciv)) )
	 		 return (bOK); //Check if topic is for us

	 /**Get payload and base on it proceed*/
	 poPayload=cJSON_GetObjectItem(poJson_reciv,"pl");
	  if(poPayload == NULL)
	  {
		  return false;
	  }

	  /**Get command ID*/
	 poResult=cJSON_GetObjectItem(poPayload,"result");
	  if(poResult == NULL)
	  {
		  return false;
	  }
	 if (!(strcmp("OK", (poResult->valuestring))))
	 {
		 bOK=true;
	 }
	 else
	 {
		 bOK=false;
	 }


	  /*clear objects*/
	  cJSON_Delete(poJson_reciv);

	  return (bOK);
}




bool CmdManager_routine (char* tsBuffJson)
{
	  cJSON* poJson_reciv;
	  cJSON* poPayload;
	  cJSON* poCmd;
	  cJSON* poArg;
	  T_CMDarg oCmdArgs;
	  bool bCmdFound = false;



	  poJson_reciv = cJSON_Parse(tsBuffJson);
	  if(poJson_reciv == NULL)
	  {
		  return false;
	  }

	  if(!(CmdManager_privVerifyDirec(poJson_reciv)) )
		  return (bCmdFound); //This is a subscribing request
	  if(!(CmdManager_privVerifyTopic(poJson_reciv)) )
		  return (bCmdFound); //Check if topic is for us

	  /**Get payload and base on it proceed*/
	  poPayload=cJSON_GetObjectItem(poJson_reciv,"pl");
	  if(poPayload == NULL)
	  {
		  return false;
	  }

	  poCmd=cJSON_GetObjectItem(poPayload,"cmd");
	  if(poCmd == NULL)
	  {
		  return false;
	  }

	  /**
	   * Get arguments
	   * [WATCH OUT NO ARGUMENT MEENS - 0XFFFF VALUE INSERTED - COVER IT IN THE CALLED FUCNTIONS]
	   * [WATCH OUT NO SUBCMD MEENS - NULL POINTER - COVER IT IN THE CALLED FUCNTIONS]
	   */
	  poArg = cJSON_GetObjectItem(poPayload,"arg1");
	  oCmdArgs.Arg1 = CmdManager_privGetArgument(poArg);
	  poArg = cJSON_GetObjectItem(poPayload,"arg2");
	  oCmdArgs.Arg2 = CmdManager_privGetArgument(poArg);
	  poArg = cJSON_GetObjectItem(poPayload,"arg3");
	  oCmdArgs.Arg3 = CmdManager_privGetArgument(poArg);
	  poArg = cJSON_GetObjectItem(poPayload,"subcmd");
	  oCmdArgs.pcSubcmd = CmdManager_privGetSubcmd(poArg);


	  /**Get command ID*/
	  bCmdFound = CmdManager_privFindCMD(poCmd->valuestring, oCmdArgs);

	  /*clear objects*/
	  cJSON_Delete(poJson_reciv);

	  return (bCmdFound);
}

/**
 * @brief Finds appropriate ModuleCMD and calls that function
 */
bool CmdManager_privFindCMD (char* strCmdRecived, T_CMDarg oCmdArgs)
{
	int i;

	/**Search every possible cmd  */
	for (i=0; i < SIZE_tcCmdStrFunc; i++)
	{
		/** if received str matches return cmd_id*/
		if (!(strcmp(tcCmdStrFunc[i].pCMDstr, strCmdRecived)))
		{
			/**Call right function*/
			tcCmdStrFunc[i].ptr_func(oCmdArgs.Arg1, oCmdArgs.Arg2, oCmdArgs.Arg3, oCmdArgs.pcSubcmd);
			return true;
		}
	}

	/**
	 * Here could be implemented some error response to MainBoard
	 */
	return false;
}

char* CmdManager_privGetSubcmd (cJSON* poArg)
{
	  if ((poArg != NULL)&&(poArg->type == 4)) //if there is  proper arg
	  {
		  return poArg->valuestring;
	  }
	  else
	  {
		 return NULL;
	  }
}

int CmdManager_privGetArgument (cJSON* poArg)
{

	  if ((poArg != 0x0)&&(poArg->type == 3)) //if there is  proper arg
	  {
		  return poArg->valueint;
	  }
	  else
	  {
		 return 0xFFFF;
	  }
}


bool CmdManager_privVerifyDirec (cJSON*  poJson_reciv)
{
	cJSON* act;
	act = cJSON_GetObjectItem(poJson_reciv, "act");


	if(act->valueint == 1)
	{
		return true;
	}
	return false;
}

bool CmdManager_privVerifyTopic (cJSON*  poJson_reciv)
{
	cJSON* top;

	top = cJSON_GetObjectItem(poJson_reciv, "top");

	char strForComp[20];
	sprintf(strForComp,"%u_in",(unsigned int)SERIAL_ID);
	if(! (strcmp(strForComp,top->valuestring)) )
	{
		return true;
	}
	return false;

}

long CmdManager_privStr2number(char* pstr)
{
	long value;

	value = strtol(pstr, &pstr, 10); // Read a number, ...

	return value;
}


