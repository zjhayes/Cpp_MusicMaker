#pragma once

#include "IPlugin.h"
#include <string>

class MusicReader : public IPlugin
{
protected:

public:
	void run();
	std::string getDescription();

};