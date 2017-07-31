/*
 * program_options.hpp
 *
 *  Created on: 31.07.2017
 *      Author: skorzpaw
 */

#ifndef PROGRAM_OPTIONS_HPP_
#define PROGRAM_OPTIONS_HPP_

#include <string>
#include <vector>

using namespace std;

class ProgramOptions
{
	private:
	vector<string> cmdList;
	vector<void(*)()> funcVect;

	public:
	void addOption (string cmd, void(*f)());
	void listOptions ();
	int checkOptionExists (string cmd);
	void executeOptions (int argNum, char* argv[]);
};



#endif /* PROGRAM_OPTIONS_HPP_ */
