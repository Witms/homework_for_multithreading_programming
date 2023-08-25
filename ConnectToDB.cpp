#include "ConnectToDB.h"

namespace aiafpb1
{

ConnectToDB::ConnectToDB() {

	mysql_init(&mysql);
	if(&mysql == nullptr) {
		std::cout << "Error: can`t create MySQL-descriptor" << std::endl;
	}

	if(!mysql_real_connect(&mysql, "localhost", "cow", "cow", "chatdb", 0, NULL, 0)) {
		std::cout << "Error: can`t connect to database " << mysql_error(&mysql) << std::endl;
	}
	else {
		std::cout << "Success to set connect to database" << std::endl;
	}

	mysql_set_character_set(&mysql, "utf8");
	std::cout << "Connection characterset: " << mysql_character_set_name(&mysql) << std::endl;

}

ConnectToDB::~ConnectToDB() {
	mysql_close(&mysql);
}

void ConnectToDB::addUser(std::string aft) {
	std::string bef = "insert into users(log, passwd, name) values(";
       	bef += aft;	
	bef += ")";
	mysql_query(&mysql,bef.c_str()); 
}

bool ConnectToDB::findFromUsers(std::string tag, std::string what, std::string& info) {

	std::string query = "select exists(select ";
	query += tag;
	query += " from users where ";
	query += tag;
	query += " = '";
	query += what;
	query += "');";
	mysql_query(&mysql, query.c_str());

	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string result;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
			for(int i = 0; i < mysql_num_fields(res); i++) {
				result += row[i];
			}
		}
	}		

	if(result == "1") { 
		
		query.clear();
		query = "select log, passwd, name from users where ";
		query += tag;
		query += " = '";
		query += what;
		query += "';";
		mysql_query(&mysql, query.c_str()); 

		if(res = mysql_store_result(&mysql)) {
			while(row = mysql_fetch_row(res)) {
				info += row[0];
				info += " ";
				info += row[1];
				info += " ";
				info += row[2];
			}
		}		
		return 1;
	}
	else { return 0;}

}

bool ConnectToDB::empty() {
	mysql_query(&mysql, "select exists(select * from users)");

	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string result;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
			for(int i = 0; i < mysql_num_fields(res); i++) {
				result += row[i];
			}
		}
	}		


	if(result == "0") { return 1;}
	else { return 0;}

}

std::string ConnectToDB::Names() {

	std::string str;

	if(this->empty()) {
		str = "Пока нет зарегистрированных пользователей\n";
		return str;
	}
	
	mysql_query(&mysql, "select name, log from users");

	MYSQL_RES* res;
	MYSQL_ROW row;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
			for(int i = 0; i < mysql_num_fields(res); i++) {
				str += row[i]; 
				str += "--";
			}
			str.resize(str.size() - 2); 
			str += '\n';
		}
	}		
	
	return str;

}

void ConnectToDB::addMessage(std::string& from, std::string& to, std::string& text)
{
	std::cout << "from:" << from << std::endl;
	std::cout << "to:" << to << std::endl;
	std::cout << "text:" << text << std::endl;


	std::string bef = "insert into messages(content, from_name) values(";
    bef += "'" + text + "', '" + from + "');";	
	mysql_query(&mysql,bef.c_str()); 
	bef.clear();
	bef = "select max(id) from messages;";
	mysql_query(&mysql, bef.c_str());

	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string result;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
			for(int i = 0; i < mysql_num_fields(res); i++) {
				result += row[i];
			}
		}
	}

	std::cout << "result:" << result << std::endl;

	if(to.empty())
	{
		bef.clear();
		bef = "insert into links(user_log, message_id) values";
		std::string buff = "select log from users;";
		mysql_query(&mysql, buff.c_str());
		buff.clear();

	
	if(res = mysql_store_result(&mysql)) 
	{
		while(row = mysql_fetch_row(res)) 
		{
				if(row[0] != from)
				{
				buff += "('";
				buff += row[0];
				buff += "', " + result + "),";
				}
		}
	}

	buff[buff.length() - 1] = ';';
	bef += buff;
	mysql_query(&mysql, bef.c_str());

	}
	else
	{
	bef.clear();
	bef = "insert into links(user_log, message_id) values(";
	bef += "'" + to + "', " + result + ");";
	
	std::cout << "bef:" << bef << std::endl;

	mysql_query(&mysql, bef.c_str());
	}

}

bool ConnectToDB::getAllFresh(std::string& to_log, std::stringstream& ss)
{
	std::string bef = "select exists(select is_fresh from links where is_fresh = true && user_log = '";
	bef += to_log + "');";
	mysql_query(&mysql, bef.c_str());

	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string result;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
				result += row[0];
		}
	}

	if(result == "0")
		return false;


	bef.clear();
	bef = "select from_name, content from links,messages where user_log = '";
    bef += to_log + "' && message_id = messages.id && is_fresh = TRUE";	
	mysql_query(&mysql,bef.c_str()); 

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
				ss << std::endl << "отправлено пользователем [" << row[0]
				<< "]" << "для пользователя [" << to_log << "]:"
				<< std::endl << row[1] << std::endl;

		}
	}
	// !
	std::cout << "getAllFresh:";
	std::cout << "ss:" << ss.str();

	bef.clear();
	bef = "update links set is_fresh = false where user_log = '";
	bef += to_log + "';";
	mysql_query(&mysql, bef.c_str());

	return true;

}

bool ConnectToDB::getPartFresh(std::string& from, std::string& to, std::stringstream& info)
{
	std::string bef = "select exists(select is_fresh from links, messages where is_fresh = true && user_log = '";
	bef += to + "' && from_name = '" + from + "');";
	mysql_query(&mysql, bef.c_str());

	MYSQL_RES* res;
	MYSQL_ROW row;
	std::string result;

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
				result += row[0];
		}
	}

	if(result == "0")
		return false;

bef.clear();
bef = "select from_name, content from links,messages where user_log = '";
    bef += to + "' && is_fresh = TRUE && from_name = '" + from + "';";	
	mysql_query(&mysql, bef.c_str()); 

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
				info << std::endl << "отправлено пользователем [" << row[0]
				<< "]" << "для пользователя [" << to << "]:"
				<< std::endl << row[1] << std::endl;

		}
	}

	bef.clear();
	bef = "update links set is_fresh = false where user_log = '";
	bef += to + "' && message_id in (select messages.id from messages where from_name = '" + from + "');";
	mysql_query(&mysql, bef.c_str());

	return true;
}

void ConnectToDB::getAllMessages(std::string& to, std::stringstream& info)
{
	std::string bef;
	bef = "select from_name, content from links,messages where user_log = '";
    bef += to + "' && message_id = messages.id;";	
	mysql_query(&mysql,bef.c_str()); 

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
				info << std::endl << "отправлено пользователем [" << row[0]
				<< "]" << "для пользователя [" << to << "]:"
				<< std::endl << row[1] << std::endl;

		}
	}

	bef.clear();
	bef = "update links set is_fresh = false where user_log = '";
	bef += to + "';";
	mysql_query(&mysql, bef.c_str());
}


void ConnectToDB::getPartMessages(std::string& from, std::string& to, std::stringstream& info)
{
	std::string bef;
	bef = "select from_name, content from links,messages where user_log = '";
    bef += to + "' && from_name = '" + from + "';";	
	mysql_query(&mysql, bef.c_str()); 

	if(res = mysql_store_result(&mysql)) {
		while(row = mysql_fetch_row(res)) {
				info << std::endl << "отправлено пользователем [" << row[0]
				<< "]" << "для пользователя [" << to << "]:"
				<< std::endl << row[1] << std::endl;

		}
	}

	bef.clear();
	bef = "update links set is_fresh = false where user_log = '";
	bef += to + "' && message_id in (select messages.id from messages where from_name = '" + from + "');";
	mysql_query(&mysql, bef.c_str());

}

}