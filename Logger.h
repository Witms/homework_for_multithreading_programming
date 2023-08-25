#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <filesystem>
#include <mutex>

static std::mutex mut;

class Logger
{
public:
	void operator()(std::string str)
	{

		if(!std::filesystem::exists(_file_name))
		{
			std::ofstream f(_file_name, std::ios::trunc | std::ios::out);
			f.close();
		}

	std::ofstream file(_file_name, std::ios::app);

	mut.lock();
	

	if(!file.is_open())
	{
		mut.unlock();
		return;
	}

	file << "Пользовательский ввод: " << str << std::endl;	

	file.close();

	mut.unlock();

	}
private:
	std::string _file_name = "log.txt";
};
