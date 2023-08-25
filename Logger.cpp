#include "Logger.h"


void Logger::operator()(std::string str)
{
	std::ofstream file("log.txt");

	if(!file.is_open())
		return;

	file << str;
	file << '\n';	

	file.close();

}
/*
void Logger::operator()(std::stringstream ss)
{
	std::ofstream file("log.txt");

	if(!file.is_open())
		return;
	file << ss.str();
	file << '\n';

	file.close();

}
*/
