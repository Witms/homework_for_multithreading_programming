#include "Messages.h"
#include "ConnectToDB.h"

namespace aiafpb1
{
	Message& Message::operator=(const Message& m)
	{
		if (&m != this)
		{
			text = m.text;
			from_name = m.from_name;
			to_name = m.to_name;
			time = m.time;
			fresh = m.fresh;
		}
		return *this;
	}

	// вывод параметров сообщения в поток, используется для вывода списка сообщений
	std::ostream& operator<<(std::ostream& out, const Message& m)
	{
		out << std::endl << "отправлено " << m.time << " пользователем [" << m.from_name << "]";
		if (m.to_name.empty()) { out << " для всех пользователей:"; }
		else
		{
			out << " для пользователя [" << m.to_name << "]:";
			if (!m.fresh) { out << std::endl << "[сообщение прочитано получателем]"; }
		}
		out << std::endl << m.text << std::endl;
		return out;
	}

	Messages::Messages() {}
	Messages::~Messages() {}

	// добавление сообщения в массив
	void Messages::add(Message& m) 
	{ 
		 std::string from = m.from_name, to = m.to_name, text = m.text;
		auto log = [] (std::string& str) {
			const char* delim = "-";
			std::string::size_type pos{};
			pos = str.find_first_of(delim, pos);
			str.erase(0, pos + 2);
		};
		log(from);
		log(to);

		 DB->addMessage(from, to, text);
	} // !

	// предикат (условие) для отбора общих сообщений, передается по указателю в TArray.getSelection через функцию getCommon (см. ниже)
	bool Messages::selectCommon(const Message& m, Message& c)
	{
		return (m.to_name.empty());
	}

	// предикат (условие) для отбора парных сообщений, передается по указателю в TArray.getSelection через функцию getPaired (см. ниже)
	bool Messages::selectPaired(const Message& m, Message& c)
	{
		return ((m.to_name == c.to_name && m.from_name == c.from_name) || (m.to_name == c.from_name && m.from_name == c.to_name));
	}

	// предикат (условие) для отбора непрочитанных сообщений, передается по указателю в TArray.getSelection через функцию getFresh (см. ниже)
	bool Messages::selectFresh(const Message& m, Message& c)
	{
		bool result = false;
		if (c.from_name.empty())
		{
			if (m.to_name.empty()) { result = (m.time > c.time); }
			else { result = (m.fresh && m.to_name == c.to_name); }
		}
		else { result = (m.from_name == c.from_name && m.to_name == c.to_name && m.fresh); }
		return result;
	}

	void Messages::getCommon(std::string& to, std::stringstream& info)
	{
		
		DB->getAllMessages(to, info);
	}
	
	void Messages::getPaired(Message& c, std::stringstream& info)
	{
		auto del = [] (std::string str)
		{
			std::string s;
			size_t i = 0;
			for(; i < str.size(); i++)
			{
				if(str[i] == '-')
				{
					i++;
					i++;
					break;
				}
			}
			str.erase(0, i);
			s = str;


			return s;
		};

		std::string to = del(c.to_name);
		std::string from = del(c.from_name);

		DB->getPartMessages(from, to, info);
	}

	bool Messages::getFresh(Message& m, std::stringstream& m_p)
	{
		auto del = [] (std::string str)
		{
			std::string s;
			size_t i = 0;
			for(; i < str.size(); i++)
			{
				if(str[i] == '-')
				{
					i++;
					i++;
					break;
				}
			}
			str.erase(0, i);
			s = str;


			return s;
		};

		std::string to_log = del(m.to_name);

		if(m.from_name.empty())
		{
			return DB->getAllFresh(to_log, m_p);
		}
		else
		{
			std::string from_log = del(m.from_name);
			return DB->getPartFresh(from_log, to_log, m_p);
		}

		return false;
	}
}