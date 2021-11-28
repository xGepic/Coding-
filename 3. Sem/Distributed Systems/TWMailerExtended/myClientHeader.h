#ifndef MYCLIENTHEADER_H
#define MYCLIENTHEADER_H

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUFFER 1024

using namespace std;

inline int create_socket;
inline char buffer[BUFFER];
inline bool isQuit;
inline bool inputCorrect = false;
inline bool isReady = false;
inline string myCommand;

void printMenu();
void printCommands();
void serverCommunication();
inline bool inputValidation(char input[BUFFER]);
inline bool isNumeric(char input[BUFFER]);
void printUsage();

#endif