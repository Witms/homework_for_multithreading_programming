#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <filesystem>

class Logger
{
public:
	void operator()(std::string str)
	{
		if(!std::filesystem::exists("log.txt"))
		{
			std::ofstream f("log.txt", std::ios::trunc | std::ios::out);
			f.close();
		}	

	std::ofstream file("log.txt", std::ios::app);

	if(!file.is_open())
		return;

	file << "Пользовательский ввод: " << str << std::endl;	

	file.close();

	}

};
