#pragma once

#include <string>
#include "MusicMaker.h"

// Base class
class IPlugin {
public:
	// pure virtual function providing interface framework.
	virtual std::string getDescription() = 0;
	virtual void run() = 0;
};