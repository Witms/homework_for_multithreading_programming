#pragma once

#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <thread>
#include "ChatBot.h"

#define PACKAGE_BUFFER 4096
#define PORT 7777

extern char buffer[];
extern char package[];
extern int socket_file_descriptor, package_size;
extern socklen_t length;
extern const char *end_string;
extern struct sockaddr_in serveraddress, client;
extern std::stringstream sstr;

void makeSocket();
void recievePackage(std::string &str);
void recievePackage(aiafpb1::CB_command &cmd);
void sendPackage(std::stringstream& sstr);


