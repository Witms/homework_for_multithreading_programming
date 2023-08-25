#include "ForNetworkClient.h"

char buffer[PACKAGE_BUFFER];
char package[PACKAGE_BUFFER];
int socket_descriptor;
struct sockaddr_in serveraddress;

int main() {
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_family = AF_INET;
	socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
	if(connect(socket_descriptor, (struct sockaddr*) &serveraddress, sizeof(serveraddress)) < 0) {
std::cout << std::endl << "Something went wrong Connnection Failed" << std::endl;
    exit(1);
	}
	bool first = true;
	while(1) {
		if(first) {
			std::cout << std::endl << " Список команд (вводится символ команды и через пробел параметр при необходимости):" << std::endl;
			std::cout << " q - прекращение работы с программой" << std::endl;
			std::cout << " r - регистрация нового пользователя" << std::endl;
			std::cout << " i - вход пользователя в систему чата, параметр - логин" << std::endl;
			std::cout << " o - выход из системы чата" << std::endl;
			std::cout << " c - вывод чата с другим пользователем, параметр - логин или имя другого" << std::endl;
			std::cout << "     пользователя (при отсутствии параметра - вывод общего чата), находясь в котором" << std::endl;
			std::cout << "     можно написать одно сообщение другому пользователю (или всем, если общий чат)," << std::endl;
			std::cout << "     после чего происходит переход в режим ввода команд" << std::endl;
			std::cout << " m - написать сообщение пользователю, параметр - логин или имя получателя" << std::endl;
			std::cout << "     (при отсутствии параметра сообщение адресуется всем)" << std::endl;
			std::cout << " s - вывод непрочитанных сообщений, параметр - логин или имя отправителя" << std::endl;
			std::cout << "     (при отсутствии параметра выводятся все новые сообщения)" << std::endl;
			std::cout << " u - вывод списка пользователей" << std::endl;
			std::cout << " ? - вывод данного списка команд" << std::endl;
			first = false;
		}
		std::cout << "Enter a message you want to send to the server: ";
		std::string bufstr;
		std::getline(std::cin, bufstr);
		strcpy(package, bufstr.c_str());
		if(strcmp(package, "q") == 0) {
			sendto(socket_descriptor, package, PACKAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
			std::cout << "Client work is done!" << std::endl;
			close(socket_descriptor);
			exit(0);
		}
		else  {	
			sendto(socket_descriptor, package, PACKAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
		}
		recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr);
		std::cout << buffer;
	}
	close(socket_descriptor);

	return 0;
}
