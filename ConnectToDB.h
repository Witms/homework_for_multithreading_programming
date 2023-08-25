#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include <sstream>

class ChatBot;
class Users;

namespace aiafpb1 
{

class ConnectToDB {
	public:
		MYSQL mysql;
	private:
		MYSQL_RES* res;
		MYSQL_ROW row;
		friend class ChatBot;
		friend class Users;
	public:
		ConnectToDB();
		~ConnectToDB();
		void addUser(std::string str);
		void addMessage(std::string&, std::string&, std::string&);
		bool findFromUsers(std::string, std::string, std::string&);
		bool empty();
		std::string Names();
		bool getAllFresh(std::string&, std::stringstream& );
		bool getPartFresh(std::string&, std::string&, std::stringstream&);
		void getAllMessages(std::string&, std::stringstream&);
		void getPartMessages(std::string&, std::string&, std::stringstream&);


};

}
