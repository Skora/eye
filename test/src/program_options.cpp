/*
 * program_options.cpp
 *
 *  Created on: 31.07.2017
 *      Author: skorzpaw
 */

#include "program_options.hpp"
#include <iostream>

void ProgramOptions::executeOptions (int argNum, char* argv[])
{
	int cmdNum = -1;
	for (int i = 1; i <= argNum; i++)
	{
		cmdNum = checkOptionExists((string)argv[i]);
		if ((cmdNum >= 0) && (funcVect.size()) )
		{
			(*funcVect[cmdNum])();;
		}
	}
}

int  ProgramOptions::checkOptionExists (string cmd)
{
	int i = 0;
	vector<string>::iterator it;
	for (it = cmdList.begin(); it != cmdList.end(); ++it)
	{
		if ((*it).find(cmd) != string::npos)
		{
			return i;
		}
		i++;
	}
	return -1;
}

void  ProgramOptions::listOptions ()
{
	vector<string>::iterator it;
	cout << "Program supports following options" << endl;
	for (it = cmdList.begin(); it != cmdList.end(); ++it)
	{
		cout << *it << endl;
	}
}

void  ProgramOptions::addOption (string cmd, void(*f)())
{
	cmdList.push_back(cmd);
	funcVect.push_back(f);
}

