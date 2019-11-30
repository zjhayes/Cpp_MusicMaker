#pragma once

#include "IPlugin.h"
#include <string>
#include <iostream>
#include <fstream>

class MusicReader : public IPlugin
{
protected:
	std::string requestFile();
	void readFile(std::string);
	void parseLine(std::string);
public:
	void run();
	std::string getDescription();

};