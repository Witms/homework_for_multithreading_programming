#pragma once
#include "ConnectToDB.h"

class ChatBot;

namespace aiafpb1

{
	struct User
	{
	public:
		std::string log;
		std::string name;
		std::string pword;

		void clear();
		std::string fullName() const;
		User& operator=(const User&);
		friend std::ostream& operator<< (std::ostream&, const User&);
		friend class ChatBot;
	};

	class Users
	{
	private:

		ConnectToDB* DB = nullptr;
		friend class ChatBot;

	public:
		Users(); 
		~Users();

		void add(const User&);
		bool nameFound(User&);
		bool logFound(User&);
		bool empty() const;
		std::stringstream showNames() const;
	};
}
