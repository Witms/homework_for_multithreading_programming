#include "ForNetworkServer.h"
#include "Logger.h"


char buffer[PACKAGE_BUFFER];
char package[PACKAGE_BUFFER];
int socket_file_descriptor, package_size;
socklen_t length;
const char *end_string = "q";
struct sockaddr_in serveraddress, client;
std::stringstream sstr;

void makeSocket() {
	socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_family = AF_INET;
	bind(socket_file_descriptor, (struct sockaddr*) &serveraddress, sizeof(serveraddress));
}

void recievePackage(std::string &str) {

	length = sizeof(client);
	package_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*) &client, &length);
	buffer[package_size] = '\0';

	std::cout << "This is that came from client: " << buffer << std::endl;
	if(strcmp(buffer, end_string) == 0) {
		std::cout << "Server is Quitting" << std::endl;
		close(socket_file_descriptor);
		exit(0);
	}
	str = buffer;
	Logger logg;
	std::thread t1(logg, str);
	if(t1.joinable())
		t1.join();

}

void recievePackage(aiafpb1::CB_command &cmd) {
	length = sizeof(client);
	package_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*) &client, &length);
	buffer[package_size] = '\0';
	std::cout << "This is that went from client: " << buffer << std::endl;
	if(strcmp(buffer, end_string) == 0) {
		std::cout << "Server is Quitting" << std::endl;
		close(socket_file_descriptor);
		exit(0);
	}
	std::stringstream str;
	str << buffer;
	str >> cmd;

	Logger logg;
	std::thread t2(logg, str.str());
	if(t2.joinable())
		t2.join();
}

void sendPackage(std::stringstream& sstr) {
	strcpy(package, sstr.str().c_str());
	Logger logg;
	std::thread t3(logg, sstr.str());
	if(t3.joinable())
		t3.join();
	sendto(socket_file_descriptor, package, PACKAGE_BUFFER, 0, (struct sockaddr*) &client, sizeof(client));
}
