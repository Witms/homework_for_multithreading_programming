#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <thread>

class Logger
{
public:
	void operator()(std::string);
//	void operator()(std::stringstream);
};
