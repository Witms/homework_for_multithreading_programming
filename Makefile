server.exe: Main_for_server.cpp ChatBot.cpp Messages.cpp TimeData.cpp Users.cpp TArrayException.cpp ForNetworkServer.cpp ConnectToDB.cpp
	g++ -std=c++17 -o server.exe Main_for_server.cpp ChatBot.cpp Messages.cpp TimeData.cpp Users.cpp TArrayException.cpp ForNetworkServer.cpp ConnectToDB.cpp -L /usr/include/mysql -l mysqlclient -I /usr/include/mysql
