#include "Users.h"

namespace aiafpb1
{
	// приведение параметров к начальным "нулевым" значениям
	void User::clear()
	{
		this->log.clear();
		this->pword.clear();
		this->name.clear();
	}

	// "полное" имя пользователя в формате (имя--логин) для возможности идентификации, т.к. имена пользователей могут совпадать
	std::string User::fullName() const { return (name + "--" + log); }

	User& User::operator=(const User& u)
	{
		if (&u != this)
		{
			log = u.log;
			pword = u.pword;
			name = u.name;
		}
		return *this;
	}

	// вывод в поток данных пользователя, используется для проверки при регистрации пользователя
	std::ostream& operator<<(std::ostream& out, const User& u)
	{
		out << " логин: " << u.log << std::endl;
		out << "пароль: " << u.pword << std::endl;
		out << "   имя: " << u.name << std::endl;
		return out;
	}

	Users::Users() {}
	Users::~Users() {}

	void Users::add(const User& u)
	{
		std::string query = "'";
		query += u.log; 
		query += "', '";
		query += u.pword; 
		query += "', '";
		query += u.name; 
		query += "'";
		DB->addUser(query);
		
	}


	bool Users::nameFound(User& c) { 
		std::string tag = "name";
		std::string what = c.name;
		std::string info;

		// !
		std::cout << "nameFound:" << std::endl;
		std::cout << "tag:" << tag << std::endl;
		std::cout << "what:" << what << std::endl;
		std::cout << "info:" << info << std::endl;

		bool result = false;
		result = DB->findFromUsers(tag, what, info);

		std::cout << "info:" << info << std::endl;

		auto save = [] (std::string& info)
		{
			std::string s;
			size_t i = 0;
			for(; i < info.size(); i++)
			{
				if(info[i] == ' ')
				{
					i++;
					break;
				}
				s += info[i];
			}
			info.erase(0, i);

			return s;
		};

		c.log = save(info);
		c.pword = save(info);
		c.name = save(info);

		std::cout << "After findFromUsers:" << std::endl;
		std::cout << "c.log:" << c.log << std::endl;
		std::cout << "c.pword:" << c.pword << std::endl;
		std::cout << "c.name:" << c.name << std::endl;
		
		return result;

	}

	bool Users::logFound(User& c) { 
		std::string tag = "log";
		std::string what = c.log;
		std::string info;
		bool result = false;
		result = DB->findFromUsers(tag, what, info);

		if(!result) return result;

		c.clear();

		int i = 0;

		for(; i < info.size(); i++) {
			if(info.c_str()[i] == ' ') {
				i++;
				break;
			}
			c.log += info.c_str()[i];
		}

		for(; i < info.size(); i++) {
			if(info.c_str()[i] == ' ') {
				i++;
				break;
			}
			c.pword += info.c_str()[i];
		}

		for(; i < info.size(); i++) {
			if(info.c_str()[i] == ' ') {
				i++;
				break;
			}
			c.name += info.c_str()[i];
		}

		std::cout << "logFound:" << std::endl;
		std::cout << "c.log:" << c.log << std::endl;
		std::cout << "c.pword:" << c.pword << std::endl;
		std::cout << "c.name:" << c.name << std::endl;
		
		return result;

	}

	// проверка наличия зарегистрированных пользователей
	bool Users::empty() const { 
		return DB->empty();

	}

	// вывод списка "полных" имен пользователей
	std::stringstream Users::showNames() const
	{
		std::stringstream info;
		info << std::endl << "Имена пользователей:" << std::endl;
		info << DB->Names().c_str();
		return info;
	}
}
//
