#include "ChatBot.h"
#include <exception>
#include "ForNetworkServer.h"
#include <iostream>
#include "Logger.h"


int main()
{	

	makeSocket();
	bool goon = true;
	aiafpb1::ChatBot cb;
	aiafpb1::CB_command command;
	
	while (goon)
	{
		try
		{
			 recievePackage(command);
			 sstr << cb.ApplyCommand(goon, command).str();
			 sendPackage(sstr);
		}
		catch (const aiafpb1::TArrayException& e)
		{
			std::cerr << std::endl << e << std::endl;
			goon = false;
		}
		catch (const std::exception& e)
		{
			goon = false;
			std::cerr << std::endl << "Обработано стандартное исключение:" << std::endl << e.what() << std::endl;
		}
		catch (...)
		{
			goon = false;
			std::cerr << std::endl << "Обработано неизвестное исключение" << std::endl;
		}
	}

	std::cout << std::endl << "Работа программы прекращена" << std::endl;
	std::cin.get();
	return 0;
}
