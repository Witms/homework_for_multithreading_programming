#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <filesystem>
#include <mutex>
#include <iostream>

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

	void operator()()
	{
		char needed;

		std::cout << "Вывести содержимое файла log.txt (y/n): ";
		std::cin >> needed;

		if(needed != 'y')
		{
			return;
		}
		

		if(!std::filesystem::exists(_file_name))
		{
			return;
		}

	std::ifstream file(_file_name);

	mut.lock();

	if(!file.is_open())
	{
		mut.unlock();
		return;
	}

	char* bu = new char[std::filesystem::file_size(_file_name) + 1] {'\0'};
	file.read(bu, std::filesystem::file_size(_file_name));
	std::cout << bu;
	delete[] bu;

	file.close();

	mut.unlock();
	}

private:
	std::string _file_name = "log.txt";
};
